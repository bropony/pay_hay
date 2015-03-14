#ifndef _USERPOST_DAO_H_
#define _USERPOST_DAO_H_
#include "Dao/Base/UserPostDaoBase.h"
namespace Dao
{
    class IUserPostDao
            :public IUserPostDaoBase
    {
    public:
        IUserPostDao();
        virtual ~IUserPostDao();

		virtual void updateUserPost(const Message::Db::Tables::TUserPost & t) = 0;
		virtual bool loadAllUserPosts(Message::Db::Tables::SeqTUserPost & postList) = 0;
    };
}
#endif
