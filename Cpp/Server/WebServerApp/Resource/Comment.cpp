#include "Comment.h"
#include "Db/DbHelper.h"
#include "User/UserManager.h"

using namespace WebServerApp;

CComment::CComment(const Message::Db::Tables::TUserComment & tUserComment)
:_tUserComment(tUserComment)
{

}

Message::Db::Tables::TUserComment & CComment::getTUserComment()
{
	return _tUserComment;
}

void CComment::updateToDb()
{
	CDbHelper::updateTUserComment(_tUserComment);
}

void CComment::commentToClient(Rmi::SComment & comment)
{
	comment.commentDt = _tUserComment.commentDt;
	comment.userId = _tUserComment.fromUserId;
	comment.nickname = _tUserComment.fromNickname;
	comment.content = _tUserComment.content;

	CUserPtr userPtr = CUserManager::instance()->findUser(_tUserComment.fromUserId);
	if (NULL != userPtr)
	{
		comment.avatarImgId = userPtr->getAvatarImgId();
	}
}
