#include "Dao/Base/UserDaoBase.h"
Dao::IUserDaoBase::IUserDaoBase()
{
}
Dao::IUserDaoBase::~IUserDaoBase()
{
}

const std::string Dao::IUserDaoBase::_tableName = "t_user";
const std::string Dao::IUserDaoBase::_userId = "user_id";
const std::string Dao::IUserDaoBase::_account = "account";
const std::string Dao::IUserDaoBase::_nickname = "nickname";
const std::string Dao::IUserDaoBase::_loginKey = "login_key";
const std::string Dao::IUserDaoBase::_createDt = "create_dt";