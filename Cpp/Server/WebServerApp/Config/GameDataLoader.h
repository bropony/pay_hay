#ifndef _GAME_CONFIG_DATA_GAME_DATA_LOADER_H_
#define _GAME_CONFIG_DATA_GAME_DATA_LOADER_H_
/*
* 加载游戏配置文件
* mahanzhou
*/

#include "framework/util/refshared.h"

namespace WebServerApp
{
	class CGameDataLoader
		: public virtual cdf::CRefShared
	{
	public:

		static CGameDataLoader * instance();

		/*
		* 加载游戏静态配置数据
		*/
		bool loadGameData();


	private:
		CGameDataLoader()
		{

		}

		~CGameDataLoader()
		{

		}
	};
}

#endif