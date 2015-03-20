#ifndef __RMI_EVENT_CONFIG_MANAGER_H__
#define __RMI_EVENT_CONFIG_MANAGER_H__

#include "framework/util/refshared.h"
#include "loader/StructConfigManager.h"
#include <fstream>

namespace cg
{
	class CMethod
		: public virtual cdf::CRefShared
	{
	public:
		CMethod(int eventId, const std::string & name);
		~CMethod();
		int getEventId(){ return _eventId; }
		const std::string & getName(){ return _name; }
		bool parseParams(const FieldConfig & inFields, const FieldConfig & outFiels);

		void callbacksToCpp(std::ofstream & Hpp, std::ofstream & Cpp);
		void methodsToCpp(std::ofstream & Hpp, std::ofstream & Cpp);

		void callbacksToJava(std::ofstream & Java);
		void methodsToJava(std::ofstream & Java);

		void callbacksToTs(std::ofstream & Ts);
		void methodsToTs(std::ofstream & Ts);
	private:
		bool parseFields(const FieldConfig & fields, SeqField & params, std::set<std::string> & usedNameSet, bool isIn);
	private:
		int _eventId;
		std::string _name;
		std::string _inSignature;
		std::string _outSignature;
		std::string _cbName;
		std::string _javaCbName;
		std::string _tsCbName;
		SeqField _inParams;
		SeqField _outParams;
	};
	typedef cdf::CHandle<CMethod> CMethodPtr;
	typedef std::vector<CMethodPtr> SeqMethod;

	class CEventConfigManager
	{
	public:
		static CEventConfigManager * instance();
		bool loadConfig(const std::string & configFile);
		void toCpp(const std::string & cppBase);
		void toJava(const std::string & javaBase);
		void toTs(const std::string & tsBase);

	private:
		void __callToCpp(std::ofstream & Cpp);
		CEventConfigManager(){}
		~CEventConfigManager(){}

	private:
		SeqMethod _methods;
		std::set<std::string> _methodNameSet;
	};
}

#endif