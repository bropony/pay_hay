#include "Comment.h"
#include "Db/DbHelper.h"

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
