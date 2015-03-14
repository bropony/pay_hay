#include "Dao/Impl/UserPostDaoImpl.h"
Dao::Impl::CUserPostDaoImpl::CUserPostDaoImpl()
{
}
Dao::Impl::CUserPostDaoImpl::~CUserPostDaoImpl()
{
}

void Dao::Impl::CUserPostDaoImpl::updateUserPost(const Message::Db::Tables::TUserPost & t)
{
	cdf::dao::SQuery query;
	cdf::dao::SCmpNode cmpNode;
	cmpNode.setColumnName(_postId);
	cmpNode.setInt(t.postId);
	query.cmpNodes.push_back(cmpNode);

	Message::Db::Tables::TUserPost r;
	if (find(query, r))
	{
		update(t);
	}
	else
	{
		save(const_cast<Message::Db::Tables::TUserPost &> (t));
	}
}

bool Dao::Impl::CUserPostDaoImpl::loadAllUserPosts(Message::Db::Tables::SeqTUserPost & postList)
{
	cdf::dao::SQuery query;
	cdf::dao::SCmpNode cmpNode;
	cmpNode.setColumnName(_userId);
	cmpNode.setInt(0);
	cmpNode.setEqualType(cdf::dao::EQUAL_TYPE_GRANTER);

	query.cmpNodes.push_back(cmpNode);

	find(query, postList);

	return true;
}
