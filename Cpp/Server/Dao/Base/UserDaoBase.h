#ifndef _USER_DAO_BASE_H_
#define _USER_DAO_BASE_H_
#include "Message/Db/Tables/TUser.h"
#include "framework/db/dao/daoquerydef.h"
#include "framework/db/cached/cacheddao.h"
namespace Dao
{
    class IUserDaoBase
    {
    public:
        IUserDaoBase();
        virtual ~IUserDaoBase();
        virtual bool get( int id , Message::Db::Tables::TUser& v , bool update = false ) = 0;
        virtual void save( Message::Db::Tables::TUser& v ) = 0;
        virtual bool update( const Message::Db::Tables::TUser& v ) = 0;
        virtual bool remove( int id ) = 0;
        
        virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUser& v , bool update = false ) = 0;
        virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUser& v , bool update = false ) = 0;
        virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUser& v) = 0;
        virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq ) = 0;
        virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp ) = 0;
        
        const static std::string _tableName;
        const static std::string _userId;
        const static std::string _account;
        const static std::string _nickname;
        const static std::string _loginKey;
        const static std::string _createDt;
    };
}
#endif
