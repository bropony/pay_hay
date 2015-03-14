#ifndef _USERCOMMENT_DAO_H_
#define _USERCOMMENT_DAO_H_
#include "Dao/Base/UserCommentDaoBase.h"
namespace Dao
{
    class IUserCommentDao
            :public IUserCommentDaoBase
    {
    public:
        IUserCommentDao();
        virtual ~IUserCommentDao();

		virtual bool loadUserComment(int postId, Message::Db::Tables::SeqTUserComment & allUserComments) = 0;
		virtual void updateUserComment(const Message::Db::Tables::TUserComment & t) = 0;
    };
}
#endif
