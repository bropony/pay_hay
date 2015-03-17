#ifndef __WEB_SERVER_APP_RESOURCE_COMMENT_H__
#define __WEB_SERVER_APP_RESOURCE_COMMENT_H__

#include "Message/Db/Tables/TUserComment.h"
#include <map>

#include "Rmi/DataStructDef.h"

namespace WebServerApp
{
	class CComment
		: public virtual cdf::CRefShared
	{
	public:
		CComment(const Message::Db::Tables::TUserComment & tUserComment);
		Message::Db::Tables::TUserComment & getTUserComment();
		void updateToDb();

		void commentToClient(Rmi::SComment & comment);

	private:
		Message::Db::Tables::TUserComment _tUserComment;
	};
	typedef cdf::CHandle<CComment> CCommentPtr;
	typedef std::map<int, CCommentPtr> MapComment;
}

#endif