#include "Dao/Impl/Base/UserCommentDaoImplBase.h"
#include "Dao/Impl/Base/UserCommentCached.h"
#include "framework/db/cached/cachedmanager.h"

using namespace cdf;
using namespace cdf::dao;
Dao::Impl::CUserCommentDaoImplBase::CUserCommentDaoImplBase()

{
    _cached = dynamic_cast< Dao::Impl::CUserCommentCached* >( cdf::cached::CCachedManager::instance()->getTableCached( "t_user_comment" ) ); 
    
}
Dao::Impl::CUserCommentDaoImplBase::~CUserCommentDaoImplBase()
{
}

bool Dao::Impl::CUserCommentDaoImplBase::get( int id , Message::Db::Tables::TUserComment& v , bool update )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return get( id , v , stmt.get() , update );
}

void Dao::Impl::CUserCommentDaoImplBase::save( Message::Db::Tables::TUserComment& v )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    save( v , stmt.get() );
}

bool Dao::Impl::CUserCommentDaoImplBase::update( const Message::Db::Tables::TUserComment& v )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( v , stmt.get() );
}

bool Dao::Impl::CUserCommentDaoImplBase::remove( int id )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return remove( id , stmt.get() );
}

long64_t Dao::Impl::CUserCommentDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserComment& v , bool update )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

bool Dao::Impl::CUserCommentDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserComment& v , bool update  )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

long64_t Dao::Impl::CUserCommentDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserComment& v)
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( cmp , v , stmt.get() );
}

long64_t Dao::Impl::CUserCommentDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( cmp , seq , stmt.get() );
}

long64_t Dao::Impl::CUserCommentDaoImplBase::remove( const cdf::dao::SeqCmpNode& cmp )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return remove( cmp , stmt.get() );
}

bool Dao::Impl::CUserCommentDaoImplBase::get( int id , Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool update , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->get( id , v , stmt , update );
    }
    std::string sql = _selectBase + " where comment_id = ?";
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    stmt->setInt( 1 , id );
    std::auto_ptr<CResultSet> rs = stmt->executeQuery();
    if( rs->next() )
    {
        __readTUserComment ( v , rs.get() );
        return true;
    }
    return false;
}

void Dao::Impl::CUserCommentDaoImplBase::save( Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() )
    {
        _cached->save( v , stmt );
        return;
    }
    stmt->prepare( _insertBase.c_str() );
    __writeTUserComment( v , stmt );
    stmt->executeUpdate();
    v.commentId = (int)stmt->getInsertID( "s_t_user_comment" );
}

bool Dao::Impl::CUserCommentDaoImplBase::update( const Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( v , stmt );
    }
    stmt->prepare( (_updateBase + " where comment_id = ?").c_str() );
    __writeTUserComment( v , stmt );
    stmt->setInt( 6 , v.commentId );
    return stmt->executeUpdate() > 0;
}

long64_t Dao::Impl::CUserCommentDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( cmp , seq , stmt );
    }
    std::string sql = "update t_user_comment";
    sql += makeUpdate( seq );
    sql += makeQuery( cmp );
    stmt->prepare( sql.c_str() );
    this->writeStmt( 1 , seq , stmt );
    this->writeStmt( (int)seq.size() + 1 , cmp , stmt );
    return stmt->executeUpdate();
}

bool Dao::Impl::CUserCommentDaoImplBase::remove( int id , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->remove( id , stmt );
    }
    stmt->prepare( "delete from t_user_comment where comment_id = ? ");
    stmt->setInt( 1 , id );
    return stmt->executeUpdate() > 0;
}

long64_t Dao::Impl::CUserCommentDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserComment& v , cdf::CStatement* stmt , bool update , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->find( query , v , stmt , update );
    }
    v.clear();
    std::string sqlWhere = makeQuery( query.cmpNodes );
    long64_t count = 0;
    if( query.countType & FIND_COUNT_TYPE_WITH_COUNT )
    {
        stmt->prepare( ("select count(*) as count1 from t_user_comment" + sqlWhere ).c_str() );
        writeStmt( 1 , query.cmpNodes , stmt );
        std::auto_ptr<CResultSet> rs = stmt->executeQuery();
        if( rs->next() )
            count = rs->getLong64( 1 );
    }
    if( !(query.countType & FIND_COUNT_TYPE_WITH_DATA) )
        return count;
    std::string sql = _selectBase + sqlWhere + makeOrder( query );
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    writeStmt( 1 , query.cmpNodes , stmt );
    std::auto_ptr<CResultSet> rs = stmt->executeQuery();
    Message::Db::Tables::TUserComment node;
    while( rs->next() )
    {
        __readTUserComment( node , rs.get() );
        v.push_back( node );
    }
    return count;
}

bool Dao::Impl::CUserCommentDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool update , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->find( query , v , stmt , update );
    }
    std::string sqlWhere = makeQuery( query.cmpNodes );
    std::string sql = _selectBase + sqlWhere + makeOrder( query );
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    writeStmt( 1 , query.cmpNodes , stmt );
    std::auto_ptr<CResultSet> rs = stmt->executeQuery();
    if( rs->next() )
    {
        __readTUserComment( v , rs.get() );
        return true;
    }
    return false;
}

long64_t Dao::Impl::CUserCommentDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserComment& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( cmp , v , stmt );
    }
    stmt->prepare( ( _updateBase + makeQuery( cmp ) ).c_str() );
    __writeTUserComment( v , stmt );
    writeStmt( _columnCount , cmp , stmt );
    return stmt->executeUpdate();
}

long64_t Dao::Impl::CUserCommentDaoImplBase::remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->remove( cmp , stmt );
    }
    stmt->prepare( ( "delete from t_user_comment" + makeQuery( cmp ) ).c_str() );
    writeStmt( 1 , cmp , stmt );
    return stmt->executeUpdate();
}


const int Dao::Impl::CUserCommentDaoImplBase::_columnCount = 6;

const std::string Dao::Impl::CUserCommentDaoImplBase::_selectBase = 
"select comment_id,post_id,from_user_id,from_nickname,content,"
"comment_dt from t_user_comment";

const std::string Dao::Impl::CUserCommentDaoImplBase::_updateBase = 
"update t_user_comment set post_id=?,from_user_id=?,from_nickname=?,"
"content=?,comment_dt=?";

const std::string Dao::Impl::CUserCommentDaoImplBase::_insertBase = 
"insert into t_user_comment ( post_id,from_user_id,from_nickname,"
"content,comment_dt) values (?,?,?,?,?)";

const std::string Dao::Impl::CUserCommentDaoImplBase::_deleteBase = 
"delete from t_user_comment";

void Dao::Impl::CUserCommentDaoImplBase::__readTUserComment( Message::Db::Tables::TUserComment& outV , cdf::CResultSet* rs )
{
    outV.commentId = rs->getInt( 1 );
    outV.postId = rs->getInt( 2 );
    outV.fromUserId = rs->getInt( 3 );
    outV.fromNickname = rs->getInt( 4 );
    outV.content = rs->getString( 5 );
    outV.commentDt = rs->getDate( 6 );
}

void Dao::Impl::CUserCommentDaoImplBase::__writeTUserComment( const Message::Db::Tables::TUserComment& inV , cdf::CStatement* stmt )
{
    stmt->setInt( 1 , inV.postId );
    stmt->setInt( 2 , inV.fromUserId );
    stmt->setInt( 3 , inV.fromNickname );
    stmt->setString( 4 , inV.content );
    stmt->setDate( 5 , inV.commentDt );
}

Dao::Impl::CUserCommentCached* Dao::Impl::CUserCommentDaoImplBase::getCached()
{
    return _cached;
}