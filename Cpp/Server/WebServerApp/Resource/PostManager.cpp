#include "PostManager.h"
#include "User/UserManager.h"
#include "Db/DaoManager.h"
#include "Helper/Util.h"

using namespace WebServerApp;

CPostManager::CPostManager()
{

}

CPostManager::~CPostManager()
{

}

CPostManager * CPostManager::instance()
{
	static CPostManager _inst;

	return &_inst;
}

void CPostManager::loadAllPosts()
{
	Message::Db::Tables::SeqTUserPost allPosts;
	CDaoManager::instance()->getIUserPostDao()->loadAllUserPosts(allPosts);

	for (const auto tPost : allPosts)
	{
		CPostPtr post = new CPost(tPost);
		addPost(post);

		CUserManager::instance()->addPostId(tPost.userId, tPost.postId);
	}
}

const CPostPtr CPostManager::findPost(int postId)
{
	auto found = _mapPost.find(postId);
	if (found != _mapPost.end())
	{
		return found->second;
	}

	return NULL;
}

const CPostPtr CPostManager::createPost(int userId, const std::string & title,
	const std::string & content, const Message::Public::SeqInt & imgIdList, const cdf::CDateTime & postDt)
{
	Message::Db::Tables::TUserPost tPost;
	tPost.userId = userId;
	tPost.title = title;
	tPost.content = content;
	tPost.postDt = postDt;

	Json::Value jsImgList;
	for (auto imgId : imgIdList)
	{
		jsImgList.append(imgId);
	}

	tPost.imgList = jsImgList.toFastString();

	CPostPtr postPtr = new CPost(tPost);
	CDaoManager::instance()->getIUserPostDao()->updateUserPost(postPtr->getTUserPost());
	addPost(postPtr);

	return postPtr;
}

void CPostManager::addPost(const CPostPtr & post)
{
	int postId = post->getTUserPost().postId;

	_mapPost[postId] = post;
	_postIdList.push_back(postId);
}

void CPostManager::getPostIdList(int lastPostId, bool forNewPosts, Message::Public::SeqInt & postIdList)
{
	unsigned maxSize = 10;
	if (forNewPosts)
	{
		CUtil::getNewList(_postIdList, maxSize, lastPostId, postIdList);
	}
	else
	{
		CUtil::getOldList(_postIdList, maxSize, lastPostId, postIdList);
	}
}

void CPostManager::getPostList(const Message::Public::SeqInt & postIdList, Json::Value & jsRes)
{
	for (auto postId : postIdList)
	{
		CPostPtr postPtr = findPost(postId);
		if (NULL == postPtr)
		{
			CDF_LOG_TRACE("CPostManager::getPostList", "NoSuchPost: " << postId);
			continue;
		}

		Json::Value jsPost;
		postPtr->postToJs(jsPost);

		jsRes.append(jsPost);
	}
}

void CPostManager::getPostList(const Message::Public::SeqInt & postIdList, Rmi::SeqPost & postList)
{
	for (auto postId : postIdList)
	{
		CPostPtr postPtr = findPost(postId);
		if (NULL == postPtr)
		{
			CDF_LOG_TRACE("CPostManager::getPostList", "NoSuchPost: " << postId);
			continue;
		}

		Rmi::SPost post;
		postPtr->postToClient(post);

		postList.push_back(post);
	}
}
