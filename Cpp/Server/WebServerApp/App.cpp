#include "framework/db/dbpublic.h"
#include "framework/db/mysql/mysqlpublic.h"
#include "framework/log/loggerutil.h"
#include "framework/xml/tinyxml/tinyxmlp.h"
#include "framework/db/cached/cachedmanager.h"
#include "framework/websocket/websocketserver.h"

#include "Dao/Impl/Base/CachedTablesInit.h"

#include "App.h"
#include "Config/Config.h"
#include "Config/GameDataLoader.h"
#include "Helper/PublicConfig.h"
#include "User/UserManager.h"
#include "Core/MessageHandler.h"
#include "Core/EventHandlerImpl.h"
#include "Resource/PostManager.h"
#include "Resource/ImageManager.h"
#include "Resource/CommentManager.h"

using namespace WebServerApp;

Application::Application()
{
}

Application::~Application()
{

}

void Application::initWebSocket()
{
	if (CPublicConfig::instance()->getDocRoot().empty())
	{
		cdf::CWebsocketServer::instance()->setDocRoot(htmlRoot);
	}
	else
	{
		cdf::CWebsocketServer::instance()->setDocRoot(CPublicConfig::instance()->getDocRoot());
	}

	cg::CMassageHandlerPtr msgHandler = new cg::CMassageHandler();
	msgHandler->setEventHandler(new CEventHandlerImpl());
	cdf::CWebsocketServer::instance()->setMessageHandler(msgHandler);
}

void Application::initThreadFun()
{
	cdf::CThreadManager::threadStart = threadStart;
	cdf::CThreadManager::threadEnd = threadEnd;
}

void Application::initPoolConnection()
{
	cdf::CXml xml;

	CDF_LOG_TRACE("[Application::initPoolConnection]", "read app config file:" << dbConnectioConfig);
	xml.loadFile(dbConnectioConfig.c_str());

	std::string url = xml.getString("db/url");
	CPublicConfig::dbUrlReplace(url);
	CDF_LOG_TRACE("[Application::initPoolConnection]", "db/url:" << url);

	int maxconn = xml.getInt("db/maxconn");
	std::string user = xml.getString("db/user");
	std::string password = xml.getString("db/password");
	CPublicConfig::dbPwdReplace(password);
	CDF_LOG_TRACE("[Application::initPoolConnection]", "db/pwd:" << password);

	cdf::CPoolConnectionManager::initialize(url.c_str(), maxconn, user.c_str(), password.c_str());

	CDF_LOG_TRACE("[Application::initPoolConnection]", "read cache config file:" << dbCachedConfig);

	int cacheInitSize = CPublicConfig::instance()->getDbCacheInitSize();

	if (!cdf::cached::CCachedManager::instance()->init(dbCachedConfig/*, cacheInitSize*/))
	{
		CDF_THROW_EXCEPTION(cdf::CException, "init " << dbCachedConfig << " error");
	}
}

void Application::threadStart(void*)
{
	cdf::cached::CCachedManager::instance()->getDb().attach();
}

void Application::threadEnd(void*)
{
	if (cdf::cached::CCachedManager::instance()->getDb().isOpen())
	{
		cdf::cached::CCachedManager::instance()->getDb().detach();
	}
}

bool Application::init()
{
	CDE_BEGIN_TRY
	{
		if (!CGameDataLoader::instance()->loadGameData())
		{
			return false;
		}

		//init
	    Dao::Impl::initCachedTables();

		CDF_LOG_TRACE("Application::init", "go");
		cdf::CTinyXml::initialize();
		initThreadFun();
		cdf::mysql::CMySQLConnection::initialize();

		CDF_LOG_TRACE("Application::init", "CPublicConfig::loadXML");
		CPublicConfig::instance()->loadXML(publicConfig);

		CDF_LOG_TRACE("Application::init", "InitPoolConnection");
		initPoolConnection();

		CDF_LOG_TRACE("Application::init", "LoadUsers");
		CUserManager::instance()->loadUsers();

		CDF_LOG_TRACE("Application::init", "Loading Resources");
		CPostManager::instance()->loadAllPosts();
		CImageManager::instance()->loadAllImages();
		CCommentManager::instance()->loadAllComments();

		CDF_LOG_TRACE("Application::init", "Init WebSocket");
		initWebSocket();
	}
	CDE_END_TRY_RETURN(__FILE__, __LINE__, false);

	return true;
}

void Application::stop()
{
	cdf::cached::CCachedManager::instance()->stop();
}

void Application::fina()
{
	CDF_LOG_TRACE("Application::fina", "go");
	cdf::cached::CCachedManager::instance()->fina();
	cdf::CPoolConnectionManager::finalize();
	cdf::mysql::CMySQLConnection::finalize();
}
