#include "Post.h"
#include "User/UserManager.h"
#include "Db/DbHelper.h"

using namespace WebServerApp;

CPost::CPost(const Message::Db::Tables::TUserPost & userPost)
:_tUserPost(userPost)
{

}

Message::Db::Tables::TUserPost & CPost::getTUserPost()
{
	return _tUserPost;
}

void CPost::postToJs(Json::Value & js)
{
	js["postId"] = _tUserPost.postId;
	js["userId"] = _tUserPost.userId;
	js["title"] = _tUserPost.title;
	js["content"] = _tUserPost.content;

	CUserPtr userPtr = CUserManager::instance()->findUser(_tUserPost.userId);
	if (NULL != userPtr)
	{
		js["account"] = userPtr->getAccount();
		js["nickname"] = userPtr->getNickname();
	}

	Json::Value jsImgList;
	jsImgList.parse(_tUserPost.imgList);
	for (unsigned i = 0; i < jsImgList.size(); i++)
	{
		int imgId = jsImgList[i].asInt();
		if (imgId > 0)
		{
			js["imgList"].append(imgId);
		}
	}

	js["nlike"] = _tUserPost.nlike;
	js["ndislike"] = _tUserPost.ndislike;
	js["ncomment"] = _tUserPost.ncomment;
	js["postDt"] = _tUserPost.postDt.getTotalSecond();
}

void CPost::postToClient(Rmi::SPost & post)
{
	post.postId = _tUserPost.postId;
	post.authorUserId = _tUserPost.userId;
	post.title = _tUserPost.title;
	post.content = _tUserPost.content;

	CUserPtr userPtr = CUserManager::instance()->findUser(_tUserPost.userId);
	if (NULL != userPtr)
	{
		post.authorAccount = userPtr->getAccount();
		post.authorNickname = userPtr->getNickname();
		post.authorAvatarImgId = userPtr->getAvatarImgId();
	}

	Json::Value jsImgList;
	jsImgList.parse(_tUserPost.imgList);
	for (unsigned i = 0; i < jsImgList.size(); i++)
	{
		int imgId = jsImgList[i].asInt();
		if (imgId > 0)
		{
			post.imgIdList.push_back(imgId);
		}
	}

	post.likes = _tUserPost.nlike;
	post.dislikes = _tUserPost.ndislike;
	post.comments = _tUserPost.ncomment;
	post.postDt = _tUserPost.postDt;
}

void CPost::updateToDb()
{
	CDbHelper::updateTUserPost(_tUserPost);
}

