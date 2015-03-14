#ifndef __WEBSERVERAPP_CONFIG_CONFIG_H__
#define __WEBSERVERAPP_CONFIG_CONFIG_H__

#include <string>

#define JOIN_PATH(parent, child) parent + "/" + child;
namespace WebServerApp
{
	const static std::string configRoot = "../config";
	const static std::string publicConfig = JOIN_PATH(configRoot, "public_config.xml");
	const static std::string engineConfig = JOIN_PATH(configRoot, "engine_config.xml");

	const static std::string dbConnectioConfig = JOIN_PATH(configRoot, "db_connection_config.xml");
	const static std::string dbCachedConfig = JOIN_PATH(configRoot, "db_cache_config.xml");

	const std::string filterNameFile = JOIN_PATH(configRoot, "filterChat.txt");
	const std::string netConfig = JOIN_PATH(configRoot, "net_config.xml");

	const std::string htmlRoot = JOIN_PATH(configRoot, "html");

	const char FIRST_LEVEL_STR_INTERVAL_CHAR = '#';			// 一级别字符串分隔符
	const char SECOND_LEVEL_STR_INTERVAL_CHAR = ',';		// 二级别字符串分隔符
}

#endif