#ifndef __WEBSOCKETAPP_APP_H__
#define __WEBSOCKETAPP_APP_H__

#include "framework/xml/xml.h"
#include "engine/rmi/rmi_common.h"

namespace WebServerApp
{
	class Application
	{
	public:
		Application();
		~Application();

		void initWebSocket();
		void initThreadFun();
		void initPoolConnection();
		static void threadStart(void*);
		static void threadEnd(void*);

		bool init();
		void stop();
		void fina();
	};
}

#endif