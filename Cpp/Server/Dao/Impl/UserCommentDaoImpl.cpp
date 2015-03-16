#include "Dao/Impl/UserCommentDaoImpl.h"
Dao::Impl::CUserCommentDaoImpl::CUserCommentDaoImpl()
{
}
Dao::Impl::CUserCommentDaoImpl::~CUserCommentDaoImpl()
{
}

bool Dao::Impl::CUserCommentDaoImpl::loadUserComment(int postId, Message::Db::Tables::SeqTUserComment & allUserComments)
{
	cdf::dao::SQuery query;

	cdf::dao::SCmpNode cmpNode;
	cmpNode.setColumnName(_postId);
	cmpNode.setInt(postId);
	if (postId <= 0)
	{
		cmpNode.setEqualType(cdf::dao::EQUAL_TYPE_GRANTER);
	}
	else
	{
		cmpNode.setEqualType(cdf::dao::EQUAL_TYPE_EQUAL);
	}

	query.cmpNodes.push_back(cmpNode);

	find(query, allUserComments);

	return true;
}


void Dao::Impl::CUserCommentDaoImpl::updateUserComment(const Message::Db::Tables::TUserComment & t)
{
	cdf::dao::SQuery query;

	cdf::dao::SCmpNode cmpNode;
	cmpNode.setColumnName(_postId);
	cmpNode.setInt(t.postId);

	query.cmpNodes.push_back(cmpNode);

	Message::Db::Tables::TUserComment r;
	if (find(query, r))
	{
		update(t);
	}
	else
	{
		save(const_cast<Message::Db::Tables::TUserComment &> (t));
	}
}
