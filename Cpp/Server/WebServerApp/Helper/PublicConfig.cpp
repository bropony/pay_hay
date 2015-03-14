#include "Helper/PublicConfig.h"
#include "framework/util/stringfun.h"
#include "framework/util/typetransform.h"
#include <iostream> 
#include <fstream>

using namespace WebServerApp;

int CPublicConfig::getXmlInt(const cdf::CXml & xml, const std::string & node, 
	bool mustExist /*= true*/, int defVal /*= 0*/)
{
	std::string realNode = std::string("root/") + node;
	int res = xml.getInt(realNode, "1/1", mustExist, defVal);
	return res;
}

const std::string CPublicConfig::getXmlString(const cdf::CXml & xml, const std::string & node, 
	bool mustExist /*= true*/, const std::string & defVal/* = ""*/)
{
	std::string realNode = std::string("root/") + node;
	std::string res = xml.getString(realNode, "1/1", mustExist, defVal);
	return res;
}

CPublicConfig::CPublicConfig(): _randInt()
{
}

CPublicConfig::~CPublicConfig()
{
}

void CPublicConfig::loadXML(const std::string& file)
{
	cdf::CXml xml;
	xml.loadFile(file.c_str());
	std::string serverOpenDtStr = getXmlString(xml, KEY_SERVER_OPEN_DT, false, "2013-12-01 00:00:00");
	_serverOpenDt.parse(serverOpenDtStr.c_str(), "YYYY-MM-DD hh:mm:ss");
	_innerKey = getXmlString(xml, KEY_INNER_KEY);
	_clientPasswd = getXmlString(xml, KEY_CLIENT_PASSWD);
	_serverId = getXmlInt(xml, KEY_SERVER_ID);
	_serverName = getXmlString(xml, KEY_SERVER_NAME);
	_platformId = getXmlInt(xml, KEY_PLATFORM_ID);
	_platformName = getXmlString(xml, KEY_PLATFORM_NAME);

	_dbOneHostIp = getXmlString(xml, KEY_DB_ONE_HOST_IP);
	_dbTwoHostIp = getXmlString(xml, KEY_DB_TWO_HOST_IP);
	_dbOneHostPort = getXmlString(xml, KEY_DB_ONE_HOST_PORT);
	_dbTwoHostPort = getXmlString(xml, KEY_DB_TWO_HOST_PORT);
	_gameAppHostDomain = getXmlString(xml, KEY_GAME_APP_HOST_DOMAIN);
	_loginAppHostDomain = getXmlString(xml, KEY_LOGIN_APP_HOST_DOMAIN);
	_serverInnerIpOne = getXmlString(xml, KEY_SERVER_INNER_IP_ONE);
	_serverInnerIpTwo = getXmlString(xml, KEY_SERVER_INNER_IP_TWO, false, _serverInnerIpOne);

	_dbPasswd = getXmlString(xml, KEY_DB_PWD);
	_dbVersion = getXmlString(xml, KEY_DB_VERSION);
	_dbCacheInitSize = getXmlInt(xml, KEY_DB_CACHE_INIT_SIZE, false, 0);

	_changePort = getXmlString(xml, KEY_CHANGE_PORT);
	_httpPort = getXmlInt(xml, KEY_HTTP_PORT, false, 9600);
	_docRoot = getXmlString(xml, KEY_DOC_ROOT, false);
	_imgRoot = getXmlString(xml, KEY_IMG_ROOT, true);

	_isCensorshipOn = (getXmlInt(xml, KEY_CENSORSHIP, false, 1) != 0);
}


CPublicConfig* CPublicConfig::instance()
{
	static CPublicConfig inst;
	return &inst;
}

void CPublicConfig::reload()
{
	//cdf::CXml xml;
	//xml.loadFile(publicConfig.c_str());
}

const std::string CPublicConfig::parseUrl(const std::string & oldUrl)
{
	if (oldUrl.empty()) return oldUrl;

	std::vector<std::string> vStr;
	cdf::CStrFun::split_str( vStr, oldUrl.c_str(), ":" );
	if (vStr.size() != 2)
	{
		throw std::string("urlError: ") + oldUrl;
	}

	std::string& ipPart = vStr[0];
	std::string portPart = vStr[1];

	std::size_t found = std::string::npos;
	found = portPart.find(KEY_CHANGE_PORT.c_str());
	if (std::string::npos != found)
	{
		portPart.replace(found, KEY_CHANGE_PORT.size(), 
			CPublicConfig::instance()->getChangePort());
	}

	std::string newUrl = oldUrl;
	if (ipPart == KEY_GAME_APP_HOST_DOMAIN)
	{
		newUrl = getGameAppHostDomain() + ":" + portPart;
	}
	else if (ipPart == KEY_LOGIN_APP_HOST_DOMAIN)
	{
		newUrl = getLoginAppHostDomain() + ":" + portPart;
	}
	else if (ipPart == KEY_DB_ONE_HOST_IP)
	{
		newUrl = getDbOneHostIp() + ":" + portPart;
	}
	else if (ipPart == KEY_DB_TWO_HOST_IP)
	{
		newUrl = getDbTwoHostIp() + ":" + portPart;
	}
	else if (ipPart == KEY_SERVER_INNER_IP_ONE)
	{
		newUrl = getServerInnerIpOne() + ":" + portPart;
	}
	else if (ipPart == KEY_SERVER_INNER_IP_TWO)
	{
		newUrl = getServerInnerIpTwo() + ":" + portPart;
	}
	else
	{
		newUrl = ipPart + ":" + portPart;
	}

	return newUrl;
}


void CPublicConfig::dbUrlReplace(std::string& url)
{
	std::size_t found = std::string::npos;
	found = url.find(KEY_DB_ONE_HOST_IP.c_str());
	if (std::string::npos != found)
	{
		url.replace(found, KEY_DB_ONE_HOST_IP.size(), CPublicConfig::instance()->getDbOneHostIp());
	}

	found = url.find(KEY_DB_ONE_HOST_PORT.c_str());
	if (std::string::npos != found)
	{
		url.replace(found, KEY_DB_ONE_HOST_PORT.size(), CPublicConfig::instance()->getDbOneHostPort());
	}

	found = url.find(KEY_DB_TWO_HOST_IP.c_str());
	if (std::string::npos != found)
	{
		url.replace(found, KEY_DB_TWO_HOST_IP.size(), CPublicConfig::instance()->getDbTwoHostIp());
	}

	found = url.find(KEY_DB_TWO_HOST_PORT.c_str());
	if (std::string::npos != found)
	{
		url.replace(found, KEY_DB_TWO_HOST_PORT.size(), CPublicConfig::instance()->getDbTwoHostPort());
	}

	found = url.find(KEY_DB_VERSION.c_str());
	if (std::string::npos != found)
	{
		url.replace(found, KEY_DB_VERSION.size(), CPublicConfig::instance()->getDbVersion());
	} 
}

void CPublicConfig::dbPwdReplace(std::string& pwd)
{
	std::size_t found = std::string::npos;
	found = pwd.find(KEY_DB_PWD.c_str());
	if (std::string::npos != found)
	{
		pwd.replace(found, KEY_DB_PWD.size(), CPublicConfig::instance()->getDbPasswd());
	}
}