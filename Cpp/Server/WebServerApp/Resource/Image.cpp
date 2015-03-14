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

	return _imgBin;
}
