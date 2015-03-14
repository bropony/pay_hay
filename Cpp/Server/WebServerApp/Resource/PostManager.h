#ifndef __WEBSERVERAPP_RESOURCE_POST_MANAGER_H__
#define __WEBSERVERAPP_RESOURCE_POST_MANAGER_H__

#include "Resource/Post.h"
#include "Message/Public/CdlPublic.h"

namespace WebServerApp
{
	class CPostManager
	{
	public:
		static CPostManager * instance();
		void loadAllPosts();

		const CPostPtr findPost(int postId);
		
		const CPostPtr createPost(int userId, const std::string & title, 
			const std::string & content, const Message::Public::SeqInt & imgIdList, const cdf::CDateTime & postDt);
		void addPost(const CPostPtr & post);

	private:
		CPostManager();
		~CPostManager();
	private:
		MapPost _mapPost;
	};
}

#endif