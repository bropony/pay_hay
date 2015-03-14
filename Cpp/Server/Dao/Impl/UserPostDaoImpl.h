#ifndef _USERPOST_DAO_IMPL_H_
#define _USERPOST_DAO_IMPL_H_
#include "Dao/Impl/Base/UserPostDaoImplBase.h"
namespace Dao
{
    namespace Impl
    {
        class CUserPostDaoImpl
                :public CUserPostDaoImplBase
        {
        public:
            CUserPostDaoImpl();
            virtual ~CUserPostDaoImpl();

			virtual void updateUserPost(const Message::Db::Tables::TUserPost & t);
			virtual bool loadAllUserPosts(Message::Db::Tables::SeqTUserPost & postList);
        };
    }
}
#endif
