#include "Image.h"
#include <fstream>

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
		std::ifstream ifs(_tUserImg.imgPath, std::ios::binary);
		if (!ifs)
		{
			return "";
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
