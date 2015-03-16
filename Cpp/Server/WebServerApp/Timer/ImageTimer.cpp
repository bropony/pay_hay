#include "ImageTimer.h"

#include "Resource/ImageManager.h"

using namespace WebServerApp;

CImageTimer::CImageTimer()
:_expiredSecs(6 * 3600)
{

}

int CImageTimer::handleTimeout(const cdf::CDateTime &currentTime, const void *act /* = 0 */)
{
	CImageManager::instance()->releaseExpiredImgMemory(currentTime, _expiredSecs);

	return 0;
}

int CImageTimer::getExpiredSecs()
{
	return _expiredSecs;
}
