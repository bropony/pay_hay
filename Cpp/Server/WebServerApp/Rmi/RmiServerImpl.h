#ifndef __RMI_RMI_SERVER_IMPL_H__
#define __RMI_RMI_SERVER_IMPL_H__

#include "Rmi/RmiServer.h"

namespace Rmi
{
	class CRmiServerImpl
		: public virtual CRmiServer
	{
	public:
		virtual void login(const std::string & account, const std::string & passwd, const CLoginCallbackPtr & loginCB);
		virtual void signup(const std::string & account, const std::string & passwd, const std::string & nickname, const CSignupCallbackPtr & signupCB);
		virtual void changeAvatar(const std::string & sessionKey, const std::string & avatar, const CChangeAvatarCallbackPtr & changeAvatarCB);
		virtual void getPosts(int lastPostId, bool forNew, int requestNum, const CGetPostsCallbackPtr & getPostsCB);
		virtual void getImage(int imgId, const CGetImageCallbackPtr & getImageCB);
		virtual void getMyPosts(const std::string & sessionKey, int lastPostId, bool forNew, const CGetMyPostsCallbackPtr & getMyPostsCB);
		virtual void startPost(const std::string & sessionKey, const std::string & title, const std::string & content, const CStartPostCallbackPtr & startPostCB);
		virtual void uploadPostImg(const std::string & sessionKey, const std::string & img, const std::string & descrpt, const CUploadPostImgCallbackPtr & uploadPostImgCB);
		virtual void endPost(const std::string & sessionKey, const CEndPostCallbackPtr & endPostCB);
		virtual void likePost(const std::string & sessionKey, int postId, const CLikePostCallbackPtr & likePostCB);
		virtual void dislikePost(const std::string & sessionKey, int postId, const CDislikePostCallbackPtr & dislikePostCB);
		virtual void commentPost(const std::string & sessionKey, int postId, const std::string & comments, const CCommentPostCallbackPtr & commentPostCB);
		virtual void getComments(const std::string & sessionKey, int postId, const CGetCommentsCallbackPtr & getCommentsCB);
		virtual void startPostEx(const std::string & sessionKey, const std::string & title, const std::string & content, int imgNum, const CStartPostExCallbackPtr & startPostExCB);
		virtual void uploadPostImgEx(const std::string & sessionKey, const std::string & img, const std::string & descrpt, int postId, int index, const CUploadPostImgExCallbackPtr & uploadPostImgExCB);

	};
}

#endif