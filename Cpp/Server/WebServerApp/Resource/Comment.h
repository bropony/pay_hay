#ifndef __WEB_SERVER_APP_RESOURCE_COMMENT_H__
#define __WEB_SERVER_APP_RESOURCE_COMMENT_H__

#include "Message/Db/Tables/TUserComment.h"
#include <map>

namespace WebServerApp
{
	class CComment
		: public virtual cdf::CRefShared
	{
	public:
		CComment(const Message::Db::Tables::TUserComment & tUserComment);
		Message::Db::Tables::TUserComment & getTUserComment();
		void updateToDb();

	private:
		Message::Db::Tables::TUserComment _tUserComment;
	};
	typedef cdf::CHandle<CComment> CCommentPtr;
	typedef std::map<int, CCommentPtr> MapComment;
}

#endif