#ifndef _COMM_PUBLIC_CONFIG_H_
#define _COMM_PUBLIC_CONFIG_H_

#include "string"
//#include "Common/Core/PublicDef.h"
#include "framework/xml/xml.h"

namespace WebServerApp
{
	const std::string KEY_SERVER_OPEN_DT = "ServerOpenDt";
	const std::string KEY_INNER_KEY = "InnerKey";
	const std::string KEY_CLIENT_PASSWD = "ClientPasswd";
	const std::string KEY_SERVER_ID = "ServerId";
	const std::string KEY_SERVER_NAME = "ServerName";
	const std::string KEY_PLATFORM_ID = "PlatformId";
	const std::string KEY_PLATFORM_NAME = "PlatformName";

	const std::string KEY_DB_ONE_HOST_IP = "DbOneHostIp";		// 第一数据库服务器主机IP
	const std::string KEY_DB_TWO_HOST_IP = "DbTwoHostIp";		// 第二数据库服务器主机IP
	const std::string KEY_DB_ONE_HOST_PORT = "DbOneHostPort";		// 第一数据库服务器主机Port
	const std::string KEY_DB_TWO_HOST_PORT = "DbTwoHostPort";		// 第二数据库服务器主机Port
	const std::string KEY_GAME_APP_HOST_DOMAIN = "GameAppHostDomain"; // 游戏APP域名
	const std::string KEY_LOGIN_APP_HOST_DOMAIN = "LoginAppHostDomain"; //登录App域名
	const std::string KEY_SERVER_INNER_IP_ONE = "ServerInnerIpOne"; //内部IP1
	const std::string KEY_SERVER_INNER_IP_TWO = "ServerInnerIpTwo"; //内部IP2

	const std::string KEY_DB_PWD = "DbPwd";						//数据库密码
	const std::string KEY_DB_VERSION = "DbVersion";			    // 数据库版本
	const std::string KEY_DB_CACHE_INIT_SIZE = "DbCacheInitSize";//共享内存初始大小

	const std::string KEY_CHANGE_PORT = "ChangePort";			// 可变端口
	const std::string KEY_CENSORSHIP = "Censorship";            // 敏感词监控
	const std::string KEY_HTTP_PORT = "HttpPort";               // http端口
	const std::string KEY_DOC_ROOT = "DocRoot";                 // http文件路径
	const std::string KEY_IMG_ROOT = "ImgRoot";                 // 图片路径
 
	class CPublicConfig
	{
	public:
		static int getXmlInt(const cdf::CXml & xml, const std::string & node, bool mustExist = true, int defVal = 0);
		static const std::string getXmlString(const cdf::CXml & xml, const std::string & node, bool mustExist = true, 
			const std::string & defVal = "");

		/*
		* db url replace
		* @param url
		*/
		static void dbUrlReplace(std::string& url);

		/*
		* db pwd replace
		*/
		static void dbPwdReplace(std::string& pwd);

	public:
		static CPublicConfig* instance();

		//void makeEntityId(int id, int type, EntityId& entityId);
		//void makeEntityId(int id, int type, int serverId, int platformId, EntityId& entityId);

		void loadXML(const std::string& file);

		void reload();

		const cdf::CDateTime & getServerOpenDt() const {return _serverOpenDt;}
		const cdf::CDateTime & getServerMergeDt() const {return _serverMergeDt;}
		const std::string & getInnerKey() const {return _innerKey;}
		const std::string & getClientPasswd() const {return _clientPasswd;}
		int getServerId() const {return _serverId;}
		const std::string & getServerName() const {return _serverName;}
		int getPlatformId() const {return _platformId;}
		const std::string & getPlatformName() const {return _platformName;}

		const std::string & getDbOneHostIp() const {return _dbOneHostIp;}
		const std::string & getDbTwoHostIp() const {return _dbTwoHostIp;}
		const std::string & getDbOneHostPort() const {return _dbOneHostPort;}
		const std::string & getDbTwoHostPort() const {return _dbTwoHostPort;}
		const std::string & getGameAppHostDomain() const {return _gameAppHostDomain;}
		const std::string & getLoginAppHostDomain() const {return _loginAppHostDomain;}
		const std::string & getServerInnerIpOne() const {return _serverInnerIpOne;}
		const std::string & getServerInnerIpTwo() const {return _serverInnerIpTwo;}

		const std::string & getDbPasswd() const {return _dbPasswd;}
		const std::string & getDbVersion() const {return _dbVersion;}
		int getDbCacheInitSize() const {return _dbCacheInitSize;}
		const std::string & getChangePort() const {return _changePort;}

		const std::string parseUrl(const std::string & oldUrl);

		void setServerRandInt(int i){_randInt = i;}
		int getServerRandInt(){return _randInt;}

		void enableCensorship(bool b){_isCensorshipOn = b;}
		bool isCensorshipEnabled(){return _isCensorshipOn;}

		int getHttpPort(){ return _httpPort; }
		const std::string & getDocRoot(){ return _docRoot; }
		const std::string & getImgRoot(){ return _imgRoot; }

	private:
		CPublicConfig();
		virtual ~CPublicConfig();

	private:
		cdf::CDateTime _serverOpenDt;
		cdf::CDateTime _serverMergeDt;
		std::string _innerKey;
		std::string _clientPasswd;
		int _serverId;
		std::string _serverName;
		int _platformId;
		std::string _platformName;

		std::string _dbOneHostIp;
		std::string _dbTwoHostIp;
		std::string _dbOneHostPort;
		std::string _dbTwoHostPort;
		std::string _gameAppHostDomain;
		std::string _loginAppHostDomain;
		std::string _serverInnerIpOne;
		std::string _serverInnerIpTwo;

		std::string _dbPasswd;
		std::string _dbVersion;
		int _dbCacheInitSize;
		std::string _changePort;
		int _httpPort;
		std::string _docRoot;
		std::string _imgRoot;

		int _randInt;

		bool _isCensorshipOn;
	};
}
#endif
