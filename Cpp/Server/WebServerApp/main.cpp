#include "framework/websocket/websocketserver.h"
#include "framework/cdf_link.h"
#include "framework/cdf_common.h"
#include "engine/rmi/rmiinteface.h"

#include "App.h"
#include "Config/Config.h"
#include "Helper/PublicConfig.h"
#include "Db/DbHelper.h"

using namespace WebServerApp;

void waitStop()
{
#ifdef CDE_LINUX
	signal(SIGINT, sigFun);
	signal(SIGTERM, sigFun);
	signal(SIGUSR1, sigFun);
	exitEvent.wait(-1);
#else
	getchar();
#endif
}

int main(int argc, char ** argv)
{
	cde::CRMIServer rmiServer;

#ifndef _DEBUG
	std::string logDir = "WebServerApp_Log";
#else
	std::string logDir = "Log/WebServerApp_Log";
#endif
	cdf::CLoggerWriterPtr logWriter = new cdf::CLoggerWriter();
	logWriter->setFileDir(logDir.c_str());
	cdf::CWebsocketServer::instance()->setLogRoot(logDir);

	rmiServer.setConfigFile(engineConfig.c_str());
	//rmiServer.setCrossFile(crossFile.c_str());
	rmiServer.init(argc, argv, logWriter);

	//start App
	Application thisApp;

	if (thisApp.init())
	{
		int httpPort = CPublicConfig::instance()->getHttpPort();
		cdf::CWebsocketServer::instance()->startThread(httpPort);

		rmiServer.start();
#ifndef _DEBUG
		logWriter->setConsoleInfo(false);
#endif

	    rmiServer.waitStop();
		rmiServer.stop();
		thisApp.stop();
		cdf::CWebsocketServer::instance()->stop();
	}

	thisApp.fina();

	return 0;

	return 0;
}
