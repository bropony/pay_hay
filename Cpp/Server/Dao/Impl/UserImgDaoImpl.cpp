#include "Dao/Impl/UserImgDaoImpl.h"
Dao::Impl::CUserImgDaoImpl::CUserImgDaoImpl()
{
}
Dao::Impl::CUserImgDaoImpl::~CUserImgDaoImpl()
{
}


void Dao::Impl::CUserImgDaoImpl::loadAllUserImg(Message::Db::Tables::SeqTUserImg & userImgList)
{
	cdf::dao::SQuery query;
	cdf::dao::SCmpNode cmpNode;

	cmpNode.setColumnName(_imgPath);
	cmpNode.setString("");
	cmpNode.setEqualType(cdf::dao::EQUAL_TYPE_NOT_EQUAL);

	query.cmpNodes.push_back(cmpNode);

	find(query, userImgList);
}

void Dao::Impl::CUserImgDaoImpl::updateUserImg(const Message::Db::Tables::TUserImg & t)
{
	cdf::dao::SQuery query;
	cdf::dao::SCmpNode cmpNode;

	cmpNode.setColumnName(_imgId);
	cmpNode.setInt(t.imgId);

	query.cmpNodes.push_back(cmpNode);

	Message::Db::Tables::TUserImg r;
	if (find(query, r))
	{
		update(t);
	}
	else
	{
		save(const_cast<Message::Db::Tables::TUserImg &> (t));
	}
}
