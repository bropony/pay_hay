#ifndef __WEBSOCKETSERVERAPP_RESOURCE_COMMENT_MANAGER_H__
#define __WEBSOCKETSERVERAPP_RESOURCE_COMMENT_MANAGER_H__

#include "Resource/Comment.h"
#include "Message/Public/CdlPublic.h"

namespace WebServerApp
{
	class CCommentManager
	{
	public:
		static CCommentManager * instance();
		void loadAllComments();
		void addComment(const CCommentPtr & commentPtr);
		const CCommentPtr createComment(int postId, int fromUserId, const std::string & fromNickName, const std::string & connent);

	private:
		typedef std::map<int, Message::Public::SeqInt> MapPostComment;
		MapComment _mapComment;
		MapPostComment _mapPostComment;
	};
}

#endif