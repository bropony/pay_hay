#include "Dao/Impl/Base/UserDaoImplBase.h"
#include "Dao/Impl/Base/UserCached.h"
#include "framework/db/cached/cachedmanager.h"

using namespace cdf;
using namespace cdf::dao;
Dao::Impl::CUserDaoImplBase::CUserDaoImplBase()

{
    _cached = dynamic_cast< Dao::Impl::CUserCached* >( cdf::cached::CCachedManager::instance()->getTableCached( "t_user" ) ); 
    
}
Dao::Impl::CUserDaoImplBase::~CUserDaoImplBase()
{
}

bool Dao::Impl::CUserDaoImplBase::get( int id , Message::Db::Tables::TUser& v , bool update )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return get( id , v , stmt.get() , update );
}

void Dao::Impl::CUserDaoImplBase::save( Message::Db::Tables::TUser& v )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    save( v , stmt.get() );
}

bool Dao::Impl::CUserDaoImplBase::update( const Message::Db::Tables::TUser& v )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( v , stmt.get() );
}

bool Dao::Impl::CUserDaoImplBase::remove( int id )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return remove( id , stmt.get() );
}

long64_t Dao::Impl::CUserDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUser& v , bool update )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

bool Dao::Impl::CUserDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUser& v , bool update  )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

long64_t Dao::Impl::CUserDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUser& v)
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( cmp , v , stmt.get() );
}

long64_t Dao::Impl::CUserDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( cmp , seq , stmt.get() );
}

long64_t Dao::Impl::CUserDaoImplBase::remove( const cdf::dao::SeqCmpNode& cmp )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return remove( cmp , stmt.get() );
}

bool Dao::Impl::CUserDaoImplBase::get( int id , Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool update , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->get( id , v , stmt , update );
    }
    std::string sql = _selectBase + " where user_id = ?";
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    stmt->setInt( 1 , id );
    std::auto_ptr<CResultSet> rs = stmt->executeQuery();
    if( rs->next() )
    {
        __readTUser ( v , rs.get() );
        return true;
    }
    return false;
}

void Dao::Impl::CUserDaoImplBase::save( Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() )
    {
        _cached->save( v , stmt );
        return;
    }
    stmt->prepare( _insertBase.c_str() );
    __writeTUser( v , stmt );
    stmt->executeUpdate();
    v.userId = (int)stmt->getInsertID( "s_t_user" );
}

bool Dao::Impl::CUserDaoImplBase::update( const Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( v , stmt );
    }
    stmt->prepare( (_updateBase + " where user_id = ?").c_str() );
    __writeTUser( v , stmt );
    stmt->setInt( 5 , v.userId );
    return stmt->executeUpdate() > 0;
}

long64_t Dao::Impl::CUserDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( cmp , seq , stmt );
    }
    std::string sql = "update t_user";
    sql += makeUpdate( seq );
    sql += makeQuery( cmp );
    stmt->prepare( sql.c_str() );
    this->writeStmt( 1 , seq , stmt );
    this->writeStmt( (int)seq.size() + 1 , cmp , stmt );
    return stmt->executeUpdate();
}

bool Dao::Impl::CUserDaoImplBase::remove( int id , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->remove( id , stmt );
    }
    stmt->prepare( "delete from t_user where user_id = ? ");
    stmt->setInt( 1 , id );
    return stmt->executeUpdate() > 0;
}

long64_t Dao::Impl::CUserDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUser& v , cdf::CStatement* stmt , bool update , bool usedCached )
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
        stmt->prepare( ("select count(*) as count1 from t_user" + sqlWhere ).c_str() );
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
    Message::Db::Tables::TUser node;
    while( rs->next() )
    {
        __readTUser( node , rs.get() );
        v.push_back( node );
    }
    return count;
}

bool Dao::Impl::CUserDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool update , bool usedCached )
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
        __readTUser( v , rs.get() );
        return true;
    }
    return false;
}

long64_t Dao::Impl::CUserDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUser& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( cmp , v , stmt );
    }
    stmt->prepare( ( _updateBase + makeQuery( cmp ) ).c_str() );
    __writeTUser( v , stmt );
    writeStmt( _columnCount , cmp , stmt );
    return stmt->executeUpdate();
}

long64_t Dao::Impl::CUserDaoImplBase::remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->remove( cmp , stmt );
    }
    stmt->prepare( ( "delete from t_user" + makeQuery( cmp ) ).c_str() );
    writeStmt( 1 , cmp , stmt );
    return stmt->executeUpdate();
}


const int Dao::Impl::CUserDaoImplBase::_columnCount = 5;

const std::string Dao::Impl::CUserDaoImplBase::_selectBase = 
"select user_id,account,nickname,login_key,create_dt from t_user";

const std::string Dao::Impl::CUserDaoImplBase::_updateBase = 
"update t_user set account=?,nickname=?,login_key=?,create_dt=?";

const std::string Dao::Impl::CUserDaoImplBase::_insertBase = 
"insert into t_user ( account,nickname,login_key,create_dt) values ("
"?,?,?,?)";

const std::string Dao::Impl::CUserDaoImplBase::_deleteBase = 
"delete from t_user";

void Dao::Impl::CUserDaoImplBase::__readTUser( Message::Db::Tables::TUser& outV , cdf::CResultSet* rs )
{
    outV.userId = rs->getInt( 1 );
    outV.account = rs->getString( 2 );
    outV.nickname = rs->getString( 3 );
    outV.loginKey = rs->getString( 4 );
    outV.createDt = rs->getDate( 5 );
}

void Dao::Impl::CUserDaoImplBase::__writeTUser( const Message::Db::Tables::TUser& inV , cdf::CStatement* stmt )
{
    stmt->setString( 1 , inV.account );
    stmt->setString( 2 , inV.nickname );
    stmt->setString( 3 , inV.loginKey );
    stmt->setDate( 4 , inV.createDt );
}

Dao::Impl::CUserCached* Dao::Impl::CUserDaoImplBase::getCached()
{
    return _cached;
}