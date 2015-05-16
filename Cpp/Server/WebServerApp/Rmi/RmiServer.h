#ifndef __RMI_RMI_SERVER_H__
#define __RMI_RMI_SERVER_H__

#include "framework/websocket/websocketcontext.h"
#include "framework/serialize/simpleserializer.h"
#include "framework/websocket/websocketserver.h"
#include "Rmi/DataStructDef.h"
#include "Rmi/RmiCallbackBase.h"

namespace Rmi
{
	class CLoginCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CLoginCallback(const cdf::CWSContextPtr & context, int msgId);

		void response( const SLoginReturn & userInfo);
	};
	typedef cdf::CHandle<CLoginCallback> CLoginCallbackPtr;

	class CSignupCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CSignupCallback(const cdf::CWSContextPtr & context, int msgId);

		void response( const SLoginReturn & userInfo);
	};
	typedef cdf::CHandle<CSignupCallback> CSignupCallbackPtr;

	class CChangeAvatarCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CChangeAvatarCallback(const cdf::CWSContextPtr & context, int msgId);

		void response(int avatarImgId);
	};
	typedef cdf::CHandle<CChangeAvatarCallback> CChangeAvatarCallbackPtr;

	class CGetPostsCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CGetPostsCallback(const cdf::CWSContextPtr & context, int msgId);

		void response( const SeqPost & postList);
	};
	typedef cdf::CHandle<CGetPostsCallback> CGetPostsCallbackPtr;

	class CGetImageCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CGetImageCallback(const cdf::CWSContextPtr & context, int msgId);

		void response( const std::string & img,  const std::string & shortDesc);
	};
	typedef cdf::CHandle<CGetImageCallback> CGetImageCallbackPtr;

	class CGetMyPostsCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CGetMyPostsCallback(const cdf::CWSContextPtr & context, int msgId);

		void response( const SeqPost & postList);
	};
	typedef cdf::CHandle<CGetMyPostsCallback> CGetMyPostsCallbackPtr;

	class CStartPostCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CStartPostCallback(const cdf::CWSContextPtr & context, int msgId);

		void response();
	};
	typedef cdf::CHandle<CStartPostCallback> CStartPostCallbackPtr;

	class CUploadPostImgCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CUploadPostImgCallback(const cdf::CWSContextPtr & context, int msgId);

		void response(int imgId);
	};
	typedef cdf::CHandle<CUploadPostImgCallback> CUploadPostImgCallbackPtr;

	class CEndPostCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CEndPostCallback(const cdf::CWSContextPtr & context, int msgId);

		void response(int postId);
	};
	typedef cdf::CHandle<CEndPostCallback> CEndPostCallbackPtr;

	class CLikePostCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CLikePostCallback(const cdf::CWSContextPtr & context, int msgId);

		void response();
	};
	typedef cdf::CHandle<CLikePostCallback> CLikePostCallbackPtr;

	class CDislikePostCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CDislikePostCallback(const cdf::CWSContextPtr & context, int msgId);

		void response();
	};
	typedef cdf::CHandle<CDislikePostCallback> CDislikePostCallbackPtr;

	class CCommentPostCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CCommentPostCallback(const cdf::CWSContextPtr & context, int msgId);

		void response();
	};
	typedef cdf::CHandle<CCommentPostCallback> CCommentPostCallbackPtr;

	class CGetCommentsCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CGetCommentsCallback(const cdf::CWSContextPtr & context, int msgId);

		void response( const SeqComment & comments);
	};
	typedef cdf::CHandle<CGetCommentsCallback> CGetCommentsCallbackPtr;

	class CStartPostExCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CStartPostExCallback(const cdf::CWSContextPtr & context, int msgId);

		void response(int postId);
	};
	typedef cdf::CHandle<CStartPostExCallback> CStartPostExCallbackPtr;

	class CUploadPostImgExCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CUploadPostImgExCallback(const cdf::CWSContextPtr & context, int msgId);

		void response(int imgId);
	};
	typedef cdf::CHandle<CUploadPostImgExCallback> CUploadPostImgExCallbackPtr;

	class CIsSessionKeyValidCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CIsSessionKeyValidCallback(const cdf::CWSContextPtr & context, int msgId);

		void response(bool res);
	};
	typedef cdf::CHandle<CIsSessionKeyValidCallback> CIsSessionKeyValidCallbackPtr;

	class CRmiServer
		: public virtual cdf::CRefShared
	{
	public:
		void __login(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void login( const std::string & account,  const std::string & passwd, const CLoginCallbackPtr & loginCB) = 0;
	
		void __signup(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void signup( const std::string & account,  const std::string & passwd,  const std::string & nickname, const CSignupCallbackPtr & signupCB) = 0;
	
		void __changeAvatar(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void changeAvatar( const std::string & sessionKey,  const std::string & avatar, const CChangeAvatarCallbackPtr & changeAvatarCB) = 0;
	
		void __getPosts(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void getPosts(int lastPostId, bool forNew, int requestNum, const CGetPostsCallbackPtr & getPostsCB) = 0;
	
		void __getImage(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void getImage(int imgId, const CGetImageCallbackPtr & getImageCB) = 0;
	
		void __getMyPosts(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void getMyPosts( const std::string & sessionKey, int lastPostId, bool forNew, const CGetMyPostsCallbackPtr & getMyPostsCB) = 0;
	
		void __startPost(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void startPost( const std::string & sessionKey,  const std::string & title,  const std::string & content, const CStartPostCallbackPtr & startPostCB) = 0;
	
		void __uploadPostImg(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void uploadPostImg( const std::string & sessionKey,  const std::string & img,  const std::string & descrpt, const CUploadPostImgCallbackPtr & uploadPostImgCB) = 0;
	
		void __endPost(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void endPost( const std::string & sessionKey, const CEndPostCallbackPtr & endPostCB) = 0;
	
		void __likePost(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void likePost( const std::string & sessionKey, int postId, const CLikePostCallbackPtr & likePostCB) = 0;
	
		void __dislikePost(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void dislikePost( const std::string & sessionKey, int postId, const CDislikePostCallbackPtr & dislikePostCB) = 0;
	
		void __commentPost(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void commentPost( const std::string & sessionKey, int postId,  const std::string & comments, const CCommentPostCallbackPtr & commentPostCB) = 0;
	
		void __getComments(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void getComments( const std::string & sessionKey, int postId, const CGetCommentsCallbackPtr & getCommentsCB) = 0;
	
		void __startPostEx(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void startPostEx( const std::string & sessionKey,  const std::string & title,  const std::string & content, int imgNum, const CStartPostExCallbackPtr & startPostExCB) = 0;
	
		void __uploadPostImgEx(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void uploadPostImgEx( const std::string & sessionKey,  const std::string & img,  const std::string & descrpt, int postId, int index, const CUploadPostImgExCallbackPtr & uploadPostImgExCB) = 0;
	
		void __isSessionKeyValid(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void isSessionKeyValid( const std::string & sessionKey, const CIsSessionKeyValidCallbackPtr & isSessionKeyValidCB) = 0;
	
		void __call(cdf::CSimpleSerializer & __is, const cdf::CWSContextPtr & context);

		void onError(int msgId, const std::string & what, int code, const cdf::CWSContextPtr & context);
	};
	typedef cdf::CHandle<CRmiServer> CRmiServerPtr;
} //end of namespace Rmi
#endif // end of __RMI_RMI_SERVER_H__

