#ifndef __RMI_RMI_SERVER_IMPL_H__
#define __RMI_RMI_SERVER_IMPL_H__

#include "Rmi/RmiServer.h"

namespace Rmi
{
	class CRmiServerImpl
		: public virtual CRmiServer
	{
	public:
		virtual void login(std::string & account, std::string & passwd, const CLoginCallbackPtr & loginCB);
		virtual void signup(std::string & account, std::string & passwd, std::string & nickname, const CSignupCallbackPtr & signupCB);
		virtual void changeAvatar(std::string & sessionKey, std::string & avatar, const CChangeAvatarCallbackPtr & changeAvatarCB);
		virtual void getPosts(int lastPostId, bool forNew, int requestNum, const CGetPostsCallbackPtr & getPostsCB);
		virtual void getImage(int imgId, const CGetImageCallbackPtr & getImageCB);
		virtual void getMyPosts(std::string & sessionKey, int lastPostId, const CGetMyPostsCallbackPtr & getMyPostsCB);
		virtual void startPost(std::string & sessionKey, std::string & title, std::string & content, const CStartPostCallbackPtr & startPostCB);
		virtual void uploadPostImg(std::string & sessionKey, std::string & img, std::string & descrpt, const CUploadPostImgCallbackPtr & uploadPostImgCB);
		virtual void endPost(std::string & sessionKey, const CEndPostCallbackPtr & endPostCB);
		virtual void likePost(std::string & sessionKey, int postId, const CLikePostCallbackPtr & likePostCB);
		virtual void dislikePost(std::string & sessionKey, int postId, const CDislikePostCallbackPtr & dislikePostCB);
		virtual void commentPost(std::string & sessionKey, int postId, std::string & comments, const CCommentPostCallbackPtr & commentPostCB);

	};
}

#endif