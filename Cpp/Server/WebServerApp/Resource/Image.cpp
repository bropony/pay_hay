#include "Image.h"
#include <fstream>

#include "Helper/PublicConfig.h"

using namespace WebServerApp;

CImage::CImage(const Message::Db::Tables::TUserImg & tImg)
:_tUserImg(tImg)
{

}

Message::Db::Tables::TUserImg & CImage::getTUserImg()
{
	return _tUserImg;
}

const std::string & CImage::getImgBin()
{
	if (_imgBin.empty())
	{
		std::string absImgPath = CPublicConfig::instance()->getImgRoot() + "/" + _tUserImg.imgPath;
		std::ifstream ifs(absImgPath, std::ios::binary);
		if (!ifs)
		{
			return "oops";
		}

		ifs.seekg(0, std::ios::end);
		_imgBin.reserve(ifs.tellg());
		ifs.seekg(0, std::ios::beg);

		_imgBin.assign((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());
	}

	_lastVisitedDt = cdf::CDateTime();

	return _imgBin;
}

void CImage::releaseExpiredImgMemory(const cdf::CDateTime & nowDt, int timeoutSecs)
{
	if (timeoutSecs <= 0)
	{
		timeoutSecs = 5 * 3600;
	}

	if ((nowDt - _lastVisitedDt).getTotalSeconds() >= timeoutSecs)
	{
		_imgBin.clear();
	}
}

const std::string & CImage::getDesc()
{
	return _tUserImg.shortDesc;
}
