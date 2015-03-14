#include "Image.h"

using namespace WebServerApp;

CImage::CImage(const Message::Db::Tables::TUserImg & tImg)
:_tUserImg(tImg)
{

}

Message::Db::Tables::TUserImg & CImage::getTUserImg()
{
	return _tUserImg;
}
