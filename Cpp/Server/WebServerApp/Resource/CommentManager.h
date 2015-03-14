#ifndef __WEBSOCKETSERVERAPP_RESOURCE_COMMENT_MANAGER_H__
#define __WEBSOCKETSERVERAPP_RESOURCE_COMMENT_MANAGER_H__

namespace WebServerApp
{
	class CCommentManager
	{
	public:
		static CCommentManager * instance();
		void loadAllComments();
	};
}

#endif