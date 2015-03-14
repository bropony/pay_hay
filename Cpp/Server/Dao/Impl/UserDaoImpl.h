#ifndef _USER_DAO_IMPL_H_
#define _USER_DAO_IMPL_H_
#include "Dao/Impl/Base/UserDaoImplBase.h"
namespace Dao
{
    namespace Impl
    {
        class CUserDaoImpl
                :public CUserDaoImplBase
        {
        public:
            CUserDaoImpl();
            virtual ~CUserDaoImpl();

			virtual bool loadUser(int userId, Message::Db::Tables::TUser & tUser);
			virtual bool loadUser(const std::string & account, Message::Db::Tables::TUser & tUser);
			virtual void loadAllUsers(Message::Db::Tables::SeqTUser & allTUsers);

			virtual void updateUser(const Message::Db::Tables::TUser & tUser);
        };
    }
}
#endif
