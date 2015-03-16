#include "framework/net/reactor/reactor.h"

#include "TimerManager.h"
#include "ImageTimer.h"

using namespace WebServerApp;

void CTimerManager::initTimers()
{
	//image timer
	CImageTimerPtr imgTimer = new CImageTimer();
	cdf::CInterval imgTimerInterval(imgTimer->getExpiredSecs(), 0);
	cdf::CReactor::instance()->schedule(imgTimer, NULL, imgTimerInterval, imgTimerInterval);

	//
}
