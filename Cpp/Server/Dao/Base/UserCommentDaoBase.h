#ifndef _USERCOMMENT_DAO_BASE_H_
#define _USERCOMMENT_DAO_BASE_H_
#include "Message/Db/Tables/TUserComment.h"
#include "framework/db/dao/daoquerydef.h"
#include "framework/db/cached/cacheddao.h"
namespace Dao
{
    class IUserCommentDaoBase
    {
    public:
        IUserCommentDaoBase();
        virtual ~IUserCommentDaoBase();
        virtual bool get( int id , Message::Db::Tables::TUserComment& v , bool update = false ) = 0;
        virtual void save( Message::Db::Tables::TUserComment& v ) = 0;
        virtual bool update( const Message::Db::Tables::TUserComment& v ) = 0;
        virtual bool remove( int id ) = 0;
        
        virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserComment& v , bool update = false ) = 0;
        virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserComment& v , bool update = false ) = 0;
        virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserComment& v) = 0;
        virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq ) = 0;
        virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp ) = 0;
        
        const static std::string _tableName;
        const static std::string _commentId;
        const static std::string _postId;
        const static std::string _fromUserId;
        const static std::string _fromNickname;
        const static std::string _content;
        const static std::string _commentDt;
    };
}
#endif
