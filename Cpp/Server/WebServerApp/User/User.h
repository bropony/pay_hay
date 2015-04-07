#ifndef __WEBSERVERAPP_USER_USER_H__
#define __WEBSERVERAPP_USER_USER_H__

#include "framework/cdf_common.h"
#include "framework/util/refshared.h"
#include "framework/websocket/websocketserver.h"
#include "framework/json/value.h"

#include "Message/Db/Tables/TUser.h"
#include "Message/Public/CdlPublic.h"

namespace WebServerApp
{
	class CUser
		: public virtual cdf::CRefShared
	{
	public:
		CUser(const Message::Db::Tables::TUser & tUser);
		~CUser();
		Message::Db::Tables::TUser & getTUser();
		int getUserId();
		const std::string & getAccount();
		const std::string & getNickname();

		const std::string & getAvatar();
		int getAvatarImgId();
		void updateAvatar(int imgId, const std::string & avatarImg);

		//验证
		bool isPasswdMatched(const std::string & passwd);
		void setPasswd(const std::string & passwd);
		const std::string & getSessionKey();
		void updateSessionKey();
		bool isSessionKeyMatched(const std::string & sessionKey);

		//连接
		WSConnectionPtr getWSConn();
		void setWSConn(WSConnectionPtr conn);

		void addPostId(int postId);
		void delPostId(int postId);
		void getNewer10PostId(int postId, Json::Value & jsList);
		void getNewer10PostId(int postId, Message::Public::SeqInt & postIdList);
		void getOlder10PostId(int postId, Json::Value & jsList);
		void getOlder10PostId(int postId, Message::Public::SeqInt & postIdList);

		//保存到数据库
		void updateToDb();

	private:
		WSConnectionPtr _wsConnectionPtr;
		std::string _sessionKey;
		std::string _avatar;

		Message::Db::Tables::TUser _tUser;
		Message::Public::SeqInt _postIdList;
	};
	typedef cdf::CHandle<CUser> CUserPtr;
	typedef std::map<int, CUserPtr> MapIdUser;
	typedef std::map<std::string, CUserPtr> MapAccountUser;
	typedef std::map<std::string, CUserPtr> MapNicknameUser;
	typedef std::map<std::string, CUserPtr> MapSessionUser;
}

#endif