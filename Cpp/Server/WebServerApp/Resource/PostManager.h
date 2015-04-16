#ifndef __WEBSERVERAPP_RESOURCE_POST_MANAGER_H__
#define __WEBSERVERAPP_RESOURCE_POST_MANAGER_H__

#include "Resource/Post.h"
#include "Message/Public/CdlPublic.h"
#include "Rmi/DataStructDef.h"

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
		const CPostPtr createPost(int userId, const std::string & title, const std::string & content, int imgNum);

		void addPost(const CPostPtr & post);

		void getPostIdList(int lastPostId, bool forNewPosts, Message::Public::SeqInt & postIdList);
		void getPostList(const Message::Public::SeqInt & postIdList, Json::Value & jsRes);
		void getPostList(const Message::Public::SeqInt & postIdList, Rmi::SeqPost & postList);

	private:
		CPostManager();
		~CPostManager();
	private:
		MapPost _mapPost;
		std::vector<int> _postIdList;
	};
}

#endif