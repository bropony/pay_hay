#include "framework/util/stringfun.h"
#include "framework/util/typetransform.h"
#include "framework/encrypt/hashencrypt.h"

#include "User.h"
#include "Helper/Util.h"
#include "Db/DaoManager.h"

using namespace WebServerApp;

CUser::CUser(const Message::Db::Tables::TUser & tUser)
:_tUser(tUser), _wsConnectionPtr()
{

}

CUser::~CUser()
{

}

Message::Db::Tables::TUser & CUser::getTUser()
{
	return _tUser;
}

int CUser::getUserId()
{
	return _tUser.userId;
}

const std::string & CUser::getAccount()
{
	return _tUser.account;
}

const std::string & CUser::getNickname()
{
	return _tUser.nickname;
}

const std::string & CUser::getAvatar()
{
	return _avatar;
}

void CUser::updateAvatar(int imgId, const std::string & avatarImg)
{
	_tUser.avatar = imgId;
	_avatar = avatarImg;
}

bool CUser::isPasswdMatched(const std::string & passwd)
{
	if (passwd == _tUser.loginKey)
	{
		return true;
	}

	return false;
}

void CUser::setPasswd(const std::string & passwd)
{
	_tUser.loginKey = passwd;
}

const std::string & CUser::getSessionKey()
{
	return _sessionKey;
}

void CUser::updateSessionKey()
{
	//char buf[512] = { 0 };
	//char format[] = "Account=%s&RandInt=%d";
	//int randInt = rand();

	//int len = 0;
	//len = cdf_snprintf(
	//	buf,
	//	sizeof(buf) - 1,
	//	format,
	//	_tUser.account.c_str(),
	//	randInt
	//	);

	//_sessionKey = cdf::CStrFun::to_lower(cdf::CMd5Encrypt().hash(buf, len).c_str());
	_sessionKey = cdf::CStrFun::get_uuid();
}

bool CUser::isSessionKeyMatched(const std::string & sessionKey)
{
	if (_sessionKey.empty() ||
		_sessionKey != sessionKey)
	{
		return false;
	}

	return true;
}

WSConnectionPtr CUser::getWSConn()
{
	return _wsConnectionPtr;
}

void CUser::setWSConn(WSConnectionPtr conn)
{
	_wsConnectionPtr = conn;
}

void CUser::addPostId(int postId)
{
	_postIdList.push_back(postId);
}

void CUser::delPostId(int postId)
{
	auto found = std::find(_postIdList.begin(), _postIdList.end(), postId);
	if (found != _postIdList.end())
	{
		_postIdList.erase(found);
	}
}

void CUser::getNewer10PostId(int postId, Json::Value & jsList)
{
	Message::Public::SeqInt postIdList;

	getNewer10PostId(postId, postIdList);

	for (auto postId : postIdList)
	{
		jsList.append(postId);
	}
}

void CUser::getNewer10PostId(int postId, Message::Public::SeqInt & postIdList)
{
	Message::Public::SeqInt::size_type maxSize = 10;

	CUtil::getNewList(_postIdList, maxSize, postId, postIdList);
}

void CUser::getOlder10PostId(int postId, Json::Value & jsList)
{
	Message::Public::SeqInt postIdList;

	getOlder10PostId(postId, postIdList);

	for (auto postId : postIdList)
	{
		jsList.append(postId);
	}
}

void CUser::getOlder10PostId(int postId, Message::Public::SeqInt & postIdList)
{
	Message::Public::SeqInt::size_type maxSize = 10;

	CUtil::getOldList(_postIdList, maxSize, postId, postIdList);
}


void CUser::updateToDb()
{
	CDaoManager::instance()->getIUserDao()->updateUser(_tUser);
}
