#include "RmiServerImpl.h"
#include "Config/ErrorCodeManager.h"
#include "Resource/ImageManager.h"
#include "Resource/PostManager.h"

#include "User/UserManager.h"
#include "User/UserHelper.h"

using namespace Rmi;
using namespace WebServerApp;

void CRmiServerImpl::login(const std::string & account, const std::string & passwd, const CLoginCallbackPtr & loginCB)
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

void CRmiServerImpl::signup(const std::string & account, const std::string & passwd, const std::string & nickname, const CSignupCallbackPtr & signupCB)
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

void CRmiServerImpl::changeAvatar(const std::string & sessionKey, const std::string & avatar, const CChangeAvatarCallbackPtr & changeAvatarCB)
{
	if (avatar.size() > 50000)
	{
		CErrorCodeManager::throwException("Error_avatarImgToLarge");
	}

	CUserPtr user = CUserHelper::getUser(changeAvatarCB->getContext(), sessionKey);

	CImagePtr imgPtr = CImageManager::instance()->createImage("avatar", avatar);
	if (NULL == imgPtr)
	{
		CErrorCodeManager::throwException("Error_saveAvatarImgError");
	}

	user->updateAvatar(imgPtr->getTUserImg().imgId, imgPtr->getImgBin());
	user->updateToDb();

	changeAvatarCB->response();
}

void CRmiServerImpl::getPosts(int lastPostId, bool forNew, int requestNum, const CGetPostsCallbackPtr & getPostsCB)
{
	Message::Public::SeqInt postIdList;

	CPostManager::instance()->getPostIdList(lastPostId, forNew, postIdList);
}

void CRmiServerImpl::getImage(int imgId, const CGetImageCallbackPtr & getImageCB)
{
	CImagePtr img = CImageManager::instance()->findImage(imgId);
	if (NULL == img)
	{
		CErrorCodeManager::throwException("Error_noSuchImg");
	}

	getImageCB->response(img->getImgBin(), img->getDesc());
}

void CRmiServerImpl::getMyPosts(const std::string & sessionKey, int lastPostId, bool forNew, const CGetMyPostsCallbackPtr & getMyPostsCB)
{
	CUserPtr user = CUserHelper::getUser(getMyPostsCB->getContext(), sessionKey);

	Message::Public::SeqInt postIdList;

	if (forNew)
	{
		user->getNewer10PostId(lastPostId, postIdList);
	}
	else
	{
		user->getOlder10PostId(lastPostId, postIdList);
	}

	Rmi::SeqPost postList;
	CPostManager::instance()->getPostList(postIdList, postList);

	getMyPostsCB->response(postList);
}

void CRmiServerImpl::startPost(const std::string & sessionKey, const std::string & title, const std::string & content, const CStartPostCallbackPtr & startPostCB)
{

}

void CRmiServerImpl::uploadPostImg(const std::string & sessionKey, const std::string & img, const std::string & descrpt, const CUploadPostImgCallbackPtr & uploadPostImgCB)
{

}

void CRmiServerImpl::endPost(const std::string & sessionKey, const CEndPostCallbackPtr & endPostCB)
{

}

void CRmiServerImpl::likePost(const std::string & sessionKey, int postId, const CLikePostCallbackPtr & likePostCB)
{

}

void CRmiServerImpl::dislikePost(const std::string & sessionKey, int postId, const CDislikePostCallbackPtr & dislikePostCB)
{

}

void CRmiServerImpl::commentPost(const std::string & sessionKey, int postId, const std::string & comments, const CCommentPostCallbackPtr & commentPostCB)
{

}
