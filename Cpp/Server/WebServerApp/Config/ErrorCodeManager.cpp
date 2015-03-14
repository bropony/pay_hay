#include "ErrorCodeManager.h"
#include "Message/Db/Tables/Loader/TErrorCodeLoader.h"
#include "framework/resource/resourceformater.h"
#include "framework/log/loggerutil.h"
#include <fstream>

using namespace WebServerApp;

CErrorCodeManager* CErrorCodeManager::instance()
{
	static CErrorCodeManager* inst = new CErrorCodeManager();
	return inst;
}

void CErrorCodeManager::throwException(const std::string& errorName, const std::string& msg /*= "" */)
{
	CErrorCodePtr errorCode = 
		CErrorCodeManager::instance()->getErrorCode(errorName);
	assert(errorCode);

	CDF_LOG_DEBUG("CErrorCodeManager::throwException" <<
		" error code:" << errorCode->_tErrorCode.errorCode << " name:"<< errorName << " msg:" << msg);

	throw cdf::CException(errorCode->_tErrorCode.errorStr.c_str(), errorCode->_tErrorCode.errorCode);
}

void 
CErrorCodeManager::throwException(const std::string& errorName, const std::vector<std::string>& msgs)
{
	CErrorCodePtr errorCode = 
		CErrorCodeManager::instance()->getErrorCode(errorName);

	cdf::CResourceFormater formater;
	formater.loadFormat(errorCode->_tErrorCode.errorStr);
	std::string errorMsg = formater.formatText(msgs);

	CDF_LOG_DEBUG("CErrorCodeManager::throwException" <<
		" error code:" << errorCode->_tErrorCode.errorCode << " msg:" << errorMsg);

	throw cdf::CException(errorMsg.c_str(), errorCode->_tErrorCode.errorCode);
}

bool CErrorCodeManager::loadConfig()
{
	_map.clear();

	Message::Db::Tables::SeqTErrorCode datas;
	Message::Db::Tables::Loader::loadFile(errorCodeConfigFile, datas);
	if (datas.empty())
	{
		CDF_LOG_TRACE("CErrorCodeManager", "datas is empty");
		assert(false);
		return false;
	}

	for (Message::Db::Tables::SeqTErrorCode::const_iterator it = datas.begin(); it != datas.end(); ++it)
	{
		CErrorCodePtr errorCode = new CErrorCode();
		errorCode->_tErrorCode = *it;
		
		MapErrorCodePtr::const_iterator itMap = _map.find(errorCode->_tErrorCode.errorName);
		if (itMap != _map.end())
		{
			CDF_LOG_TRACE("CErrorCodeManager", "[errorCode has exist] errorName:" << errorCode->_tErrorCode.errorName);
			assert(false);
			return false;
		}

		_map[errorCode->_tErrorCode.errorName] = errorCode;	
	}

	std::string unkownError = "ExceptionCodeUnkown";
	MapErrorCodePtr::iterator it = _map.find(unkownError);
	if (it == _map.end())
	{
		assert(false);
		return false;
	}

	return true;
}

bool CErrorCodeManager::reloadConfig()
{
	CDF_LOG_TRACE("CErrorCodeManager::reloadConfig", "reloading");

	//backup
	MapErrorCodePtr tmp;
	tmp.swap(_map);

	//clear
	clearConfig();

	//load
	bool res = loadConfig();

	//check
	if (!res)
	{
		_map.swap(tmp);
	}

	return res;
}

CErrorCodePtr CErrorCodeManager::getErrorCode( const std::string& errorName )
{
	MapErrorCodePtr::const_iterator it = _map.find(errorName);
	if (it != _map.end())
	{
		return it->second;
	}

	{
		std::ofstream ofs("unkown_error.txt", std::ofstream::app);
		ofs << cdf::CDateTime().asString() << "->" << errorName << std::endl;
		ofs.close();
	}

	it = _map.find("ExceptionCodeUnkown");
	assert(it != _map.end());

	if (it == _map.end())
	{
		return NULL;
	}

	return it->second;
}