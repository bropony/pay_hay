#include "UserHelper.h"
#include "Config/ErrorCodeManager.h"

using namespace WebServerApp;

const CUserPtr CUserHelper::getUser(const cdf::CWSContextPtr & context, bool throwIfNull/* = true*/)
{
	CUserPtr user = CUserPtr::dynamicCast(context->getUserObject());

	if (NULL == user && throwIfNull)
	{
		CErrorCodeManager::throwException("Error_nullUserPtr");
	}

	return user;
}
