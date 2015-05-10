#include "CommentManager.h"

#include "Db/DaoManager.h"

using namespace WebServerApp;

CCommentManager * CCommentManager::instance()
{
	static CCommentManager _inst;

	return &_inst;
}

void CCommentManager::loadAllComments()
{
	Message::Db::Tables::SeqTUserComment allUserComments;
	CDaoManager::instance()->getIUserCommentDao()->loadUserComment(0, allUserComments);

	for (auto t : allUserComments)
	{
		CCommentPtr commentPtr = new CComment(t);
		addComment(commentPtr);
	}
}

void CCommentManager::addComment(const CCommentPtr & commentPtr)
{
	int commentId = commentPtr->getTUserComment().commentId;
	if (_mapComment.find(commentId) == _mapComment.end())
	{
		_mapComment[commentId] = commentPtr;
		_mapPostComment[commentPtr->getTUserComment().postId].push_back(commentId);
	}
}

const CCommentPtr CCommentManager::createComment(int postId, int fromUserId, const std::string & fromNickName, const std::string & connent)
{
	Message::Db::Tables::TUserComment tComment;
	tComment.postId = postId;
	tComment.fromUserId = fromUserId;
	tComment.fromNickname = fromNickName;
	tComment.commentDt = cdf::CDateTime();
	tComment.content = connent;

	CDaoManager::instance()->getIUserCommentDao()->updateUserComment(tComment);

	CCommentPtr commentPtr = new CComment(tComment);
	addComment(commentPtr);

	return commentPtr;
}

void CCommentManager::getCommentsByPostId(int postId, Rmi::SeqComment & comments)
{
	auto found = _mapPostComment.find(postId);
	if (found == _mapPostComment.end())
	{
		return;
	}

	for (auto commentId : found->second)
	{
		auto commentFound = _mapComment.find(commentId);
		if (commentFound == _mapComment.end())
		{
			continue;
		}

		Rmi::SComment comment;
		commentFound->second->commentToClient(comment);

		comments.push_back(comment);
	}
}
