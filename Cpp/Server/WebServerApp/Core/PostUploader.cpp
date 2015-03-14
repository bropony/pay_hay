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

		_mapPostInst.erase(found);
	}
}

void CPostUploader::addImg(int userId, const std::string & fileName, const std::string & shortDesc, const std::string & img)
{
	auto found = _mapPostInst.find(userId);
	if (found == _mapPostInst.end())
	{
		CDF_LOG_TRACE("CPostUploader::addImg", "NoPost: " << userId);
		//return;
	}

	CImagePtr newImg = CImageManager::instance()->createImage(fileName, shortDesc, img);

	if (NULL != newImg && found != _mapPostInst.end())
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
	return newPost->getTUserPost().postId;
}
