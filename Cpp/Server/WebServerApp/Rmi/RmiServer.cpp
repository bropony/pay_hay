#include "RmiServer.h"
#include "Config/ErrorCodeManager.h"

using namespace Rmi;

CLoginCallback::CLoginCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CLoginCallback::response( const SLoginReturn & userInfo)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	userInfo.__write(__os);

	__response(__os);
}


CSignupCallback::CSignupCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CSignupCallback::response( const SLoginReturn & userInfo)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	userInfo.__write(__os);

	__response(__os);
}


CChangeAvatarCallback::CChangeAvatarCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CChangeAvatarCallback::response()
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);


	__response(__os);
}


CGetPostsCallback::CGetPostsCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CGetPostsCallback::response( const SeqPost & postList)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	::Rmi::__write(__os, postList, SeqPost__U__());

	__response(__os);
}


CGetImageCallback::CGetImageCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CGetImageCallback::response( const std::string & img,  const std::string & shortDesc)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	__os.write(img);
	__os.write(shortDesc);

	__response(__os);
}


CGetMyPostsCallback::CGetMyPostsCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CGetMyPostsCallback::response( const SeqPost & postList)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	::Rmi::__write(__os, postList, SeqPost__U__());

	__response(__os);
}


CStartPostCallback::CStartPostCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CStartPostCallback::response()
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);


	__response(__os);
}


CUploadPostImgCallback::CUploadPostImgCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CUploadPostImgCallback::response(int imgId)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	__os.write(imgId);

	__response(__os);
}


CEndPostCallback::CEndPostCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CEndPostCallback::response(int postId)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	__os.write(postId);

	__response(__os);
}


CLikePostCallback::CLikePostCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CLikePostCallback::response()
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);


	__response(__os);
}


CDislikePostCallback::CDislikePostCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CDislikePostCallback::response()
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);


	__response(__os);
}


CCommentPostCallback::CCommentPostCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CCommentPostCallback::response()
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);


	__response(__os);
}


void CRmiServer::__login(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string account;
	__is.read(account);

	std::string passwd;
	__is.read(passwd);

	CLoginCallbackPtr __cb = new CLoginCallback(context, __msgId);
	login(account, passwd, __cb);
}

void CRmiServer::__signup(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string account;
	__is.read(account);

	std::string passwd;
	__is.read(passwd);

	std::string nickname;
	__is.read(nickname);

	CSignupCallbackPtr __cb = new CSignupCallback(context, __msgId);
	signup(account, passwd, nickname, __cb);
}

void CRmiServer::__changeAvatar(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string sessionKey;
	__is.read(sessionKey);

	std::string avatar;
	__is.read(avatar);

	CChangeAvatarCallbackPtr __cb = new CChangeAvatarCallback(context, __msgId);
	changeAvatar(sessionKey, avatar, __cb);
}

void CRmiServer::__getPosts(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	int lastPostId = 0;
	__is.read(lastPostId);

	bool forNew = false;
	__is.read(forNew);

	int requestNum = 0;
	__is.read(requestNum);

	CGetPostsCallbackPtr __cb = new CGetPostsCallback(context, __msgId);
	getPosts(lastPostId, forNew, requestNum, __cb);
}

void CRmiServer::__getImage(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	int imgId = 0;
	__is.read(imgId);

	CGetImageCallbackPtr __cb = new CGetImageCallback(context, __msgId);
	getImage(imgId, __cb);
}

void CRmiServer::__getMyPosts(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string sessionKey;
	__is.read(sessionKey);

	int lastPostId = 0;
	__is.read(lastPostId);

	bool forNew = false;
	__is.read(forNew);

	CGetMyPostsCallbackPtr __cb = new CGetMyPostsCallback(context, __msgId);
	getMyPosts(sessionKey, lastPostId, forNew, __cb);
}

void CRmiServer::__startPost(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string sessionKey;
	__is.read(sessionKey);

	std::string title;
	__is.read(title);

	std::string content;
	__is.read(content);

	CStartPostCallbackPtr __cb = new CStartPostCallback(context, __msgId);
	startPost(sessionKey, title, content, __cb);
}

void CRmiServer::__uploadPostImg(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string sessionKey;
	__is.read(sessionKey);

	std::string img;
	__is.read(img);

	std::string descrpt;
	__is.read(descrpt);

	CUploadPostImgCallbackPtr __cb = new CUploadPostImgCallback(context, __msgId);
	uploadPostImg(sessionKey, img, descrpt, __cb);
}

void CRmiServer::__endPost(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string sessionKey;
	__is.read(sessionKey);

	CEndPostCallbackPtr __cb = new CEndPostCallback(context, __msgId);
	endPost(sessionKey, __cb);
}

void CRmiServer::__likePost(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string sessionKey;
	__is.read(sessionKey);

	int postId = 0;
	__is.read(postId);

	CLikePostCallbackPtr __cb = new CLikePostCallback(context, __msgId);
	likePost(sessionKey, postId, __cb);
}

void CRmiServer::__dislikePost(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string sessionKey;
	__is.read(sessionKey);

	int postId = 0;
	__is.read(postId);

	CDislikePostCallbackPtr __cb = new CDislikePostCallback(context, __msgId);
	dislikePost(sessionKey, postId, __cb);
}

void CRmiServer::__commentPost(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string sessionKey;
	__is.read(sessionKey);

	int postId = 0;
	__is.read(postId);

	std::string comments;
	__is.read(comments);

	CCommentPostCallbackPtr __cb = new CCommentPostCallback(context, __msgId);
	commentPost(sessionKey, postId, comments, __cb);
}

void CRmiServer::__call(cdf::CSimpleSerializer & __is, const cdf::CWSContextPtr & context)
{
	int __msgId = 0;
	int __eventId = 0;

	try
	{
		__is.read(__msgId);
		__is.read(__eventId);
	}
	catch (const cdf::CException & ex)
	{
		onError(__msgId, ex.what(), ex.code(), context);
	}

	try
	{
		switch (__eventId)
		{
		case 1:
			__login(__is, __msgId, context);
			break;
		case 2:
			__signup(__is, __msgId, context);
			break;
		case 3:
			__changeAvatar(__is, __msgId, context);
			break;
		case 20:
			__getPosts(__is, __msgId, context);
			break;
		case 21:
			__getImage(__is, __msgId, context);
			break;
		case 22:
			__getMyPosts(__is, __msgId, context);
			break;
		case 30:
			__startPost(__is, __msgId, context);
			break;
		case 31:
			__uploadPostImg(__is, __msgId, context);
			break;
		case 32:
			__endPost(__is, __msgId, context);
			break;
		case 40:
			__likePost(__is, __msgId, context);
			break;
		case 41:
			__dislikePost(__is, __msgId, context);
			break;
		case 42:
			__commentPost(__is, __msgId, context);
			break;
		default:
			WebServerApp::CErrorCodeManager::throwException("Error_NotRegisterdRmiCall");
			break;
		}
	}
	catch (const cdf::CException & ex)
	{
		onError(__msgId, ex.what(), ex.code(), context);
	}
}

void CRmiServer::onError(int msgId, const std::string & what, int code, const cdf::CWSContextPtr & context)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();
	__os.write(msgId);
	__os.write(false);
	__os.write(what);
	__os.write(code);

	__os.encrypt();
	cdf::CWebsocketServer::instance()->sendData(context, __os.getBuffer(), websocketpp::frame::opcode::value::BINARY);
}

