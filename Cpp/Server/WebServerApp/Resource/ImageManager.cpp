#include "ImageManager.h"
#include "Db/DaoManager.h"
#include "Helper/PublicConfig.h"
#include "Helper/ImageInfo.h"

#include "framework/log/loggerutil.h"
#include "framework/util/stringfun.h"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"

using namespace WebServerApp;

CImageManager * CImageManager::instance()
{
	static CImageManager _inst;

	return &_inst;
}

void CImageManager::loadAllImages()
{
	Message::Db::Tables::SeqTUserImg allImages;
	CDaoManager::instance()->getIUserImgDao()->loadAllUserImg(allImages);

	for (auto tImg : allImages)
	{
		CImagePtr imgPtr = new CImage(tImg);
		addImage(imgPtr);
	}
}

const CImagePtr CImageManager::findImage(int imgId)
{
	auto found = _mapImage.find(imgId);

	if (found != _mapImage.end())
	{
		return found->second;
	}

	return NULL;
}

const CImagePtr CImageManager::createImage(const std::string & filename, 
	const std::string & shortDesc, const std::string & imgBinary)
{
	cdf::CDateTime now;

	char buff[1024];
	sprintf_s(buff, sizeof(buff)-1, "%04d%02d%02d/",
		now.getYear(), now.getMonth(), now.getDay());

	std::string imgDir = CPublicConfig::instance()->getImgRoot() + "/" + buff;
	boost::filesystem::path imgPath(imgDir);

	if (!boost::filesystem::exists(imgPath))
	{
		if (!boost::filesystem::create_directories(imgPath))
		{
			CDF_LOG_TRACE("CImageManager::createImage", "Create Folder Failed: " << imgPath.generic_string());
			//return NULL;
		}
	}

	std::string extention;
	if (!CImageInfo::getImageType(imgBinary, extention))
	{
		CDF_LOG_TRACE("CImageManager::createImage", "Unknown Image Type");
	}

	std::string imgFileName = cdf::CStrFun::get_uuid() + extention;
	std::string fullImgFileName = imgDir + "/" + imgFileName;

	std::ofstream imgStream(fullImgFileName, std::ios::binary | std::ios::out);
	if (imgStream)
	{
		imgStream.write(imgBinary.c_str(), imgBinary.size());
	}
	else
	{
		CDF_LOG_TRACE("CImageManager::createImage", "Create File Failed: " << imgFileName);
		return NULL;
	}

	Message::Db::Tables::TUserImg tImg;
	tImg.imgPath = std::string(buff) + "/" + imgFileName;
	tImg.shortDesc = shortDesc;

	CImagePtr newImg = new CImage(tImg);
	CDaoManager::instance()->getIUserImgDao()->updateUserImg(newImg->getTUserImg());
	addImage(newImg);

	return newImg;
}

void CImageManager::addImage(const CImagePtr & imgPtr)
{
	_mapImage[imgPtr->getTUserImg().imgId] = imgPtr;
}
