#ifndef __WEB_SERVER_APP_TIMER_IMAGE_TIMER_H__
#define __WEB_SERVER_APP_TIMER_IMAGE_TIMER_H__

#include "framework/util/eventhandler.h"

namespace WebServerApp
{
	class CImageTimer
		: public virtual cdf::IEventHandler
	{
	public:
		CImageTimer();
		virtual int handleTimeout(const cdf::CDateTime &currentTime, const void *act /* = 0 */);
		int getExpiredSecs();
	private:
		int _expiredSecs;
	};
	typedef cdf::CHandle<CImageTimer> CImageTimerPtr;
}


#endif