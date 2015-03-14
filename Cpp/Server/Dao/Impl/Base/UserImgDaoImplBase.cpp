#include "Dao/Impl/Base/UserImgDaoImplBase.h"
#include "Dao/Impl/Base/UserImgCached.h"
#include "framework/db/cached/cachedmanager.h"

using namespace cdf;
using namespace cdf::dao;
Dao::Impl::CUserImgDaoImplBase::CUserImgDaoImplBase()

{
    _cached = dynamic_cast< Dao::Impl::CUserImgCached* >( cdf::cached::CCachedManager::instance()->getTableCached( "t_user_img" ) ); 
    
}
Dao::Impl::CUserImgDaoImplBase::~CUserImgDaoImplBase()
{
}

bool Dao::Impl::CUserImgDaoImplBase::get( int id , Message::Db::Tables::TUserImg& v , bool update )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return get( id , v , stmt.get() , update );
}

void Dao::Impl::CUserImgDaoImplBase::save( Message::Db::Tables::TUserImg& v )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    save( v , stmt.get() );
}

bool Dao::Impl::CUserImgDaoImplBase::update( const Message::Db::Tables::TUserImg& v )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( v , stmt.get() );
}

bool Dao::Impl::CUserImgDaoImplBase::remove( int id )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return remove( id , stmt.get() );
}

long64_t Dao::Impl::CUserImgDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserImg& v , bool update )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

bool Dao::Impl::CUserImgDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserImg& v , bool update  )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

long64_t Dao::Impl::CUserImgDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserImg& v)
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( cmp , v , stmt.get() );
}

long64_t Dao::Impl::CUserImgDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( cmp , seq , stmt.get() );
}

long64_t Dao::Impl::CUserImgDaoImplBase::remove( const cdf::dao::SeqCmpNode& cmp )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return remove( cmp , stmt.get() );
}

bool Dao::Impl::CUserImgDaoImplBase::get( int id , Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool update , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->get( id , v , stmt , update );
    }
    std::string sql = _selectBase + " where img_id = ?";
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    stmt->setInt( 1 , id );
    std::auto_ptr<CResultSet> rs = stmt->executeQuery();
    if( rs->next() )
    {
        __readTUserImg ( v , rs.get() );
        return true;
    }
    return false;
}

void Dao::Impl::CUserImgDaoImplBase::save( Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() )
    {
        _cached->save( v , stmt );
        return;
    }
    stmt->prepare( _insertBase.c_str() );
    __writeTUserImg( v , stmt );
    stmt->executeUpdate();
    v.imgId = (int)stmt->getInsertID( "s_t_user_img" );
}

bool Dao::Impl::CUserImgDaoImplBase::update( const Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( v , stmt );
    }
    stmt->prepare( (_updateBase + " where img_id = ?").c_str() );
    __writeTUserImg( v , stmt );
    stmt->setInt( 3 , v.imgId );
    return stmt->executeUpdate() > 0;
}

long64_t Dao::Impl::CUserImgDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( cmp , seq , stmt );
    }
    std::string sql = "update t_user_img";
    sql += makeUpdate( seq );
    sql += makeQuery( cmp );
    stmt->prepare( sql.c_str() );
    this->writeStmt( 1 , seq , stmt );
    this->writeStmt( (int)seq.size() + 1 , cmp , stmt );
    return stmt->executeUpdate();
}

bool Dao::Impl::CUserImgDaoImplBase::remove( int id , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->remove( id , stmt );
    }
    stmt->prepare( "delete from t_user_img where img_id = ? ");
    stmt->setInt( 1 , id );
    return stmt->executeUpdate() > 0;
}

long64_t Dao::Impl::CUserImgDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserImg& v , cdf::CStatement* stmt , bool update , bool usedCached )
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
        stmt->prepare( ("select count(*) as count1 from t_user_img" + sqlWhere ).c_str() );
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
    Message::Db::Tables::TUserImg node;
    while( rs->next() )
    {
        __readTUserImg( node , rs.get() );
        v.push_back( node );
    }
    return count;
}

bool Dao::Impl::CUserImgDaoImplBase::find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool update , bool usedCached )
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
        __readTUserImg( v , rs.get() );
        return true;
    }
    return false;
}

long64_t Dao::Impl::CUserImgDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserImg& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( cmp , v , stmt );
    }
    stmt->prepare( ( _updateBase + makeQuery( cmp ) ).c_str() );
    __writeTUserImg( v , stmt );
    writeStmt( _columnCount , cmp , stmt );
    return stmt->executeUpdate();
}

long64_t Dao::Impl::CUserImgDaoImplBase::remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->remove( cmp , stmt );
    }
    stmt->prepare( ( "delete from t_user_img" + makeQuery( cmp ) ).c_str() );
    writeStmt( 1 , cmp , stmt );
    return stmt->executeUpdate();
}


const int Dao::Impl::CUserImgDaoImplBase::_columnCount = 3;

const std::string Dao::Impl::CUserImgDaoImplBase::_selectBase = 
"select img_id,img_path,short_desc from t_user_img";

const std::string Dao::Impl::CUserImgDaoImplBase::_updateBase = 
"update t_user_img set img_path=?,short_desc=?";

const std::string Dao::Impl::CUserImgDaoImplBase::_insertBase = 
"insert into t_user_img ( img_path,short_desc) values (?,?)";

const std::string Dao::Impl::CUserImgDaoImplBase::_deleteBase = 
"delete from t_user_img";

void Dao::Impl::CUserImgDaoImplBase::__readTUserImg( Message::Db::Tables::TUserImg& outV , cdf::CResultSet* rs )
{
    outV.imgId = rs->getInt( 1 );
    outV.imgPath = rs->getString( 2 );
    outV.shortDesc = rs->getString( 3 );
}

void Dao::Impl::CUserImgDaoImplBase::__writeTUserImg( const Message::Db::Tables::TUserImg& inV , cdf::CStatement* stmt )
{
    stmt->setString( 1 , inV.imgPath );
    stmt->setString( 2 , inV.shortDesc );
}

Dao::Impl::CUserImgCached* Dao::Impl::CUserImgDaoImplBase::getCached()
{
    return _cached;
}