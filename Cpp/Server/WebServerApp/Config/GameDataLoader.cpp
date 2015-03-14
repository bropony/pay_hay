#include "GameDataLoader.h"
#include "framework/resource/resourcebundle.h"
#include "framework/log/loggerutil.h"

#include "ErrorCodeManager.h"


#define LoadConfig(manager) { \
	cdf::CDateTime startDt; \
	CDF_LOG_TRACE("CGameDataLoader::loadGameData", "loading " #manager "..."); \
	if (!(manager::instance()->loadConfig())) \
	{ \
        CDF_LOG_TRACE("CGameDataLoader::loadGameData", "loading " #manager " failed"); \
        assert(false); \
        return false; \
    } \
	CDF_LOG_TRACE("CGameDataLoader::loadGameData", "loading " #manager " cost time:" << (cdf::CDateTime() - startDt).asString()); \
}

using namespace WebServerApp;

CGameDataLoader * CGameDataLoader::instance()
{
	static CGameDataLoader _inst;

	return &_inst;
}

bool CGameDataLoader::loadGameData()
{
	CDF_LOG_TRACE( "CGameDataLoader::loadGameData", "Loading Game Data Starts" );
	cdf::CDateTime globalStartDt;

	// ¼ÓÔØ´íÎóÂë
	LoadConfig(CErrorCodeManager);


	CDF_LOG_TRACE("GameDataLoader::loadGameData", "Loading Game Data SUCCESS! TimeUsed: " 
		<< (cdf::CDateTime()-globalStartDt).getTotalMills() << "(ms)");

	return true;
}
