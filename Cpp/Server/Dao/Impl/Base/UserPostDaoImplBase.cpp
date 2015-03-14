#include "Dao/Impl/Base/UserPostDaoImplBase.h"
#include "Dao/Impl/Base/UserPostCached.h"
#include "framework/db/cached/cachedmanager.h"

using namespace cdf;
using namespace cdf::dao;
Dao::Impl::CUserPostDaoImplBase::CUserPostDaoImplBase()

{
    _cached = dynamic_cast< Dao::Impl::CUserPostCached* >( cdf::cached::CCachedManager::instance()->getTableCached( "t_user_post" ) ); 
    
}
Dao::Impl::CUserPostDaoImplBase::~CUserPostDaoImplBase()
{
}

bool Dao::Impl::CUserPostDaoImplBase::get( int id , Message::Db::Tables::TUserPost& v , bool update )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return get( id , v , stmt.get() , update );
}

void Dao::Impl::CUserPostDaoImplBase::save( Message::Db::Tables::TUserPost& v )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    save( v , stmt.get() );
}

bool Dao::Impl::CUserPostDaoImplBase::update( const Message::Db::Tables::TUserPost& v )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( v , stmt.get() );
}

bool Dao::Impl::CUserPostDaoImplBase::remove( int id )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return remove( id , stmt.get() );
}

long64_t Dao::Impl::CUserPostDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserPost& v , bool update )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

bool Dao::Impl::CUserPostDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserPost& v , bool update  )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

long64_t Dao::Impl::CUserPostDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserPost& v)
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( cmp , v , stmt.get() );
}

long64_t Dao::Impl::CUserPostDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( cmp , seq , stmt.get() );
}

long64_t Dao::Impl::CUserPostDaoImplBase::remove( const cdf::dao::SeqCmpNode& cmp )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return remove( cmp , stmt.get() );
}

bool Dao::Impl::CUserPostDaoImplBase::get( int id , Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool update , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->get( id , v , stmt , update );
    }
    std::string sql = _selectBase + " where post_id = ?";
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    stmt->setInt( 1 , id );
    std::auto_ptr<CResultSet> rs = stmt->executeQuery();
    if( rs->next() )
    {
        __readTUserPost ( v , rs.get() );
        return true;
    }
    return false;
}

void Dao::Impl::CUserPostDaoImplBase::save( Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() )
    {
        _cached->save( v , stmt );
        return;
    }
    stmt->prepare( _insertBase.c_str() );
    __writeTUserPost( v , stmt );
    stmt->executeUpdate();
    v.postId = (int)stmt->getInsertID( "s_t_user_post" );
}

bool Dao::Impl::CUserPostDaoImplBase::update( const Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( v , stmt );
    }
    stmt->prepare( (_updateBase + " where post_id = ?").c_str() );
    __writeTUserPost( v , stmt );
    stmt->setInt( 9 , v.postId );
    return stmt->executeUpdate() > 0;
}

long64_t Dao::Impl::CUserPostDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( cmp , seq , stmt );
    }
    std::string sql = "update t_user_post";
    sql += makeUpdate( seq );
    sql += makeQuery( cmp );
    stmt->prepare( sql.c_str() );
    this->writeStmt( 1 , seq , stmt );
    this->writeStmt( (int)seq.size() + 1 , cmp , stmt );
    return stmt->executeUpdate();
}

bool Dao::Impl::CUserPostDaoImplBase::remove( int id , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->remove( id , stmt );
    }
    stmt->prepare( "delete from t_user_post where post_id = ? ");
    stmt->setInt( 1 , id );
    return stmt->executeUpdate() > 0;
}

long64_t Dao::Impl::CUserPostDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserPost& v , cdf::CStatement* stmt , bool update , bool usedCached )
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
        stmt->prepare( ("select count(*) as count1 from t_user_post" + sqlWhere ).c_str() );
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
    Message::Db::Tables::TUserPost node;
    while( rs->next() )
    {
        __readTUserPost( node , rs.get() );
        v.push_back( node );
    }
    return count;
}

bool Dao::Impl::CUserPostDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool update , bool usedCached )
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
        __readTUserPost( v , rs.get() );
        return true;
    }
    return false;
}

long64_t Dao::Impl::CUserPostDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( cmp , v , stmt );
    }
    stmt->prepare( ( _updateBase + makeQuery( cmp ) ).c_str() );
    __writeTUserPost( v , stmt );
    writeStmt( _columnCount , cmp , stmt );
    return stmt->executeUpdate();
}

long64_t Dao::Impl::CUserPostDaoImplBase::remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->remove( cmp , stmt );
    }
    stmt->prepare( ( "delete from t_user_post" + makeQuery( cmp ) ).c_str() );
    writeStmt( 1 , cmp , stmt );
    return stmt->executeUpdate();
}


const int Dao::Impl::CUserPostDaoImplBase::_columnCount = 9;

const std::string Dao::Impl::CUserPostDaoImplBase::_selectBase = 
"select post_id,user_id,title,content,img_list,nlike,ndislike,"
"ncomment,post_dt from t_user_post";

const std::string Dao::Impl::CUserPostDaoImplBase::_updateBase = 
"update t_user_post set user_id=?,title=?,content=?,img_list=?,"
"nlike=?,ndislike=?,ncomment=?,post_dt=?";

const std::string Dao::Impl::CUserPostDaoImplBase::_insertBase = 
"insert into t_user_post ( user_id,title,content,img_list,nlike,"
"ndislike,ncomment,post_dt) values (?,?,?,?,?,?,?,?)";

const std::string Dao::Impl::CUserPostDaoImplBase::_deleteBase = 
"delete from t_user_post";

void Dao::Impl::CUserPostDaoImplBase::__readTUserPost( Message::Db::Tables::TUserPost& outV , cdf::CResultSet* rs )
{
    outV.postId = rs->getInt( 1 );
    outV.userId = rs->getInt( 2 );
    outV.title = rs->getString( 3 );
    outV.content = rs->getString( 4 );
    outV.imgList = rs->getString( 5 );
    outV.nlike = rs->getInt( 6 );
    outV.ndislike = rs->getInt( 7 );
    outV.ncomment = rs->getInt( 8 );
    outV.postDt = rs->getDate( 9 );
}

void Dao::Impl::CUserPostDaoImplBase::__writeTUserPost( const Message::Db::Tables::TUserPost& inV , cdf::CStatement* stmt )
{
    stmt->setInt( 1 , inV.userId );
    stmt->setString( 2 , inV.title );
    stmt->setString( 3 , inV.content );
    stmt->setString( 4 , inV.imgList );
    stmt->setInt( 5 , inV.nlike );
    stmt->setInt( 6 , inV.ndislike );
    stmt->setInt( 7 , inV.ncomment );
    stmt->setDate( 8 , inV.postDt );
}

Dao::Impl::CUserPostCached* Dao::Impl::CUserPostDaoImplBase::getCached()
{
    return _cached;
}