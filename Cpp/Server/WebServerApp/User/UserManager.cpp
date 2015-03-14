#include "UserManager.h"

#include "Db/DaoManager.h"

using namespace WebServerApp;

CUserManager::CUserManager()
{

}

CUserManager::~CUserManager()
{

}

CUserManager * CUserManager::instance()
{
	static CUserManager _inst;

	return &_inst;
}

void CUserManager::loadUsers()
{
	Message::Db::Tables::SeqTUser allTUsers;
	CDaoManager::instance()->getIUserDao()->loadAllUsers(allTUsers);

	for (const auto tUser : allTUsers)
	{
		if (tUser.account.empty())
		{
			continue;
		}

		CUserPtr userPtr = new CUser(tUser);
		addUser(userPtr);
	}
}

const CUserPtr CUserManager::findUser(int userId)
{
	const auto found = _mapIdUser.find(userId);
	if (found == _mapIdUser.end())
	{
		return NULL;
	}

	return found->second;
}

const CUserPtr CUserManager::findUser(const std::string & account)
{
	const auto found = _mapAccountUser.find(account);
	if (found == _mapAccountUser.end())
	{
		return NULL;
	}

	return found->second;
}

const CUserPtr CUserManager::findUserByNickname(const std::string & nickname)
{
	const auto found = _mapNicknameUser.find(nickname);
	
	if (found == _mapNicknameUser.end())
	{
		return NULL;
	}

	return found->second;
}

bool CUserManager::hasUserExisted(const std::string & account)
{
	const auto found = _mapAccountUser.find(account);
	if (found == _mapAccountUser.end())
	{
		return false;
	}

	return true;
}

bool CUserManager::hasUserExistedByNickname(const std::string & nickname)
{
	const auto found = _mapNicknameUser.find(nickname);

	if (found == _mapNicknameUser.end())
	{
		return false;
	}

	return true;
}

const CUserPtr CUserManager::createUser(const std::string & account, const std::string & nickname, const std::string & passwd)
{
	Message::Db::Tables::TUser tUser;
	tUser.account = account;
	tUser.nickname = nickname;
	tUser.loginKey = passwd;
	tUser.createDt = cdf::CDateTime();

	CDF_LOG_DEBUG("Now: " << tUser.createDt.getTotalDay());

	CUserPtr newUser = new CUser(tUser);
	addUser(newUser);
	newUser->updateToDb();

	return newUser;
}

void CUserManager::addUser(const CUserPtr & user)
{
	if (NULL == findUser(user->getUserId()))
	{
		_mapIdUser[user->getUserId()] = user;
		_mapAccountUser[user->getAccount()] = user;
		_mapNicknameUser[user->getNickname()] = user;
	}
}

void CUserManager::addPostId(int userId, int postId)
{
	auto found = _mapIdUser.find(userId);

	if (found != _mapIdUser.end())
	{
		found->second->addPostId(postId);
	}
}
