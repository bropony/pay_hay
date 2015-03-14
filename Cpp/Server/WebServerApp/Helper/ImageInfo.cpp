#include "ImageInfo.h"
#include "framework/log/loggerutil.h"
#include <cstdio>

using namespace WebServerApp;

bool CImageInfo::getImageType(const std::string & img, std::string & imgType)
{
	//std::string magic = img.substr(0, 4);
	unsigned char magic[4];
	for (unsigned i = 0; i < 4; i++)
	{
		magic[i] = img[i];
	}

	if (magic[0] == 'G' && magic[1] == 'I' && magic[2] == 'F' /*&& magic[3] = '8'*/)
	{
		imgType = ".gif";
		return true;
	}
	
	if (magic[0] == 0xff && magic[1] == 0xd8)
	{
		imgType = ".jpg";
		return true;
	}

	if (magic[0] == 0x89 && magic[1] == 0x50 && magic[2] == 0x4e && magic[3] == 0x47)
	{
		imgType = ".png";
		return true;
	}

	if (magic[0] == 0x00 && magic[1] == 0x00 && magic[2] == 0x01 && magic[3] == 0x00)
	{
		imgType = ".ico";
		return true;
	}

	if (magic[0] == 0x42 && magic[1] == 0x4d)
	{
		imgType = ".bmp";
		return true;
	}

	imgType = ".png";
	return false;
}
