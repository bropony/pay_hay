#ifndef __CONFIG_MANAGER_H__
#define __CONFIG_MANAGER_H__

#include <string>
#include <vector>
#include <set>
#include <fstream>

namespace cg
{
	class CTypes
	{
	public:
		static bool checkType(const std::string & type)
		{
			return (typeSet.find(type) != typeSet.end());
		}

		static const std::string getIdent(int n);

	public:
		static std::set<std::string> typeSet;
	};

	class CParam
	{
	public:
		CParam(const std::string & n , const std::string & t)
		:name(n), type(t){};
		std::string name;
		std::string type;

		bool checkType()
		{
			return CTypes::checkType(type);
		}

		const std::string getTypeName()
		{
			if (type == "string")
			{
				return "const std::string &";
			}
			else if (type == "date")
			{
				return "const cdf::CDateTime &";
			}
			else if (type == "json")
			{
				return "const Json::Value &";
			}

			return type;
		}

		const std::string getJsonType()
		{
			if (type == "string"){ return "string"; }
			if (type == "int"){ return "number"; }
			if (type == "double"){ return "number"; }
			if (type == "json"){ return "object"; }
			if (type == "bool"){ return "boolean"; }
			if (type == "date"){ return "object"; }
		}
	};
	typedef std::vector<CParam> SeqParam;

	class CEvent
	{
	public:
		CEvent(){};
		~CEvent(){};

		bool init(int eventId, const std::string & name, const std::string & inParams, const std::string & outParams);
		void gencallback(std::ofstream & hpp, std::ofstream & cpp);
		const std::string & getName(){ return _eventName; }
		const std::string & getCall(){ return _funcCall; }
		const std::string & getCbName(){ return _cbName; }
		const SeqParam & getOutParams(){ return _outParams; }
		const SeqParam & getInParams(){ return _inParams; }
		const std::string & getFuncSig(){ return _funcSig; }

	private:
		static bool parseParam(const std::string & fmtParam, SeqParam & params);
	private:
		int _eventId;
		std::string _eventName;
		SeqParam _inParams;
		SeqParam _outParams;

		std::string _funcSig;
		std::string _funcCall;
		std::string _cbName;
		std::string _cbSig;
	};
	typedef std::vector<CEvent> SeqEvent;

	const std::string configFile = "../config/data/t_event_config.json";

	class CEventManager
	{
	public:
		static CEventManager * instance();
		bool loadConfig();
		const SeqEvent & getEvents(){ return _events; }

	private:
		SeqEvent _events;
	};
}

#endif
