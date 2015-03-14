#ifndef __WEB_SERVER_APP_HELPER_IMAGE_INFO_H__
#define __WEB_SERVER_APP_HELPER_IMAGE_INFO_H__

#include <string>

namespace WebServerApp
{
	class CImageInfo
	{
	public:
		static bool getImageType(const std::string & img, std::string & imgType);
	private:
		CImageInfo();
		~CImageInfo();
	};
}

#endif