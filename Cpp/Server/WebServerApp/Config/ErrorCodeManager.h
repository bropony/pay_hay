#ifndef _COMMON_ERROR_ERROR_CODE_MANAGER_H_
#define _COMMON_ERROR_ERROR_CODE_MANAGER_H_

#include "framework/stlex/hashmap.h"
#include "Message/Db/Tables/TErrorCode.h"

namespace WebServerApp
{
	/*
	* 职业配置文件
	*/
	const std::string errorCodeConfigFile = "../config/data/t_error_code.json";


	class CErrorCode
		: public virtual cdf::CRefShared
	{
	public:
		Message::Db::Tables::TErrorCode _tErrorCode;
	};
	typedef cdf::CHandle<CErrorCode> CErrorCodePtr;
	typedef cde_hash_map<std::string, CErrorCodePtr> MapErrorCodePtr;

	class CErrorCodeManager
	{
	public:
		static CErrorCodeManager* instance();

		/*
		* 抛异常
		*/
		static void throwException(const std::string& errorName, const std::string& msg = "");

		/*
		* 抛异常
		*/
		static void throwException(const std::string& errorName, const std::vector<std::string>& msgs);

		/*
		* 加载配置
		* @return bool
		*/
		virtual bool loadConfig();

		virtual bool reloadConfig();

		/*
		* 获取错误码
		* @param errorName
		* @return CBornPointPtr
		*/
		CErrorCodePtr getErrorCode(const std::string& errorName);

	private:
		CErrorCodeManager()
			:_map()
		{
		}

		~CErrorCodeManager()
		{
		}

		virtual bool clearConfig()
		{
			_map.clear();
			return true;
		}

		MapErrorCodePtr _map;
	};
}

#endif