#include "UserHelper.h"
#include "UserManager.h"
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

const CUserPtr CUserHelper::getUser(const cdf::CWSContextPtr & context, const std::string & sessionKey, bool throwIfNull /*= true*/)
{
	CUserPtr user = CUserPtr::dynamicCast(context->getUserObject());

	if (NULL != user)
	{
		return user;
	}

	user = CUserManager::instance()->findUserBySessionKey(sessionKey);

	if (NULL != user)
	{
		context->setUserObject(user);

		return user;
	}

	if (throwIfNull)
	{
		CErrorCodeManager::throwException("Error_nullUserPtr");
	}

	return NULL;
}
