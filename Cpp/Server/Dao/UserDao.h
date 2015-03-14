#ifndef _USER_DAO_H_
#define _USER_DAO_H_
#include "Dao/Base/UserDaoBase.h"
namespace Dao
{
    class IUserDao
            :public IUserDaoBase
    {
    public:
        IUserDao();
        virtual ~IUserDao();

		virtual bool loadUser(int userId, Message::Db::Tables::TUser & tUser) = 0;
		virtual bool loadUser(const std::string & account, Message::Db::Tables::TUser & tUser) = 0;
		virtual void loadAllUsers(Message::Db::Tables::SeqTUser & allTUsers) = 0;

		virtual void updateUser(const Message::Db::Tables::TUser & tUser) = 0;
    };
}
#endif
