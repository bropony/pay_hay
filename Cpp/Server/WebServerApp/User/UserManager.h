#ifndef __WEBSERVERAPP_USER_USERMANAGER_H__
#define __WEBSERVERAPP_USER_USERMANAGER_H__

#include "User/User.h"

namespace WebServerApp
{
	class CUserManager
	{
	public:
		static CUserManager * instance();
		void loadUsers();

		const CUserPtr findUser(int userId);
		const CUserPtr findUser(const std::string & account);
		const CUserPtr findUserByNickname(const std::string & nickname);
		bool hasUserExisted(const std::string & account);
		bool hasUserExistedByNickname(const std::string & nickname);

		const CUserPtr createUser(const std::string & account, const std::string & nickname, const std::string & passwd);
		void addUser(const CUserPtr & user);

		void addPostId(int userId, int postId);
	private:
		CUserManager();
		~CUserManager();

	private:
		MapIdUser _mapIdUser;
		MapAccountUser _mapAccountUser;
		MapNicknameUser _mapNicknameUser;
	};
}

#endif