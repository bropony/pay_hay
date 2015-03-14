#ifndef _GAME_CONFIG_DATA_GAME_DATA_LOADER_H_
#define _GAME_CONFIG_DATA_GAME_DATA_LOADER_H_
/*
* ������Ϸ�����ļ�
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
		* ������Ϸ��̬��������
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