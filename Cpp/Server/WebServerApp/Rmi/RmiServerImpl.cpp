#include "RmiServerImpl.h"
#include "Config/ErrorCodeManager.h"
#include "Resource/ImageManager.h"
#include "Resource/PostManager.h"

#include "User/UserManager.h"
#include "User/UserHelper.h"

using namespace Rmi;
using namespace WebServerApp;

void CRmiServerImpl::login(std::string & account, std::string & passwd, const CLoginCallbackPtr & loginCB)
{
	CUserPtr user = CUserManager::instance()->findUser(account);
	if (NULL == user ||
		!user->isPasswdMatched(passwd))
	{
		CErrorCodeManager::throwException("Error_accountOrPasswd");
	}

	CUserManager::instance()->updateUserSessionKey(user);

	SLoginReturn userInfo;
	userInfo.userId = user->getUserId();
	userInfo.nickname = user->getNickname();
	userInfo.sessionKey = user->getSessionKey();
	userInfo.avatar = user->getAvatar();

	loginCB->response(userInfo);

	loginCB->getContext()->setUserObject(user);
}

void CRmiServerImpl::signup(std::string & account, std::string & passwd, std::string & nickname, const CSignupCallbackPtr & signupCB)
{
	if (account.size() < 5)
	{
		CErrorCodeManager::throwException("Error_accountTooShort");
	}

	if (nickname.empty())
	{
		CErrorCodeManager::throwException("Error_nicknameNeeded");
	}

	if (passwd.empty())
	{
		CErrorCodeManager::throwException("Error_passwdNeeded");
	}

	if (NULL != CUserManager::instance()->findUser(account))
	{
		CErrorCodeManager::throwException("Error_accountExisted");
	}

	if (NULL != CUserManager::instance()->findUserByNickname(nickname))
	{
		CErrorCodeManager::throwException("Error_nicknameUsed");
	}

	CUserPtr user = CUserManager::instance()->createUser(account, nickname, passwd);

	SLoginReturn userInfo;
	userInfo.userId = user->getUserId();
	userInfo.nickname = user->getNickname();
	userInfo.sessionKey = user->getSessionKey();
	userInfo.avatar = user->getAvatar();

	signupCB->response(userInfo);

	signupCB->getContext()->setUserObject(user);
}

void CRmiServerImpl::changeAvatar(std::string & sessionKey, std::string & avatar, const CChangeAvatarCallbackPtr & changeAvatarCB)
{
	CUserPtr user = CUserHelper::getUser(changeAvatarCB->getContext(), sessionKey);

	changeAvatarCB->response();
}

void CRmiServerImpl::getPosts(int lastPostId, bool forNew, int requestNum, const CGetPostsCallbackPtr & getPostsCB)
{
	Message::Public::SeqInt postIdList;

	CPostManager::instance()->getPostIdList(lastPostId, forNew, postIdList);
}

void CRmiServerImpl::getImage(int imgId, const CGetImageCallbackPtr & getImageCB)
{

}

void CRmiServerImpl::getMyPosts(std::string & sessionKey, int lastPostId, const CGetMyPostsCallbackPtr & getMyPostsCB)
{

}

void CRmiServerImpl::startPost(std::string & sessionKey, std::string & title, std::string & content, const CStartPostCallbackPtr & startPostCB)
{

}

void CRmiServerImpl::uploadPostImg(std::string & sessionKey, std::string & img, std::string & descrpt, const CUploadPostImgCallbackPtr & uploadPostImgCB)
{

}

void CRmiServerImpl::endPost(std::string & sessionKey, const CEndPostCallbackPtr & endPostCB)
{

}

void CRmiServerImpl::likePost(std::string & sessionKey, int postId, const CLikePostCallbackPtr & likePostCB)
{

}

void CRmiServerImpl::dislikePost(std::string & sessionKey, int postId, const CDislikePostCallbackPtr & dislikePostCB)
{

}

void CRmiServerImpl::commentPost(std::string & sessionKey, int postId, std::string & comments, const CCommentPostCallbackPtr & commentPostCB)
{

}
