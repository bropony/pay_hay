#include "PostUploader.h"
#include "Resource/ImageManager.h"
#include "Resource/PostManager.h"
#include "framework/log/loggerutil.h"

using namespace WebServerApp;

CPostUploader * CPostUploader::instance()
{
	static CPostUploader _inst;

	return &_inst;
}

void CPostUploader::startPost(int userId, const std::string & title, const std::string & content, const Json::Value & jsImages)
{
	auto found = _mapPostInst.find(userId);
	if (found != _mapPostInst.end())
	{
		endPost(found->first, found->second.postDt);

		_mapPostInst.erase(found);
	}

	CPostInst postInst;
	postInst.title = title;
	postInst.content = content;
	postInst.jsImages = jsImages;
	postInst.postDt = cdf::CDateTime();
	postInst.imgIdex = 0;

	_mapPostInst[userId] = postInst;
}

void CPostUploader::addImg(int userId, const std::string & img)
{
	auto found = _mapPostInst.find(userId);
	if (found == _mapPostInst.end())
	{
		CDF_LOG_TRACE("CPostUploader::addImg", "NoPost: " << userId);

		CImageManager::instance()->createImage("unknow.jpg", "unknownPost", img);
		return;
	}

	std::string fileName = "oops.jpg";
	std::string shortDesc = "oops";
	auto postInst = found->second;
	if (postInst.imgIdex < postInst.jsImages.size())
	{
		if (postInst.jsImages[postInst.imgIdex].size() == 2)
		{
			fileName = postInst.jsImages[postInst.imgIdex][unsigned(0)].asString();
			shortDesc = postInst.jsImages[postInst.imgIdex][unsigned(1)].asString();
		}

		postInst.imgIdex++;
	}

	CImagePtr newImg = CImageManager::instance()->createImage(fileName, shortDesc, img);

	if (NULL != newImg)
	{
		found->second.msgIdList.push_back(newImg->getTUserImg().imgId);
	}
}

int CPostUploader::endPost(int userId, cdf::CDateTime & postDt)
{
	auto found = _mapPostInst.find(userId);
	if (found == _mapPostInst.end())
	{
		CDF_LOG_TRACE("CPostUploader::endPost", "NoPost: " << userId);
		return 0;
	}

	const auto postInst = found->second;
	CPostPtr newPost = CPostManager::instance()->createPost(userId, postInst.title, 
		postInst.content, postInst.msgIdList, postInst.postDt);

	postDt = postInst.postDt;
	_mapPostInst.erase(found);


	return newPost->getTUserPost().postId;
}
