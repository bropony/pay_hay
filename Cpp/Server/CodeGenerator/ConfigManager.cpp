#include "ConfigManager.h"
#include "framework/util/stringfun.h"
#include "framework/log/loggerutil.h"

#include "Message/Db/Tables/Loader/TEventConfigLoader.h"

#include <locale>

using namespace cg;

const std::string CTypes::getIdent(int n)
{
	std::string res;
	for (int i = 0; i < n; i++)
	{
		res += "    ";
	}

	return res;
}


std::set<std::string> CTypes::typeSet = {
	"int", /*"long",*/ "string", "json", "double", "bool", "date" };


bool CEvent::init(int eventId, const std::string & name, const std::string & inParams, const std::string & outParams)
{
	_eventId = eventId;
	_eventName = name;
	if (!parseParam(inParams, _inParams))
	{
		return false;
	}

	if (!parseParam(outParams, _outParams))
	{
		return false;
	}

	std::locale loc;
	std::string tmpName = _eventName;
	tmpName[0] = std::toupper(tmpName[0], loc);
	_cbName = "C" + tmpName + "_callback";

	_funcSig = _eventName + "(";
	auto isFirst = true;
	for (auto pair : _inParams)
	{
		if (!isFirst)
		{
			_funcSig += ", ";
		}

		_funcSig += pair.getTypeName() + " " + pair.name;
		isFirst = false;
	}
	if (!isFirst)
	{
		_funcSig += ", ";
	}
	_funcSig += "const ::cg::" + _cbName + "Ptr & callback";

	_funcSig += ")";

	_cbSig = "response(";
	isFirst = true;
	for (auto pair : _outParams)
	{
		if (!isFirst)
		{
			_cbSig += ", ";
		}
		isFirst = false;

		_cbSig += pair.getTypeName() + " " + pair.name;
	}
	_cbSig += ")";

	return true;
}

bool CEvent::parseParam(const std::string & fmtParam, SeqParam & params)
{
	std::vector<std::string> seqParamPair;
	cdf::CStrFun::split(seqParamPair, fmtParam.c_str(), '#');

	std::set<std::string> usedName;
	for (auto pair : seqParamPair)
	{
		std::vector<std::string> tags;
		cdf::CStrFun::split(tags, pair.c_str(), ':');
		if (tags.size() != 2)
		{
			CDF_LOG_TRACE("CEvent::parseParam", "paramError: " << fmtParam);
			return false;
		}

		std::string name = tags[0];
		std::string type = tags[1];

		if (usedName.find(name) != usedName.end())
		{
			CDF_LOG_TRACE("CEvent::parseParam", "duplicated param name: " << name);
			return false;
		}

		if (!CTypes::checkType(type))
		{
			CDF_LOG_TRACE("CEvent::parseParam", "invalid param type: " << type);
			return false;
		}

		usedName.insert(name);

		params.push_back(CParam(name, type));
	}

	return true;
}

void CEvent::gencallback(std::ofstream & hpp, std::ofstream & cpp)
{
	std::string ident1 = CTypes::getIdent(1);
	std::string ident2 = CTypes::getIdent(2);

	std::string ctor = _cbName + "(int msgId, const std::string & event, const cdf::CWSContextPtr & context)";

	hpp << ident1 << "class " << _cbName << "\n";
	hpp << ident2 << ": public virtual cdf::CRefShared\n";
	hpp << ident1 << "{\n";
	hpp << ident1 << "public:\n";
	hpp << ident2 << ctor << ";\n";
	hpp << ident2 << "void " << _cbSig << ";\n";
	hpp << ident2 << "void responseB(const std::string & data);\n";
	hpp << ident2 << "const cdf::CWSContextPtr getContext(){ return _context; }\n";
	hpp << "\n";
	hpp << ident1 << "private:\n";
	hpp << ident2 << "int _msgId;\n";
	hpp << ident2 << "std::string _event;\n";
	hpp << ident2 << "cdf::CWSContextPtr _context;\n";
	hpp << ident1 << "};\n";
	hpp << ident1 << "typedef cdf::CHandle<" << _cbName << "> " << _cbName << "Ptr;\n\n";

	cpp << _cbName << "::" << ctor << "\n";
	cpp << ident1 << ":_msgId(msgId), _event(event), _context(context)\n";
	cpp << "{\n}\n\n";

	cpp << "void " << _cbName << "::" << _cbSig << "\n{\n";
	cpp << ident1 << "Json::Value __res;\n";
	cpp << ident1 << "__res[\"msg_id\"] = _msgId;\n";
	cpp << ident1 << "__res[\"event\"] = \"" << _eventName << "\";\n";
	for (auto pair : _outParams)
	{
		if (pair.type == "date")
		{
			cpp << ident1 << "__res[\"" << pair.name << "\"] = " << pair.name << ".getTotalSecond();\n";
		}
		else
		{
			cpp << ident1 << "__res[\"" << pair.name << "\"] = " << pair.name << ";\n";
		}
	}
	cpp << "\n";
	cpp << ident1 << "cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());\n";
	cpp << "}\n\n";

	cpp << "void " << _cbName << "::responseB(const std::string & data)\n";
	cpp << "{\n";
	cpp << ident1 << "std::string __res;\n";
	cpp << ident1 << "__res.resize(4);\n";
	cpp << ident1 << "int msgId = cdf::endian(_msgId);\n";
	cpp << ident1 << "for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}\n";
	cpp << ident1 << "__res += data;\n";
	cpp << ident1 << "cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);\n";
	cpp << "}\n";

	cpp << "\n\n";
}


CEventManager * CEventManager::instance()
{
	static CEventManager _inst;

	return &_inst;
}

bool CEventManager::loadConfig()
{
	Message::Db::Tables::SeqTEventConfig configs;
	Message::Db::Tables::Loader::loadFile(configFile, configs);

	std::set<std::string> usedName;
	for (auto config : configs)
	{
		if (usedName.find(config.event) != usedName.end())
		{
			CDF_LOG_TRACE("CEventManager::loadConfig", "duplicated event: " << config.event);
			return false;
		}
		CEvent evt;
		if (!evt.init(config.eventId, config.event, config.inParams, config.outParams))
		{
			return false;
		}

		_events.push_back(evt);
	}

	return true;
}
