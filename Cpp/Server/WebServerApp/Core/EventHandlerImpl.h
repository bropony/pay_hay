#ifndef __WEBSERVERAPP_CORE_EVENT_HANDLER_IMPL_H__
#define __WEBSERVERAPP_CORE_EVENT_HANDLER_IMPL_H__

#include "framework/websocket/websocketcontext.h"
#include "framework/json/value.h"
#include "Core/EventHandler.h"

namespace WebServerApp
{
	class CEventHandlerImpl
		: public virtual cg::CEventHandler
	{
	public:
		CEventHandlerImpl();
		~CEventHandlerImpl();

		virtual void onUploadImg(int type, const std::string & img, const cdf::CWSContextPtr & context);

		virtual void login(const std::string & account, 
			const std::string & passwd, 
			const std::string & deviceId, 
			const ::cg::CLogin_callbackPtr & callback);

		virtual void signup(const std::string & account, 
			const std::string & nickname, 
			const std::string & passwd, 
			const std::string & deviceId, 
			const ::cg::CSignup_callbackPtr & callback);

		virtual void reconnect(const std::string & account, 
			const std::string & sessionKey,
			const ::cg::CReconnect_callbackPtr & callback);

		virtual void startPost(const std::string & title, 
			const std::string & content, const Json::Value & imgNames, 
			const ::cg::CStartPost_callbackPtr & callback);

		virtual void endPost(const ::cg::CEndPost_callbackPtr & callback);

		virtual void deletePost(int postId, const ::cg::CDeletePost_callbackPtr & callback);

		virtual void getPostList(int userId, 
			int lastPostId, 
			bool forNewPost, 
			const ::cg::CGetPostList_callbackPtr & callback);

		virtual void viewPost(int postId, 
			const ::cg::CViewPost_callbackPtr & callback);

		virtual void commentPost(int postId, 
			const std::string & comment, 
			const ::cg::CCommentPost_callbackPtr & callback);

		virtual void likePost(int postId, const ::cg::CLikePost_callbackPtr & callback);

		virtual void dislikePost(int postId, 
			const ::cg::CDislikePost_callbackPtr & callback);

		virtual void test(const cdf::CDateTime & testIn, const ::cg::CTest_callbackPtr & callback);

		virtual void getImage(int imgId, const ::cg::CGetImage_callbackPtr & callback);
	};

	typedef cdf::CHandle<CEventHandlerImpl> CEventHandlerImplPtr;
}

#endif