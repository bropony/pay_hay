#include "Dao/Impl/Base/UserImgCached.h"
#include "Dao/Impl/UserImgDaoImpl.h"
#include "framework/util/exception.h"
#include "framework/db/cached/cachedmanager.h"
#include "framework/db/cached/cachedtransaction.h"
#include "framework/log/loggerutil.h"

using namespace cdf;
using namespace cdf::dao;
using namespace cdf::cached;
using namespace Dao::Impl;
USE_FASTDB_NAMESPACE;

REGISTER( TUserImgCached );
cdf::CAutoRun CUserImgCached::_autoRun( CUserImgCached::regist );

FASTDB_NS::dbFieldDescriptor* 
TUserImgCached::dbDescribeComponents(FASTDB_NS::dbFieldDescriptor*)
{
    return
        &(
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("img_id", (char*)&imgId-(char*)this , sizeof( imgId ), FASTDB_NS::HASHED | FASTDB_NS::INDEXED ), imgId),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("img_path", (char*)&imgPath-(char*)this , sizeof( imgPath ), 0 ), imgPath),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("short_desc", (char*)&shortDesc-(char*)this , sizeof( shortDesc ), 0 ), shortDesc)
        );
    
}

void
TUserImgCached::__update( const Message::Db::Tables::TUserImg& t )
{
    imgId = t.imgId;
    imgPath = t.imgPath;
    shortDesc = t.shortDesc;
}

void
TUserImgCached::__save( Message::Db::Tables::TUserImg& t ) const 
{
    t.imgId = imgId;
    t.imgPath = imgPath;
    t.shortDesc = shortDesc;
}

void Dao::Impl::CUserImgCached::regist()
{
    static Dao::Impl::CUserImgCached cached;
    cdf::cached::CCachedManager::instance()->registTableCached( "t_user_img" , &cached );
}

bool Dao::Impl::CUserImgCached::get( int id , Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool update )
{
    dbQuery q;
    q = "img_id=",(id);
    dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbCursorType type = dbCursorViewOnly;
    if( update )
    {
        type = dbCursorForUpdate;
    }
    int n = cursor.select( q , type );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        cursor.get()->__save( v );
        return true;
    }
}

void Dao::Impl::CUserImgCached::save( Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt1 = conn->createStatement();
    TUserImgCached t;
    if( !isInsertOnly() )
    {
        conn->setCached( false );
        conn->begin( false );
        MEM_NODE_PTR nodePtr = getNagtive( stmt1.get() );
        conn->commit( false );
        v.imgId = nodePtr->getNode().imgId;
        t.__update( v );
        if( !isNagtiveOnly() )
        {
            dbAnyReference ref;
            CCachedManager::instance()->getDb().insertRecord( 
            	&TUserImgCached::dbDescriptor , &ref , &t
            	);
        }
    }
    else
    {
        v.imgId = ++ _id;
        t.__update( v );
    }
    __registToTx( 
    	stmt->getConnection()->getTransaction() , 
    	t ,
    	cdf::cached::ECachedUpdateModelAdd
    	);
}

bool Dao::Impl::CUserImgCached::update( const Message::Db::Tables::TUserImg& t , cdf::CStatement* stmt )
{
    dbQuery q;
    q = "img_id=",(t.imgId);
    dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
    int n = cursor.select( q , dbCursorForUpdate );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        cursor.get()->__update( t );
        cursor.update();
        __registToTx( 
        	stmt->getConnection()->getTransaction() , 
        	*cursor.get() ,
        	cdf::cached::ECachedUpdateModelUpdate
        	);
        return true;
    }
}

long64_t Dao::Impl::CUserImgCached::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt )
{
    dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    makeQuery( cmp , cachedCmpNodes , query );
    int n = cursor.select( query , dbCursorForUpdate );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        do
        {
            __update( *cursor.get() , seq );
            cursor.update();
            __registToTx( 
            stmt->getConnection()->getTransaction() , 
            *cursor.get() ,
            cdf::cached::ECachedUpdateModelUpdate 
            );
        }
        while( cursor.next() );
    }
    return n;
}

bool Dao::Impl::CUserImgCached::remove( int id , cdf::CStatement* stmt )
{
    dbQuery q;
    q = "img_id=",(id);
    dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
    int n = cursor.select( q , dbCursorForUpdate );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        do
        {
            __registToTx( 
            	stmt->getConnection()->getTransaction() , 
            	*cursor.get() ,
            	cdf::cached::ECachedUpdateModelDelete
            	);
        }
        while( cursor.next() );
        cursor.removeAllSelected();
        return true;
    }
}

long64_t Dao::Impl::CUserImgCached::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserImg& v , cdf::CStatement* stmt , bool update )
{
    v.clear();
    dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query1;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    makeQuery( query.cmpNodes , cachedCmpNodes , query1 );
    std::string order;
    makeOrder( query.orderType , query1 , order );
    dbCursorType type = dbCursorViewOnly;
    if( update )
    {
        type = dbCursorForUpdate;
    }
    int n = cursor.select( query1 , type );
    if( query.countType == cdf::dao::FIND_COUNT_TYPE_WITH_COUNT )
    {
        return n;
    }
    if( 0 == n )
    {
        return 0;
    }
    else
    {
        int i = 0;
        Message::Db::Tables::TUserImg table;
        do
        {
            if( query.startIndex == query.endIndex && query.startIndex == 0 )
            {
                cursor.get()->__save( table );
                v.push_back( table );
            }
            else
            {
                if( i >= query.startIndex )
                {
                    if( i < query.endIndex )
                    {
                        cursor.get()->__save( table );
                        v.push_back( table );
                    }
                    else
                    {
                        break;
                    }
                }
                i ++;
            }
        }
        while( cursor.next() );
    }
    if( query.countType == cdf::dao::FIND_COUNT_TYPE_WITH_DATA )
    {
        return 0;
    }
    return n;
}

bool Dao::Impl::CUserImgCached::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool update )
{
    dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query1;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    makeQuery( query.cmpNodes , cachedCmpNodes , query1 );
    dbCursorType type = dbCursorViewOnly;
    if( update )
    {
        type = dbCursorForUpdate;
    }
    int n = cursor.select( query1 , type );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        cursor.get()->__save( v );
        return true;
    }
}

long64_t Dao::Impl::CUserImgCached::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt )
{
    dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    makeQuery( cmp , cachedCmpNodes , query );
    int n = cursor.select( query , dbCursorForUpdate );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        do
        {
            int id = cursor.get()->imgId;
            cursor.get()->__update( v );
            cursor.get()->imgId = id;
            __registToTx( 
            stmt->getConnection()->getTransaction() , 
            *cursor.get() ,
            cdf::cached::ECachedUpdateModelUpdate );
            cursor.update();
        }
        while( cursor.next() );
    }
    return n;
}

long64_t Dao::Impl::CUserImgCached::remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt )
{
    dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query1;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    int n = 0;
    makeQuery( cmp , cachedCmpNodes , query1 );
    n = cursor.select( query1 , dbCursorForUpdate );
    if( n == 0 )
    {
        return 0;
    }
    do
    {
        __registToTx( 
        stmt->getConnection()->getTransaction() , 
        *cursor.get() ,
        cdf::cached::ECachedUpdateModelDelete
        );
    }
    while( cursor.next() );
    cursor.removeAllSelected();
    return n;
}

int Dao::Impl::CUserImgCached::getTotalCount()
{
    dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
    return cursor.select( dbCursorViewOnly );
}

void Dao::Impl::CUserImgCached::clear( cdf::CStatement* stmt )
{
    
    remove( cdf::dao::SeqCmpNode() , stmt );
}

void Dao::Impl::CUserImgCached::load( cdf::CStatement* stmt )
{
    CUserImgDaoImpl dao;
    cdf::dao::SQuery query;
    if ( !getNagtiveCheck().empty() )
    {
        cdf::dao::SCmpNode cmpNode;
        cmpNode.setColumnName( getNagtiveCheck() );
        cmpNode.setEqualType( cdf::dao::EQUAL_TYPE_NOT_EQUAL );
        bool canCheck = true;
        if ( getNagtiveCheck() == "img_id" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "img_path" )
        {
            cmpNode.setString( "" );
        }
        else if ( getNagtiveCheck() == "short_desc" )
        {
            cmpNode.setString( "" );
        }
        else 
        {
            assert( false );
            canCheck = false;
        }
        if ( canCheck )
        {
            query.cmpNodes.push_back( cmpNode );
        }
    }
    Message::Db::Tables::SeqTUserImg tables;
    TUserImgCached table;
    dao.CUserImgDaoImplBase::find( query , tables , stmt , false , false );
    Message::Db::Tables::SeqTUserImg::iterator iter;
    for( iter = tables.begin() ; iter != tables.end() ; iter ++ )
    {
        dbAnyReference ref;
        table.__update( *iter );
        CCachedManager::instance()->getDb().insertRecord( 
        &TUserImgCached::dbDescriptor , &ref , &table
        );
    }
}

void Dao::Impl::CUserImgCached::flush( cdf::CStatement* stmt )
{
    CUserImgDaoImpl dao;
    MEM_NODE_MAP flushMap;
    {
        cdf::CAutoLightLock l(_lock);
        if( _flushMap.size() == 0 )
        {
            return;
        }
        flushMap = _flushMap;
        _flushMap.clear();
    }
    for( MEM_NODE_MAP::const_iterator iter = flushMap.begin() ; iter != flushMap.end() ; iter ++ )
    {
        CDE_BEGIN_TRY
        {
            switch( iter->second->getUpdateMode() )
            {
                case ECachedUpdateModelAdd:
                {
                    dao.CUserImgDaoImplBase::save( iter->second->getNode() , stmt , false );
                }
                break;
                case ECachedUpdateModelUpdate:
                {
                    dao.CUserImgDaoImplBase::update( iter->second->getNode() , stmt , false );
                }
                break;
                case ECachedUpdateModelDelete:
                {
                    dao.CUserImgDaoImplBase::remove( iter->second->getNode().imgId , stmt , false );
                }
            }
        }
        CDE_END_TRY( __FILE__ , __LINE__ );
    }
}

void Dao::Impl::CUserImgCached::rollback( cdf::CTransaction* tx )
{
    cdf::CAutoLightLock l(_lock);
    TRANSACTION_MAP::iterator iter;
    iter = _transactionNodes.find( tx );
    if( _transactionNodes.end() == iter )
    {
        return;
    }
    for( 
    MEM_NODE_MAP::const_iterator iter1 = iter->second.begin() ;
    iter1 != iter->second.end() ; 
    iter1 ++ 
    )
    {
        if( iter1->second->getUpdateMode() & ECachedUpdateModelAdd )
        {
            iter1->second->setUpdateMode( ECachedUpdateModelDelete );
            MEM_NODE_MAP::iterator iter2 = _flushMap.find( iter1->first );
            if( iter2 == _flushMap.end() )
            {
                _flushMap[iter1->first] = iter1->second;
            }
            else
            {
                iter2->second = iter1->second;
            }
        }
    }
    _transactionNodes.erase( iter );
}

void Dao::Impl::CUserImgCached::commit( cdf::CTransaction* tx )
{
    cdf::CAutoLightLock l(_lock);
    TRANSACTION_MAP::iterator iter;
    iter = _transactionNodes.find( tx );
    if( _transactionNodes.end() == iter )
    {
        return;
    }
    for( 
    MEM_NODE_MAP::const_iterator iter1 = iter->second.begin() ;
    iter1 != iter->second.end() ; 
    iter1 ++ )
    {
        MEM_NODE_MAP::iterator iter2 = _flushMap.find( iter1->first );
        if( iter1->second->getUpdateMode() & ECachedUpdateModelDelete )
        {
            iter1->second->setUpdateMode( ECachedUpdateModelDelete );
        }
        else if( iter1->second->getUpdateMode() & ECachedUpdateModelAdd )
        {
            if( !isInsertOnly() )
            {
                iter1->second->setUpdateMode( ECachedUpdateModelUpdate );
            }
            else
            {
                iter1->second->setUpdateMode( ECachedUpdateModelAdd );
            }
        }
        else if( iter1->second->getUpdateMode() & ECachedUpdateModelUpdate )
        {
            iter1->second->setUpdateMode( ECachedUpdateModelUpdate );
        }
        if( iter2 == _flushMap.end() )
        {
            _flushMap[iter1->first] = iter1->second;
        }
        else
        {
            iter2->second = iter1->second;
        }
    }
    _transactionNodes.erase( iter );
}

void Dao::Impl::CUserImgCached::unnagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    CUserImgDaoImpl dao;
    for( MEM_NODE_LIST::const_iterator iter = _nagtiveList.begin() ; iter != _nagtiveList.end() ; iter ++ )
    {
        dao.CUserImgDaoImplBase::remove( (*iter)->getNode().imgId , stmt , false );
    }
    _nagtiveList.clear();
}
void Dao::Impl::CUserImgCached::nagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    if( (int)_nagtiveList.size() <= ( getNagtiveCount() / 2 ) )
    {
        Message::Db::Tables::TUserImg t;
        t.__init();
        bool isBegin = stmt->getConnection()->getTransaction()->isBegin();
        if( !isBegin )
        {
            stmt->getConnection()->begin( false );
        }
        CUserImgDaoImpl dao;
        while( (int)_nagtiveList.size() < getNagtiveCount() )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( ECachedUpdateModelAdd );
            dao.CUserImgDaoImplBase::save( t , stmt , false );
            nodePtr->getNode().__update( t );
            _nagtiveList.push_back( nodePtr );
        }
        if( !isBegin )
        {
            stmt->getConnection()->commit( false );
        }
    }
}
void Dao::Impl::CUserImgCached::cached( const cdf::dao::SQuery& query , cdf::CStatement* stmt )
{
    CUserImgDaoImpl dao;
    Message::Db::Tables::SeqTUserImg tables;
    dao.CUserImgDaoImplBase::find( query , tables , stmt , false , false );
    cached( tables );
}
void Dao::Impl::CUserImgCached::cached( Message::Db::Tables::SeqTUserImg& tables )
{
    TUserImgCached table;
    Message::Db::Tables::SeqTUserImg::const_iterator iter;
    for( iter = tables.begin() ; iter != tables.end() ; iter ++ )
    {
        dbQuery q;
        q = "img_id=",(iter->imgId);
        dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
        if( cursor.select( q , dbCursorForUpdate ) == 0 )
        {
            dbAnyReference ref;
            table.__update( *iter );
            CCachedManager::instance()->getDb().insertRecord( &TUserImgCached::dbDescriptor , &ref , &table );
        }
    }
}
void Dao::Impl::CUserImgCached::evict( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt )
{
    dbCursor< TUserImgCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query1;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    int n = 0;
    makeQuery( cmp , cachedCmpNodes , query1 );
    n = cursor.select( query1 , dbCursorForUpdate );
    if( n == 0 )
    {
        return;
    }
    cursor.removeAllSelected();
}
Dao::Impl::CUserImgCached::MEM_NODE_PTR Dao::Impl::CUserImgCached::getNagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    if( _nagtiveList.empty() )
    {
        Message::Db::Tables::TUserImg t;
        t.__init();
        bool isBegin = stmt->getConnection()->getTransaction()->isBegin();
        if( !isBegin )
        {
            stmt->getConnection()->begin( false );
        }
        CUserImgDaoImpl dao;
        while( (int)_nagtiveList.size() < getNagtiveCount() )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( ECachedUpdateModelAdd );
            dao.CUserImgDaoImplBase::save( t , stmt , false );
            nodePtr->getNode().__update( t );
            _nagtiveList.push_back( nodePtr );
        }
        if( !isBegin )
        {
            stmt->getConnection()->commit( false );
        }
    }
    if( _nagtiveList.empty() )
    {
        return NULL;
    }
    else
    {
        MEM_NODE_PTR node = *_nagtiveList.begin();
        _nagtiveList.pop_front();
        return node;
    }
}
void Dao::Impl::CUserImgCached::__registToTx( 
	cdf::CTransaction* tx , 
	const TUserImgCached& table,
	cdf::cached::ECachedUpdateModel model
	)
{
    cdf::CAutoLightLock l(_lock);
    if( tx->isBegin() && !isInsertOnly() )
    {
        CCachedTransaction *tx1 = (CCachedTransaction*)tx;
        tx1->insertTable( this );
        TRANSACTION_MAP::iterator iter;
        iter = _transactionNodes.find( tx );
        if( _transactionNodes.end() == iter )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( model );
            Message::Db::Tables::TUserImg v;
            table.__save( v );
            nodePtr->setNode( v );
            _transactionNodes[tx][nodePtr->getNode().imgId] = nodePtr;
        }
        else
        {
            MEM_NODE_MAP::iterator iter2 = iter->second.find( table.imgId );
            if( iter2 == iter->second.end() )
            {
                MEM_NODE_PTR nodePtr = new MEM_NODE();
                nodePtr->setUpdateMode( model );
                Message::Db::Tables::TUserImg v;
                table.__save( v );
                nodePtr->setNode( v );
                iter->second[ table.imgId ] = nodePtr;
            }
            else
            {
                iter2->second->setUpdateMode( iter2->second->getUpdateMode() | model );
                table.__save( iter2->second->getNode() );
            }
        }
    }
    else
    {
        MEM_NODE_PTR nodePtr = new MEM_NODE();
        if( model == ECachedUpdateModelAdd && !isInsertOnly() )
        {
            nodePtr->setUpdateMode( ECachedUpdateModelUpdate );
        }
        else
        {
            nodePtr->setUpdateMode( model );
        }
        Message::Db::Tables::TUserImg v;
        table.__save( v );
        nodePtr->setNode( v );
        MEM_NODE_MAP::iterator iter = _flushMap.find( table.imgId );
        if( iter == _flushMap.end() )
        {
            _flushMap[table.imgId] = nodePtr;
        }
        else
        {
            iter->second = nodePtr;
        }
    }
}
void Dao::Impl::CUserImgCached::__update(
    TUserImgCached& v,
	const cdf::dao::SeqDataNode& seq 
	)
{
    cdf::dao::SeqDataNode::const_iterator iter;
    for( iter = seq.begin() ; iter != seq.end() ; iter ++ )
    {
        if( iter->getColumnName() == "img_path" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_user_img column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.imgPath = iter->getString();
            continue;
        }
        if( iter->getColumnName() == "short_desc" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_user_img column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.shortDesc = iter->getString();
            continue;
        }
        std::string exp = "table name:t_user_img column name:" + iter->getColumnName() + " error";
        throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
    }
}