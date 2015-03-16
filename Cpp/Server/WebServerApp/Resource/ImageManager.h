#ifndef __WEBSERVERAPP_RESOURCE_IMAGE_MANAGER_H__
#define __WEBSERVERAPP_RESOURCE_IMAGE_MANAGER_H__

#include "Resource/Image.h"

namespace WebServerApp
{
	class CImageManager
	{
	public:
		static CImageManager * instance();
		void loadAllImages();
		void releaseExpiredImgMemory(const cdf::CDateTime & nowDt, int expiredSecs);

		const CImagePtr findImage(int imgId);

		const CImagePtr createImage(const std::string & shortDesc, const std::string & imgBinary);
		void addImage(const CImagePtr & imgPtr);
	private:
		CImageManager(){};
		~CImageManager(){};

	private:
		MapImage _mapImage;
	};
}

#endif