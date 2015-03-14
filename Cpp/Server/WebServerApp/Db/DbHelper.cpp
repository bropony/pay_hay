#include "DbHelper.h"

using namespace WebServerApp;


void CDbHelper::updateTUser(const Message::Db::Tables::TUser & t)
{
	CDaoManager::instance()->getIUserDao()->updateUser(t);
}

void CDbHelper::updateTUserPost(const Message::Db::Tables::TUserPost & t)
{
	CDaoManager::instance()->getIUserPostDao();
}

void CDbHelper::updateTUserComment(const Message::Db::Tables::TUserComment & t)
{

}

void CDbHelper::updateTUserImg(const Message::Db::Tables::TUserImg & t)
{

}
