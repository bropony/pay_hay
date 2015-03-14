#ifndef _USERPOST_DAO_BASE_H_
#define _USERPOST_DAO_BASE_H_
#include "Message/Db/Tables/TUserPost.h"
#include "framework/db/dao/daoquerydef.h"
#include "framework/db/cached/cacheddao.h"
namespace Dao
{
    class IUserPostDaoBase
    {
    public:
        IUserPostDaoBase();
        virtual ~IUserPostDaoBase();
        virtual bool get( int id , Message::Db::Tables::TUserPost& v , bool update = false ) = 0;
        virtual void save( Message::Db::Tables::TUserPost& v ) = 0;
        virtual bool update( const Message::Db::Tables::TUserPost& v ) = 0;
        virtual bool remove( int id ) = 0;
        
        virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserPost& v , bool update = false ) = 0;
        virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserPost& v , bool update = false ) = 0;
        virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserPost& v) = 0;
        virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq ) = 0;
        virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp ) = 0;
        
        const static std::string _tableName;
        const static std::string _postId;
        const static std::string _userId;
        const static std::string _title;
        const static std::string _content;
        const static std::string _imgList;
        const static std::string _nlike;
        const static std::string _ndislike;
        const static std::string _ncomment;
        const static std::string _postDt;
    };
}
#endif
