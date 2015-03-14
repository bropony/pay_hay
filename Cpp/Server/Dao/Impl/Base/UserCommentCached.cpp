#include "Dao/Impl/Base/UserCommentCached.h"
#include "Dao/Impl/UserCommentDaoImpl.h"
#include "framework/util/exception.h"
#include "framework/db/cached/cachedmanager.h"
#include "framework/db/cached/cachedtransaction.h"
#include "framework/log/loggerutil.h"

using namespace cdf;
using namespace cdf::dao;
using namespace cdf::cached;
using namespace Dao::Impl;
USE_FASTDB_NAMESPACE;

REGISTER( TUserCommentCached );
cdf::CAutoRun CUserCommentCached::_autoRun( CUserCommentCached::regist );

FASTDB_NS::dbFieldDescriptor* 
TUserCommentCached::dbDescribeComponents(FASTDB_NS::dbFieldDescriptor*)
{
    return
        &(
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("comment_id", (char*)&commentId-(char*)this , sizeof( commentId ), FASTDB_NS::HASHED | FASTDB_NS::INDEXED ), commentId),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("post_id", (char*)&postId-(char*)this , sizeof( postId ), FASTDB_NS::INDEXED ), postId),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("from_user_id", (char*)&fromUserId-(char*)this , sizeof( fromUserId ), 0 ), fromUserId),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("from_nickname", (char*)&fromNickname-(char*)this , sizeof( fromNickname ), 0 ), fromNickname),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("content", (char*)&content-(char*)this , sizeof( content ), 0 ), content),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("comment_dt", (char*)&commentDt-(char*)this , sizeof( commentDt ), 0 ), commentDt)
        );
    
}

void
TUserCommentCached::__update( const Message::Db::Tables::TUserComment& t )
{
    commentId = t.commentId;
    postId = t.postId;
    fromUserId = t.fromUserId;
    fromNickname = t.fromNickname;
    content = t.content;
    {
        cdf::CDateTime __date( t.commentDt );
        __date.clearMillSecond();
        commentDt = __date.getTotalMill();
    }
}

void
TUserCommentCached::__save( Message::Db::Tables::TUserComment& t ) const 
{
    t.commentId = commentId;
    t.postId = postId;
    t.fromUserId = fromUserId;
    t.fromNickname = fromNickname;
    t.content = content;
    t.commentDt.init( commentDt );
}

void Dao::Impl::CUserCommentCached::regist()
{
    static Dao::Impl::CUserCommentCached cached;
    cdf::cached::CCachedManager::instance()->registTableCached( "t_user_comment" , &cached );
}

bool Dao::Impl::CUserCommentCached::get( int id , Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool update )
{
    dbQuery q;
    q = "comment_id=",(id);
    dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

void Dao::Impl::CUserCommentCached::save( Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt1 = conn->createStatement();
    TUserCommentCached t;
    if( !isInsertOnly() )
    {
        conn->setCached( false );
        conn->begin( false );
        MEM_NODE_PTR nodePtr = getNagtive( stmt1.get() );
        conn->commit( false );
        v.commentId = nodePtr->getNode().commentId;
        t.__update( v );
        if( !isNagtiveOnly() )
        {
            dbAnyReference ref;
            CCachedManager::instance()->getDb().insertRecord( 
            	&TUserCommentCached::dbDescriptor , &ref , &t
            	);
        }
    }
    else
    {
        v.commentId = ++ _id;
        t.__update( v );
    }
    __registToTx( 
    	stmt->getConnection()->getTransaction() , 
    	t ,
    	cdf::cached::ECachedUpdateModelAdd
    	);
}

bool Dao::Impl::CUserCommentCached::update( const Message::Db::Tables::TUserComment& t , cdf::CStatement* stmt )
{
    dbQuery q;
    q = "comment_id=",(t.commentId);
    dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

long64_t Dao::Impl::CUserCommentCached::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt )
{
    dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

bool Dao::Impl::CUserCommentCached::remove( int id , cdf::CStatement* stmt )
{
    dbQuery q;
    q = "comment_id=",(id);
    dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

long64_t Dao::Impl::CUserCommentCached::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserComment& v , cdf::CStatement* stmt , bool update )
{
    v.clear();
    dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
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
        Message::Db::Tables::TUserComment table;
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

bool Dao::Impl::CUserCommentCached::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool update )
{
    dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

long64_t Dao::Impl::CUserCommentCached::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt )
{
    dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
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
            int id = cursor.get()->commentId;
            cursor.get()->__update( v );
            cursor.get()->commentId = id;
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

long64_t Dao::Impl::CUserCommentCached::remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt )
{
    dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
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

int Dao::Impl::CUserCommentCached::getTotalCount()
{
    dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
    return cursor.select( dbCursorViewOnly );
}

void Dao::Impl::CUserCommentCached::clear( cdf::CStatement* stmt )
{
    
    remove( cdf::dao::SeqCmpNode() , stmt );
}

void Dao::Impl::CUserCommentCached::load( cdf::CStatement* stmt )
{
    CUserCommentDaoImpl dao;
    cdf::dao::SQuery query;
    if ( !getNagtiveCheck().empty() )
    {
        cdf::dao::SCmpNode cmpNode;
        cmpNode.setColumnName( getNagtiveCheck() );
        cmpNode.setEqualType( cdf::dao::EQUAL_TYPE_NOT_EQUAL );
        bool canCheck = true;
        if ( getNagtiveCheck() == "comment_id" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "post_id" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "from_user_id" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "from_nickname" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "content" )
        {
            cmpNode.setString( "" );
        }
        else if ( getNagtiveCheck() == "comment_dt" )
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
    Message::Db::Tables::SeqTUserComment tables;
    TUserCommentCached table;
    dao.CUserCommentDaoImplBase::find( query , tables , stmt , false , false );
    Message::Db::Tables::SeqTUserComment::iterator iter;
    for( iter = tables.begin() ; iter != tables.end() ; iter ++ )
    {
        dbAnyReference ref;
        table.__update( *iter );
        CCachedManager::instance()->getDb().insertRecord( 
        &TUserCommentCached::dbDescriptor , &ref , &table
        );
    }
}

void Dao::Impl::CUserCommentCached::flush( cdf::CStatement* stmt )
{
    CUserCommentDaoImpl dao;
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
                    dao.CUserCommentDaoImplBase::save( iter->second->getNode() , stmt , false );
                }
                break;
                case ECachedUpdateModelUpdate:
                {
                    dao.CUserCommentDaoImplBase::update( iter->second->getNode() , stmt , false );
                }
                break;
                case ECachedUpdateModelDelete:
                {
                    dao.CUserCommentDaoImplBase::remove( iter->second->getNode().commentId , stmt , false );
                }
            }
        }
        CDE_END_TRY( __FILE__ , __LINE__ );
    }
}

void Dao::Impl::CUserCommentCached::rollback( cdf::CTransaction* tx )
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

void Dao::Impl::CUserCommentCached::commit( cdf::CTransaction* tx )
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

void Dao::Impl::CUserCommentCached::unnagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    CUserCommentDaoImpl dao;
    for( MEM_NODE_LIST::const_iterator iter = _nagtiveList.begin() ; iter != _nagtiveList.end() ; iter ++ )
    {
        dao.CUserCommentDaoImplBase::remove( (*iter)->getNode().commentId , stmt , false );
    }
    _nagtiveList.clear();
}
void Dao::Impl::CUserCommentCached::nagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    if( (int)_nagtiveList.size() <= ( getNagtiveCount() / 2 ) )
    {
        Message::Db::Tables::TUserComment t;
        t.__init();
        bool isBegin = stmt->getConnection()->getTransaction()->isBegin();
        if( !isBegin )
        {
            stmt->getConnection()->begin( false );
        }
        CUserCommentDaoImpl dao;
        while( (int)_nagtiveList.size() < getNagtiveCount() )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( ECachedUpdateModelAdd );
            dao.CUserCommentDaoImplBase::save( t , stmt , false );
            nodePtr->getNode().__update( t );
            _nagtiveList.push_back( nodePtr );
        }
        if( !isBegin )
        {
            stmt->getConnection()->commit( false );
        }
    }
}
void Dao::Impl::CUserCommentCached::cached( const cdf::dao::SQuery& query , cdf::CStatement* stmt )
{
    CUserCommentDaoImpl dao;
    Message::Db::Tables::SeqTUserComment tables;
    dao.CUserCommentDaoImplBase::find( query , tables , stmt , false , false );
    cached( tables );
}
void Dao::Impl::CUserCommentCached::cached( Message::Db::Tables::SeqTUserComment& tables )
{
    TUserCommentCached table;
    Message::Db::Tables::SeqTUserComment::const_iterator iter;
    for( iter = tables.begin() ; iter != tables.end() ; iter ++ )
    {
        dbQuery q;
        q = "comment_id=",(iter->commentId);
        dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
        if( cursor.select( q , dbCursorForUpdate ) == 0 )
        {
            dbAnyReference ref;
            table.__update( *iter );
            CCachedManager::instance()->getDb().insertRecord( &TUserCommentCached::dbDescriptor , &ref , &table );
        }
    }
}
void Dao::Impl::CUserCommentCached::evict( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt )
{
    dbCursor< TUserCommentCached > cursor( &( CCachedManager::instance()->getDb() ) );
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
Dao::Impl::CUserCommentCached::MEM_NODE_PTR Dao::Impl::CUserCommentCached::getNagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    if( _nagtiveList.empty() )
    {
        Message::Db::Tables::TUserComment t;
        t.__init();
        bool isBegin = stmt->getConnection()->getTransaction()->isBegin();
        if( !isBegin )
        {
            stmt->getConnection()->begin( false );
        }
        CUserCommentDaoImpl dao;
        while( (int)_nagtiveList.size() < getNagtiveCount() )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( ECachedUpdateModelAdd );
            dao.CUserCommentDaoImplBase::save( t , stmt , false );
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
void Dao::Impl::CUserCommentCached::__registToTx( 
	cdf::CTransaction* tx , 
	const TUserCommentCached& table,
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
            Message::Db::Tables::TUserComment v;
            table.__save( v );
            nodePtr->setNode( v );
            _transactionNodes[tx][nodePtr->getNode().commentId] = nodePtr;
        }
        else
        {
            MEM_NODE_MAP::iterator iter2 = iter->second.find( table.commentId );
            if( iter2 == iter->second.end() )
            {
                MEM_NODE_PTR nodePtr = new MEM_NODE();
                nodePtr->setUpdateMode( model );
                Message::Db::Tables::TUserComment v;
                table.__save( v );
                nodePtr->setNode( v );
                iter->second[ table.commentId ] = nodePtr;
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
        Message::Db::Tables::TUserComment v;
        table.__save( v );
        nodePtr->setNode( v );
        MEM_NODE_MAP::iterator iter = _flushMap.find( table.commentId );
        if( iter == _flushMap.end() )
        {
            _flushMap[table.commentId] = nodePtr;
        }
        else
        {
            iter->second = nodePtr;
        }
    }
}
void Dao::Impl::CUserCommentCached::__update(
    TUserCommentCached& v,
	const cdf::dao::SeqDataNode& seq 
	)
{
    cdf::dao::SeqDataNode::const_iterator iter;
    for( iter = seq.begin() ; iter != seq.end() ; iter ++ )
    {
        if( iter->getColumnName() == "post_id" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_user_comment column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.postId = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "from_user_id" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_user_comment column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.fromUserId = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "from_nickname" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_user_comment column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.fromNickname = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "content" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_user_comment column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.content = iter->getString();
            continue;
        }
        if( iter->getColumnName() == "comment_dt" )
        {
            if( iter->getDataType() != cdf::TYPE_DATE )
            {
                std::string exp = "table name:t_user_comment column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            cdf::CDateTime date( iter->getDate() );
            date.clearMillSecond();
            v.commentDt = date.getTotalMill();
            continue;
        }
        std::string exp = "table name:t_user_comment column name:" + iter->getColumnName() + " error";
        throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
    }
}