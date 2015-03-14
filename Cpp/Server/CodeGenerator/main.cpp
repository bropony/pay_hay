//#include "Generator.h"
#include "loader/StructConfigManager.h"
#include "loader/EventConfigManager.h"

using namespace cg;

int main(int argc, char ** argv)
{
	std::string structConfigFile = "../config/data/t_struct_config.json";
	std::string eventConfigFile = "../config/data/t_event_config.json";
	std::string cppBase = "../../Server/WebServerApp/Rmi";
	std::string javaBase = "F:/Programs/java/Serialize/src/rmi/client";

	if (!CStructManager::instance()->loadConfig(structConfigFile))
	{
		return -1;
	}

	CStructManager::instance()->toCpp(cppBase);
	CStructManager::instance()->toJava(javaBase);

	if (!CEventConfigManager::instance()->loadConfig(eventConfigFile))
	{
		return -1;
	}

	CEventConfigManager::instance()->toCpp(cppBase);
	CEventConfigManager::instance()->toJava(javaBase);

	return 0;
}