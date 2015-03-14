#ifndef __WEBSERVERAPP_DB_DB_HELPER_H__
#define __WEBSERVERAPP_DB_DB_HELPER_H__

#include "Db/DaoManager.h"

namespace WebServerApp
{
	class CDbHelper
	{
	public:
		static void updateTUser(const Message::Db::Tables::TUser & t);
		static void updateTUserPost(const Message::Db::Tables::TUserPost & t);
		static void updateTUserComment(const Message::Db::Tables::TUserComment & t);
		static void updateTUserImg(const Message::Db::Tables::TUserImg & t);
	private:
		CDbHelper();
		~CDbHelper();
	};
}

#endif