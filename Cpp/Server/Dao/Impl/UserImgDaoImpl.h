#ifndef _USERIMG_DAO_IMPL_H_
#define _USERIMG_DAO_IMPL_H_
#include "Dao/Impl/Base/UserImgDaoImplBase.h"
namespace Dao
{
    namespace Impl
    {
        class CUserImgDaoImpl
                :public CUserImgDaoImplBase
        {
        public:
            CUserImgDaoImpl();
            virtual ~CUserImgDaoImpl();

			virtual void loadAllUserImg(Message::Db::Tables::SeqTUserImg & userImgList);
			virtual void updateUserImg(const Message::Db::Tables::TUserImg & t);
        };
    }
}
#endif
