#ifndef __WEBSERAPP_RESOURCE_IMAGE_H__
#define __WEBSERAPP_RESOURCE_IMAGE_H__

#include "framework/util/refshared.h"
#include "Message/Db/Tables/TUserImg.h"

namespace WebServerApp
{
	class CImage
		:public virtual cdf::CRefShared
	{
	public:
		CImage(const Message::Db::Tables::TUserImg & tImg);

		Message::Db::Tables::TUserImg & getTUserImg();

	private:
		Message::Db::Tables::TUserImg _tUserImg;
	};
	typedef cdf::CHandle<CImage> CImagePtr;
	typedef std::map<int, CImagePtr> MapImage;
}

#endif