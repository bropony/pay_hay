#include "Dao/Impl/Base/UserPostCached.h"
#include "Dao/Impl/UserPostDaoImpl.h"
#include "framework/util/exception.h"
#include "framework/db/cached/cachedmanager.h"
#include "framework/db/cached/cachedtransaction.h"
#include "framework/log/loggerutil.h"

using namespace cdf;
using namespace cdf::dao;
using namespace cdf::cached;
using namespace Dao::Impl;
USE_FASTDB_NAMESPACE;

REGISTER( TUserPostCached );
cdf::CAutoRun CUserPostCached::_autoRun( CUserPostCached::regist );

FASTDB_NS::dbFieldDescriptor* 
TUserPostCached::dbDescribeComponents(FASTDB_NS::dbFieldDescriptor*)
{
    return
        &(
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("post_id", (char*)&postId-(char*)this , sizeof( postId ), FASTDB_NS::HASHED | FASTDB_NS::INDEXED ), postId),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("user_id", (char*)&userId-(char*)this , sizeof( userId ), FASTDB_NS::INDEXED ), userId),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("title", (char*)&title-(char*)this , sizeof( title ), 0 ), title),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("content", (char*)&content-(char*)this , sizeof( content ), 0 ), content),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("img_list", (char*)&imgList-(char*)this , sizeof( imgList ), 0 ), imgList),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("nlike", (char*)&nlike-(char*)this , sizeof( nlike ), 0 ), nlike),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("ndislike", (char*)&ndislike-(char*)this , sizeof( ndislike ), 0 ), ndislike),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("ncomment", (char*)&ncomment-(char*)this , sizeof( ncomment ), 0 ), ncomment),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("post_dt", (char*)&postDt-(char*)this , sizeof( postDt ), 0 ), postDt)
        );
    
}

void
TUserPostCached::__update( const Message::Db::Tables::TUserPost& t )
{
    postId = t.postId;
    userId = t.userId;
    title = t.title;
    content = t.content;
    imgList = t.imgList;
    nlike = t.nlike;
    ndislike = t.ndislike;
    ncomment = t.ncomment;
    {
        cdf::CDateTime __date( t.postDt );
        __date.clearMillSecond();
        postDt = __date.getTotalMill();
    }
}

void
TUserPostCached::__save( Message::Db::Tables::TUserPost& t ) const 
{
    t.postId = postId;
    t.userId = userId;
    t.title = title;
    t.content = content;
    t.imgList = imgList;
    t.nlike = nlike;
    t.ndislike = ndislike;
    t.ncomment = ncomment;
    t.postDt.init( postDt );
}

void Dao::Impl::CUserPostCached::regist()
{
    static Dao::Impl::CUserPostCached cached;
    cdf::cached::CCachedManager::instance()->registTableCached( "t_user_post" , &cached );
}

bool Dao::Impl::CUserPostCached::get( int id , Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool update )
{
    dbQuery q;
    q = "post_id=",(id);
    dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

void Dao::Impl::CUserPostCached::save( Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt1 = conn->createStatement();
    TUserPostCached t;
    if( !isInsertOnly() )
    {
        conn->setCached( false );
        conn->begin( false );
        MEM_NODE_PTR nodePtr = getNagtive( stmt1.get() );
        conn->commit( false );
        v.postId = nodePtr->getNode().postId;
        t.__update( v );
        if( !isNagtiveOnly() )
        {
            dbAnyReference ref;
            CCachedManager::instance()->getDb().insertRecord( 
            	&TUserPostCached::dbDescriptor , &ref , &t
            	);
        }
    }
    else
    {
        v.postId = ++ _id;
        t.__update( v );
    }
    __registToTx( 
    	stmt->getConnection()->getTransaction() , 
    	t ,
    	cdf::cached::ECachedUpdateModelAdd
    	);
}

bool Dao::Impl::CUserPostCached::update( const Message::Db::Tables::TUserPost& t , cdf::CStatement* stmt )
{
    dbQuery q;
    q = "post_id=",(t.postId);
    dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

long64_t Dao::Impl::CUserPostCached::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt )
{
    dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

bool Dao::Impl::CUserPostCached::remove( int id , cdf::CStatement* stmt )
{
    dbQuery q;
    q = "post_id=",(id);
    dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

long64_t Dao::Impl::CUserPostCached::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserPost& v , cdf::CStatement* stmt , bool update )
{
    v.clear();
    dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
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
        Message::Db::Tables::TUserPost table;
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

bool Dao::Impl::CUserPostCached::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool update )
{
    dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

long64_t Dao::Impl::CUserPostCached::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt )
{
    dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
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
            int id = cursor.get()->postId;
            cursor.get()->__update( v );
            cursor.get()->postId = id;
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

long64_t Dao::Impl::CUserPostCached::remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt )
{
    dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

int Dao::Impl::CUserPostCached::getTotalCount()
{
    dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
    return cursor.select( dbCursorViewOnly );
}

void Dao::Impl::CUserPostCached::clear( cdf::CStatement* stmt )
{
    
    remove( cdf::dao::SeqCmpNode() , stmt );
}

void Dao::Impl::CUserPostCached::load( cdf::CStatement* stmt )
{
    CUserPostDaoImpl dao;
    cdf::dao::SQuery query;
    if ( !getNagtiveCheck().empty() )
    {
        cdf::dao::SCmpNode cmpNode;
        cmpNode.setColumnName( getNagtiveCheck() );
        cmpNode.setEqualType( cdf::dao::EQUAL_TYPE_NOT_EQUAL );
        bool canCheck = true;
        if ( getNagtiveCheck() == "post_id" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "user_id" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "title" )
        {
            cmpNode.setString( "" );
        }
        else if ( getNagtiveCheck() == "content" )
        {
            cmpNode.setString( "" );
        }
        else if ( getNagtiveCheck() == "img_list" )
        {
            cmpNode.setString( "" );
        }
        else if ( getNagtiveCheck() == "nlike" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "ndislike" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "ncomment" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "post_dt" )
        {
            assert( false );
            canCheck = false;
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
    Message::Db::Tables::SeqTUserPost tables;
    TUserPostCached table;
    dao.CUserPostDaoImplBase::find( query , tables , stmt , false , false );
    Message::Db::Tables::SeqTUserPost::iterator iter;
    for( iter = tables.begin() ; iter != tables.end() ; iter ++ )
    {
        dbAnyReference ref;
        table.__update( *iter );
        CCachedManager::instance()->getDb().insertRecord( 
        &TUserPostCached::dbDescriptor , &ref , &table
        );
    }
}

void Dao::Impl::CUserPostCached::flush( cdf::CStatement* stmt )
{
    CUserPostDaoImpl dao;
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
                    dao.CUserPostDaoImplBase::save( iter->second->getNode() , stmt , false );
                }
                break;
                case ECachedUpdateModelUpdate:
                {
                    dao.CUserPostDaoImplBase::update( iter->second->getNode() , stmt , false );
                }
                break;
                case ECachedUpdateModelDelete:
                {
                    dao.CUserPostDaoImplBase::remove( iter->second->getNode().postId , stmt , false );
                }
            }
        }
        CDE_END_TRY( __FILE__ , __LINE__ );
    }
}

void Dao::Impl::CUserPostCached::rollback( cdf::CTransaction* tx )
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

void Dao::Impl::CUserPostCached::commit( cdf::CTransaction* tx )
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

void Dao::Impl::CUserPostCached::unnagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    CUserPostDaoImpl dao;
    for( MEM_NODE_LIST::const_iterator iter = _nagtiveList.begin() ; iter != _nagtiveList.end() ; iter ++ )
    {
        dao.CUserPostDaoImplBase::remove( (*iter)->getNode().postId , stmt , false );
    }
    _nagtiveList.clear();
}
void Dao::Impl::CUserPostCached::nagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    if( (int)_nagtiveList.size() <= ( getNagtiveCount() / 2 ) )
    {
        Message::Db::Tables::TUserPost t;
        t.__init();
        bool isBegin = stmt->getConnection()->getTransaction()->isBegin();
        if( !isBegin )
        {
            stmt->getConnection()->begin( false );
        }
        CUserPostDaoImpl dao;
        while( (int)_nagtiveList.size() < getNagtiveCount() )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( ECachedUpdateModelAdd );
            dao.CUserPostDaoImplBase::save( t , stmt , false );
            nodePtr->getNode().__update( t );
            _nagtiveList.push_back( nodePtr );
        }
        if( !isBegin )
        {
            stmt->getConnection()->commit( false );
        }
    }
}
void Dao::Impl::CUserPostCached::cached( const cdf::dao::SQuery& query , cdf::CStatement* stmt )
{
    CUserPostDaoImpl dao;
    Message::Db::Tables::SeqTUserPost tables;
    dao.CUserPostDaoImplBase::find( query , tables , stmt , false , false );
    cached( tables );
}
void Dao::Impl::CUserPostCached::cached( Message::Db::Tables::SeqTUserPost& tables )
{
    TUserPostCached table;
    Message::Db::Tables::SeqTUserPost::const_iterator iter;
    for( iter = tables.begin() ; iter != tables.end() ; iter ++ )
    {
        dbQuery q;
        q = "post_id=",(iter->postId);
        dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
        if( cursor.select( q , dbCursorForUpdate ) == 0 )
        {
            dbAnyReference ref;
            table.__update( *iter );
            CCachedManager::instance()->getDb().insertRecord( &TUserPostCached::dbDescriptor , &ref , &table );
        }
    }
}
void Dao::Impl::CUserPostCached::evict( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt )
{
    dbCursor< TUserPostCached > cursor( &( CCachedManager::instance()->getDb() ) );
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
Dao::Impl::CUserPostCached::MEM_NODE_PTR Dao::Impl::CUserPostCached::getNagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    if( _nagtiveList.empty() )
    {
        Message::Db::Tables::TUserPost t;
        t.__init();
        bool isBegin = stmt->getConnection()->getTransaction()->isBegin();
        if( !isBegin )
        {
            stmt->getConnection()->begin( false );
        }
        CUserPostDaoImpl dao;
        while( (int)_nagtiveList.size() < getNagtiveCount() )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( ECachedUpdateModelAdd );
            dao.CUserPostDaoImplBase::save( t , stmt , false );
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
void Dao::Impl::CUserPostCached::__registToTx( 
	cdf::CTransaction* tx , 
	const TUserPostCached& table,
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
            Message::Db::Tables::TUserPost v;
            table.__save( v );
            nodePtr->setNode( v );
            _transactionNodes[tx][nodePtr->getNode().postId] = nodePtr;
        }
        else
        {
            MEM_NODE_MAP::iterator iter2 = iter->second.find( table.postId );
            if( iter2 == iter->second.end() )
            {
                MEM_NODE_PTR nodePtr = new MEM_NODE();
                nodePtr->setUpdateMode( model );
                Message::Db::Tables::TUserPost v;
                table.__save( v );
                nodePtr->setNode( v );
                iter->second[ table.postId ] = nodePtr;
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
        Message::Db::Tables::TUserPost v;
        table.__save( v );
        nodePtr->setNode( v );
        MEM_NODE_MAP::iterator iter = _flushMap.find( table.postId );
        if( iter == _flushMap.end() )
        {
            _flushMap[table.postId] = nodePtr;
        }
        else
        {
            iter->second = nodePtr;
        }
    }
}
void Dao::Impl::CUserPostCached::__update(
    TUserPostCached& v,
	const cdf::dao::SeqDataNode& seq 
	)
{
    cdf::dao::SeqDataNode::const_iterator iter;
    for( iter = seq.begin() ; iter != seq.end() ; iter ++ )
    {
        if( iter->getColumnName() == "user_id" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_user_post column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.userId = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "title" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_user_post column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.title = iter->getString();
            continue;
        }
        if( iter->getColumnName() == "content" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_user_post column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.content = iter->getString();
            continue;
        }
        if( iter->getColumnName() == "img_list" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_user_post column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.imgList = iter->getString();
            continue;
        }
        if( iter->getColumnName() == "nlike" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_user_post column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.nlike = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "ndislike" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_user_post column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.ndislike = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "ncomment" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_user_post column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.ncomment = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "post_dt" )
        {
            if( iter->getDataType() != cdf::TYPE_DATE )
            {
                std::string exp = "table name:t_user_post column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            cdf::CDateTime date( iter->getDate() );
            date.clearMillSecond();
            v.postDt = date.getTotalMill();
            continue;
        }
        std::string exp = "table name:t_user_post column name:" + iter->getColumnName() + " error";
        throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
    }
}