#ifndef __WEBSERVERAPP_RESOURCE_POST_H__
#define __WEBSERVERAPP_RESOURCE_POST_H__

#include "framework/cdf_common.h"
#include "framework/util/refshared.h"

#include "Message/Db/Tables/TUserPost.h"

namespace WebServerApp
{
	class CPost
		: public virtual cdf::CRefShared
	{
	public:
		CPost(const Message::Db::Tables::TUserPost & userPost);
		Message::Db::Tables::TUserPost & getTUserPost();
	private:
		Message::Db::Tables::TUserPost _tUserPost;
	};
	typedef cdf::CHandle<CPost> CPostPtr;
	typedef std::map<int, CPostPtr> MapPost;
}

#endif