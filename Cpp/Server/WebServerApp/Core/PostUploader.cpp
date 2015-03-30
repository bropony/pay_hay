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

void CPostUploader::startPost(int userId, const std::string & title, const std::string & content)
{
	auto found = _mapPostInst.find(userId);
	if (found != _mapPostInst.end())
	{
		endPost(found->first, found->second.postDt);

		_mapPostInst.erase(userId);
	}

	CPostInst postInst;
	postInst.title = title;
	postInst.content = content;
	postInst.postDt = cdf::CDateTime();
	postInst.imgIdex = 0;

	_mapPostInst[userId] = postInst;
}

int CPostUploader::addImg(int userId, const std::string & img, const std::string & shortDesc)
{
	auto found = _mapPostInst.find(userId);
	if (found == _mapPostInst.end())
	{
		CDF_LOG_TRACE("CPostUploader::addImg", "NoPost: " << userId);

		CImagePtr newImg = CImageManager::instance()->createImage(shortDesc, img);
		if (NULL != newImg)
		{
			return newImg->getTUserImg().imgId;
		}
		else
		{
			return 0;
		}
	}

	CImagePtr newImg = CImageManager::instance()->createImage(shortDesc, img);

	if (NULL != newImg)
	{
		found->second.msgIdList.push_back(newImg->getTUserImg().imgId);

		return newImg->getTUserImg().imgId;
	}

	return 0;
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
