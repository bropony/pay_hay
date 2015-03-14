#ifndef __WEBSERVERAPP_USER_USER_HELPER_H__
#define __WEBSERVERAPP_USER_USER_HELPER_H__

#include "User/User.h"
#include "framework/websocket/websocketserver.h"

namespace WebServerApp
{
	class CUserHelper
	{
	public:
		static const CUserPtr getUser(const cdf::CWSContextPtr & context, bool throwIfNull = true);
		static const CUserPtr getUser(const cdf::CWSContextPtr & context, const std::string & sessionKey, bool throwIfNull = true);

	private:
		CUserHelper();
		~CUserHelper();
	};
}

#endif