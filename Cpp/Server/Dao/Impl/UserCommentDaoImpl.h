#ifndef _USERCOMMENT_DAO_IMPL_H_
#define _USERCOMMENT_DAO_IMPL_H_
#include "Dao/Impl/Base/UserCommentDaoImplBase.h"
namespace Dao
{
    namespace Impl
    {
        class CUserCommentDaoImpl
                :public CUserCommentDaoImplBase
        {
        public:
            CUserCommentDaoImpl();
            virtual ~CUserCommentDaoImpl();

			virtual void updateUserComment(const Message::Db::Tables::TUserComment & t);
			virtual bool loadUserComment(int postId, Message::Db::Tables::SeqTUserComment & allUserComments);
        };
    }
}
#endif
