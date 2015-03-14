#include "EventHandlerImpl.h"
#include "EventCommon.h"

#include "User/UserManager.h"
#include "User/UserHelper.h"
#include "Config/ErrorCodeManager.h"
#include "Core/PostUploader.h"
#include "Resource/PostManager.h"
#include "Resource/ImageManager.h"

#include "framework/websocket/websocketserver.h"

using namespace WebServerApp;

CEventHandlerImpl::CEventHandlerImpl()
{

}

CEventHandlerImpl::~CEventHandlerImpl()
{

}

void CEventHandlerImpl::onUploadImg(int type, const std::string & img, const cdf::CWSContextPtr & context)
{
	CUserPtr user = CUserHelper::getUser(context);
	
	switch (type)
	{
	case ImageType::POST:
		CPostUploader::instance()->addImg(user->getUserId(), img);
		break;
	default:
		CErrorCodeManager::throwException("Error_unkwonImgType");
		break;
	}
	
}

void CEventHandlerImpl::login(const std::string & account,
	const std::string & passwd,
	const std::string & deviceId,
	const ::cg::CLogin_callbackPtr & callback
	)
{
	CUserPtr user = CUserManager::instance()->findUser(account);
	if (NULL == user || 
		!user->isPasswdMatched(passwd))
	{
		CErrorCodeManager::throwException("Error_accountOrPasswd");
	}

	callback->response(user->getSessionKey(), user->getNickname(), user->getUserId());
	callback->getContext()->setUserObject(user);
}

void CEventHandlerImpl::signup(const std::string & account,
	const std::string & nickname,
	const std::string & passwd,
	const std::string & deviceId,
	const ::cg::CSignup_callbackPtr & callback
	)
{
	if (CUserManager::instance()->hasUserExisted(account))
	{
		CErrorCodeManager::throwException("Error_accountExisted");
	}

	if (CUserManager::instance()->hasUserExistedByNickname(nickname))
	{
		CErrorCodeManager::throwException("Error_nicknameUsed");
	}

	CUserPtr user = CUserManager::instance()->createUser(account, nickname, passwd);
	callback->getContext()->setUserObject(user);

	callback->response(user->getSessionKey(), user->getUserId());
}

void CEventHandlerImpl::reconnect(const std::string & account,
	const std::string & sessionKey,
	const ::cg::CReconnect_callbackPtr & callback)
{
	CUserPtr user = CUserManager::instance()->findUser(account);
	if (NULL == user)
	{
		CDF_LOG_TRACE("CEventHandlerImpl::reconnect", "account Not Found: " << account);
		CErrorCodeManager::throwException("Error_userDataError");
	}

	if (!user->isSessionKeyMatched(sessionKey))
	{
		CErrorCodeManager::throwException("Error_userDataError");
	}

	callback->getContext()->setUserObject(user);
	callback->response(0);
}

void CEventHandlerImpl::startPost(const std::string & title,
	const std::string & content, const Json::Value & imgNames,
	const ::cg::CStartPost_callbackPtr & callback)
{
	CUserPtr user = CUserHelper::getUser(callback->getContext());

	CPostUploader::instance()->startPost(user->getUserId(), title, content, imgNames);

	callback->response();
}

//void CEventHandlerImpl::uploadImg(const std::string & img, const cdf::CWSContextPtr & context)
//{
//	CUserPtr user = CUserHelper::getUser(context);
//
//	CPostUploader::instance()->addImg(user->getUserId(), "tmp.jpg", "binary", img);
//}
//
//void CEventHandlerImpl::uploadImg(const std::string & filename, const std::string & shortDesc, const std::string & img)
//{
//	CUserPtr user = CUserHelper::getUser(_context);
//
//	CPostUploader::instance()->addImg(user->getUserId(), filename, shortDesc, img);
//
//	Json::Value jsRes;
//	sendData(jsRes);
//}

void CEventHandlerImpl::endPost(const ::cg::CEndPost_callbackPtr & callback)
{
	CUserPtr user = CUserHelper::getUser(callback->getContext());

	cdf::CDateTime postDt;

	int postId = CPostUploader::instance()->endPost(user->getUserId(), postDt);

	callback->response(postId);
}

void CEventHandlerImpl::deletePost(int postId, const ::cg::CDeletePost_callbackPtr & callback)
{

}

void CEventHandlerImpl::getPostList(int userId,
	int lastPostId,
	bool forNewPost,
	const ::cg::CGetPostList_callbackPtr & callback)
{
	Message::Public::SeqInt postIdList;

	if (userId > 0)
	{
		CUserPtr userPtr = CUserManager::instance()->findUser(userId);
		if (NULL == userPtr)
		{
			CDF_LOG_TRACE("CEventHandlerImpl::getPostList", "NoSuchUser: " << userId);
		}
		else
		{
			if (forNewPost)
			{
				userPtr->getNewer10PostId(lastPostId, postIdList);
			}
			else
			{
				userPtr->getOlder10PostId(lastPostId, postIdList);
			}
		}
	}
	else
	{
		CPostManager::instance()->getPostIdList(lastPostId, forNewPost, postIdList);
	}

	Json::Value jsRes;
	jsRes.parse("[]");
	CPostManager::instance()->getPostList(postIdList, jsRes);

	callback->response(jsRes);
}

void CEventHandlerImpl::viewPost(int postId,
	const ::cg::CViewPost_callbackPtr & callback)
{

}

void CEventHandlerImpl::commentPost(int postId,
	const std::string & comment,
	const ::cg::CCommentPost_callbackPtr & callback)
{

}

void CEventHandlerImpl::likePost(int postId, const ::cg::CLikePost_callbackPtr & callback)
{

}

void CEventHandlerImpl::dislikePost(int postId,
	const ::cg::CDislikePost_callbackPtr & callback)
{

}

void CEventHandlerImpl::test(const cdf::CDateTime & testIn, const ::cg::CTest_callbackPtr & callback)
{

}

void CEventHandlerImpl::getImage(int imgId, const ::cg::CGetImage_callbackPtr & callback)
{
	CImagePtr img = CImageManager::instance()->findImage(imgId);
	if (NULL == img)
	{
		CErrorCodeManager::throwException("Error_noSuchImg");
	}

	callback->responseB(img->getImgBin());
}