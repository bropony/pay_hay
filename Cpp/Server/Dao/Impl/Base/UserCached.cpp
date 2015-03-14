#include "Dao/Impl/Base/UserCached.h"
#include "Dao/Impl/UserDaoImpl.h"
#include "framework/util/exception.h"
#include "framework/db/cached/cachedmanager.h"
#include "framework/db/cached/cachedtransaction.h"
#include "framework/log/loggerutil.h"

using namespace cdf;
using namespace cdf::dao;
using namespace cdf::cached;
using namespace Dao::Impl;
USE_FASTDB_NAMESPACE;

REGISTER( TUserCached );
cdf::CAutoRun CUserCached::_autoRun( CUserCached::regist );

FASTDB_NS::dbFieldDescriptor* 
TUserCached::dbDescribeComponents(FASTDB_NS::dbFieldDescriptor*)
{
    return
        &(
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("user_id", (char*)&userId-(char*)this , sizeof( userId ), FASTDB_NS::HASHED | FASTDB_NS::INDEXED ), userId),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("account", (char*)&account-(char*)this , sizeof( account ), FASTDB_NS::INDEXED ), account),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("nickname", (char*)&nickname-(char*)this , sizeof( nickname ), 0 ), nickname),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("login_key", (char*)&loginKey-(char*)this , sizeof( loginKey ), 0 ), loginKey),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("create_dt", (char*)&createDt-(char*)this , sizeof( createDt ), 0 ), createDt)
        );
    
}

void
TUserCached::__update( const Message::Db::Tables::TUser& t )
{
    userId = t.userId;
    account = t.account;
    nickname = t.nickname;
    loginKey = t.loginKey;
    {
        cdf::CDateTime __date( t.createDt );
        __date.clearMillSecond();
        createDt = __date.getTotalMill();
    }
}

void
TUserCached::__save( Message::Db::Tables::TUser& t ) const 
{
    t.userId = userId;
    t.account = account;
    t.nickname = nickname;
    t.loginKey = loginKey;
    t.createDt.init( createDt );
}

void Dao::Impl::CUserCached::regist()
{
    static Dao::Impl::CUserCached cached;
    cdf::cached::CCachedManager::instance()->registTableCached( "t_user" , &cached );
}

bool Dao::Impl::CUserCached::get( int id , Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool update )
{
    dbQuery q;
    q = "user_id=",(id);
    dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

void Dao::Impl::CUserCached::save( Message::Db::Tables::TUser& v , cdf::CStatement* stmt )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt1 = conn->createStatement();
    TUserCached t;
    if( !isInsertOnly() )
    {
        conn->setCached( false );
        conn->begin( false );
        MEM_NODE_PTR nodePtr = getNagtive( stmt1.get() );
        conn->commit( false );
        v.userId = nodePtr->getNode().userId;
        t.__update( v );
        if( !isNagtiveOnly() )
        {
            dbAnyReference ref;
            CCachedManager::instance()->getDb().insertRecord( 
            	&TUserCached::dbDescriptor , &ref , &t
            	);
        }
    }
    else
    {
        v.userId = ++ _id;
        t.__update( v );
    }
    __registToTx( 
    	stmt->getConnection()->getTransaction() , 
    	t ,
    	cdf::cached::ECachedUpdateModelAdd
    	);
}

bool Dao::Impl::CUserCached::update( const Message::Db::Tables::TUser& t , cdf::CStatement* stmt )
{
    dbQuery q;
    q = "user_id=",(t.userId);
    dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

long64_t Dao::Impl::CUserCached::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt )
{
    dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

bool Dao::Impl::CUserCached::remove( int id , cdf::CStatement* stmt )
{
    dbQuery q;
    q = "user_id=",(id);
    dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

long64_t Dao::Impl::CUserCached::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUser& v , cdf::CStatement* stmt , bool update )
{
    v.clear();
    dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
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
        Message::Db::Tables::TUser table;
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

bool Dao::Impl::CUserCached::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool update )
{
    dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

long64_t Dao::Impl::CUserCached::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUser& v , cdf::CStatement* stmt )
{
    dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
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
            int id = cursor.get()->userId;
            cursor.get()->__update( v );
            cursor.get()->userId = id;
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

long64_t Dao::Impl::CUserCached::remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt )
{
    dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

int Dao::Impl::CUserCached::getTotalCount()
{
    dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
    return cursor.select( dbCursorViewOnly );
}

void Dao::Impl::CUserCached::clear( cdf::CStatement* stmt )
{
    
    remove( cdf::dao::SeqCmpNode() , stmt );
}

void Dao::Impl::CUserCached::load( cdf::CStatement* stmt )
{
    CUserDaoImpl dao;
    cdf::dao::SQuery query;
    if ( !getNagtiveCheck().empty() )
    {
        cdf::dao::SCmpNode cmpNode;
        cmpNode.setColumnName( getNagtiveCheck() );
        cmpNode.setEqualType( cdf::dao::EQUAL_TYPE_NOT_EQUAL );
        bool canCheck = true;
        if ( getNagtiveCheck() == "user_id" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "account" )
        {
            cmpNode.setString( "" );
        }
        else if ( getNagtiveCheck() == "nickname" )
        {
            cmpNode.setString( "" );
        }
        else if ( getNagtiveCheck() == "login_key" )
        {
            cmpNode.setString( "" );
        }
        else if ( getNagtiveCheck() == "create_dt" )
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
    Message::Db::Tables::SeqTUser tables;
    TUserCached table;
    dao.CUserDaoImplBase::find( query , tables , stmt , false , false );
    Message::Db::Tables::SeqTUser::iterator iter;
    for( iter = tables.begin() ; iter != tables.end() ; iter ++ )
    {
        dbAnyReference ref;
        table.__update( *iter );
        CCachedManager::instance()->getDb().insertRecord( 
        &TUserCached::dbDescriptor , &ref , &table
        );
    }
}

void Dao::Impl::CUserCached::flush( cdf::CStatement* stmt )
{
    CUserDaoImpl dao;
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
                    dao.CUserDaoImplBase::save( iter->second->getNode() , stmt , false );
                }
                break;
                case ECachedUpdateModelUpdate:
                {
                    dao.CUserDaoImplBase::update( iter->second->getNode() , stmt , false );
                }
                break;
                case ECachedUpdateModelDelete:
                {
                    dao.CUserDaoImplBase::remove( iter->second->getNode().userId , stmt , false );
                }
            }
        }
        CDE_END_TRY( __FILE__ , __LINE__ );
    }
}

void Dao::Impl::CUserCached::rollback( cdf::CTransaction* tx )
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

void Dao::Impl::CUserCached::commit( cdf::CTransaction* tx )
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

void Dao::Impl::CUserCached::unnagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    CUserDaoImpl dao;
    for( MEM_NODE_LIST::const_iterator iter = _nagtiveList.begin() ; iter != _nagtiveList.end() ; iter ++ )
    {
        dao.CUserDaoImplBase::remove( (*iter)->getNode().userId , stmt , false );
    }
    _nagtiveList.clear();
}
void Dao::Impl::CUserCached::nagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    if( (int)_nagtiveList.size() <= ( getNagtiveCount() / 2 ) )
    {
        Message::Db::Tables::TUser t;
        t.__init();
        bool isBegin = stmt->getConnection()->getTransaction()->isBegin();
        if( !isBegin )
        {
            stmt->getConnection()->begin( false );
        }
        CUserDaoImpl dao;
        while( (int)_nagtiveList.size() < getNagtiveCount() )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( ECachedUpdateModelAdd );
            dao.CUserDaoImplBase::save( t , stmt , false );
            nodePtr->getNode().__update( t );
            _nagtiveList.push_back( nodePtr );
        }
        if( !isBegin )
        {
            stmt->getConnection()->commit( false );
        }
    }
}
void Dao::Impl::CUserCached::cached( const cdf::dao::SQuery& query , cdf::CStatement* stmt )
{
    CUserDaoImpl dao;
    Message::Db::Tables::SeqTUser tables;
    dao.CUserDaoImplBase::find( query , tables , stmt , false , false );
    cached( tables );
}
void Dao::Impl::CUserCached::cached( Message::Db::Tables::SeqTUser& tables )
{
    TUserCached table;
    Message::Db::Tables::SeqTUser::const_iterator iter;
    for( iter = tables.begin() ; iter != tables.end() ; iter ++ )
    {
        dbQuery q;
        q = "user_id=",(iter->userId);
        dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
        if( cursor.select( q , dbCursorForUpdate ) == 0 )
        {
            dbAnyReference ref;
            table.__update( *iter );
            CCachedManager::instance()->getDb().insertRecord( &TUserCached::dbDescriptor , &ref , &table );
        }
    }
}
void Dao::Impl::CUserCached::evict( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt )
{
    dbCursor< TUserCached > cursor( &( CCachedManager::instance()->getDb() ) );
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
Dao::Impl::CUserCached::MEM_NODE_PTR Dao::Impl::CUserCached::getNagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    if( _nagtiveList.empty() )
    {
        Message::Db::Tables::TUser t;
        t.__init();
        bool isBegin = stmt->getConnection()->getTransaction()->isBegin();
        if( !isBegin )
        {
            stmt->getConnection()->begin( false );
        }
        CUserDaoImpl dao;
        while( (int)_nagtiveList.size() < getNagtiveCount() )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( ECachedUpdateModelAdd );
            dao.CUserDaoImplBase::save( t , stmt , false );
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
void Dao::Impl::CUserCached::__registToTx( 
	cdf::CTransaction* tx , 
	const TUserCached& table,
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
            Message::Db::Tables::TUser v;
            table.__save( v );
            nodePtr->setNode( v );
            _transactionNodes[tx][nodePtr->getNode().userId] = nodePtr;
        }
        else
        {
            MEM_NODE_MAP::iterator iter2 = iter->second.find( table.userId );
            if( iter2 == iter->second.end() )
            {
                MEM_NODE_PTR nodePtr = new MEM_NODE();
                nodePtr->setUpdateMode( model );
                Message::Db::Tables::TUser v;
                table.__save( v );
                nodePtr->setNode( v );
                iter->second[ table.userId ] = nodePtr;
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
        Message::Db::Tables::TUser v;
        table.__save( v );
        nodePtr->setNode( v );
        MEM_NODE_MAP::iterator iter = _flushMap.find( table.userId );
        if( iter == _flushMap.end() )
        {
            _flushMap[table.userId] = nodePtr;
        }
        else
        {
            iter->second = nodePtr;
        }
    }
}
void Dao::Impl::CUserCached::__update(
    TUserCached& v,
	const cdf::dao::SeqDataNode& seq 
	)
{
    cdf::dao::SeqDataNode::const_iterator iter;
    for( iter = seq.begin() ; iter != seq.end() ; iter ++ )
    {
        if( iter->getColumnName() == "account" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_user column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.account = iter->getString();
            continue;
        }
        if( iter->getColumnName() == "nickname" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_user column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.nickname = iter->getString();
            continue;
        }
        if( iter->getColumnName() == "login_key" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_user column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.loginKey = iter->getString();
            continue;
        }
        if( iter->getColumnName() == "create_dt" )
        {
            if( iter->getDataType() != cdf::TYPE_DATE )
            {
                std::string exp = "table name:t_user column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            cdf::CDateTime date( iter->getDate() );
            date.clearMillSecond();
            v.createDt = date.getTotalMill();
            continue;
        }
        std::string exp = "table name:t_user column name:" + iter->getColumnName() + " error";
        throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
    }
}