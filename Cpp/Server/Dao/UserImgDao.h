#ifndef _USERIMG_DAO_H_
#define _USERIMG_DAO_H_
#include "Dao/Base/UserImgDaoBase.h"
namespace Dao
{
    class IUserImgDao
            :public IUserImgDaoBase
    {
    public:
        IUserImgDao();
        virtual ~IUserImgDao();

		virtual void loadAllUserImg(Message::Db::Tables::SeqTUserImg & userImgList) = 0;
		virtual void updateUserImg(const Message::Db::Tables::TUserImg & t) = 0;
    };
}
#endif
