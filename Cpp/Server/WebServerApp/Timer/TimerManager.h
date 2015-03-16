#ifndef __WEB_SERVER_APP_TIMER_TIMER_MANAGER_H__
#define __WEB_SERVER_APP_TIMER_TIMER_MANAGER_H__

namespace WebServerApp
{
	class CTimerManager
	{
	public:
		static void initTimers();
	private:
		CTimerManager();
		~CTimerManager();
	};
}

#endif