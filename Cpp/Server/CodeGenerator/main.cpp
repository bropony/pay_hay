//#include "Generator.h"
#include "loader/StructConfigManager.h"
#include "loader/EventConfigManager.h"
#include <iostream>
#include <cstdio>

using namespace cg;

int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		std::cout << argv[0] << " <javaOutDir>" << std::endl;
		return 0;
	}

	std::string structConfigFile = "../config/data/t_struct_config.json";
	std::string eventConfigFile = "../config/data/t_event_config.json";
	std::string cppBase = "../../Server/WebServerApp/Rmi";
	std::string javaBase = argv[1];
	std::string tsBase = "";
	if (argc > 2)
	{
		tsBase = argv[2];
	}

	std::cout << "Loading struct config" << std::endl;
	if (!CStructManager::instance()->loadConfig(structConfigFile))
	{
		return -1;
	}

	std::cout << "generating struct codes" << std::endl;
	CStructManager::instance()->toCpp(cppBase);
	CStructManager::instance()->toJava(javaBase);
	CStructManager::instance()->toTs(tsBase);

	std::cout << "loading event configs..." << std::endl;
	if (!CEventConfigManager::instance()->loadConfig(eventConfigFile))
	{
		return -1;
	}

	std::cout << "generating event codes..." << std::endl;
	CEventConfigManager::instance()->toCpp(cppBase);
	CEventConfigManager::instance()->toJava(javaBase);
	CEventConfigManager::instance()->toTs(tsBase);

	std::cout << "Job done...\n" << std::endl;

	std::cout << "Press ENTER to exit..." << std::endl;
	std::getchar();

	return 0;
}
