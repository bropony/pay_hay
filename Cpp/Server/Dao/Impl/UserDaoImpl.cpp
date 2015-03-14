#include "Dao/Impl/UserDaoImpl.h"
Dao::Impl::CUserDaoImpl::CUserDaoImpl()
{
}
Dao::Impl::CUserDaoImpl::~CUserDaoImpl()
{
}

bool Dao::Impl::CUserDaoImpl::loadUser(int userId, Message::Db::Tables::TUser & tUser)
{
	cdf::dao::SQuery query;
	cdf::dao::SCmpNode cmpNode;
	cmpNode.setColumnName(_userId);
	cmpNode.setInt(userId);

	query.cmpNodes.push_back(cmpNode);

	return find(query, tUser);
}

bool Dao::Impl::CUserDaoImpl::loadUser(const std::string & account, Message::Db::Tables::TUser & tUser)
{
	cdf::dao::SQuery query;
	cdf::dao::SCmpNode cmpNode;
	cmpNode.setColumnName(_account);
	cmpNode.setString(account);

	query.cmpNodes.push_back(cmpNode);

	return find(query, tUser);
}

void Dao::Impl::CUserDaoImpl::loadAllUsers(Message::Db::Tables::SeqTUser & allTUsers)
{
	cdf::dao::SQuery query;
	cdf::dao::SCmpNode cmpNode;
	cmpNode.setColumnName(_account);
	cmpNode.setString("");
	cmpNode.setEqualType(cdf::dao::EQUAL_TYPE_NOT_EQUAL);

	query.cmpNodes.push_back(cmpNode);

	find(query, allTUsers);
}

void Dao::Impl::CUserDaoImpl::updateUser(const Message::Db::Tables::TUser & tUser)
{
	cdf::dao::SQuery query;
	cdf::dao::SCmpNode cmpNode;
	cmpNode.setColumnName(_userId);
	cmpNode.setInt(tUser.userId);

	query.cmpNodes.push_back(cmpNode);

	Message::Db::Tables::TUser t;
	if (find(query, t))
	{
		update(tUser);
	}
	else
	{
		save(const_cast< Message::Db::Tables::TUser & >(tUser));
	}
}
