#ifndef __STRUCT_CONFIG_MANAGER_H__
#define __STRUCT_CONFIG_MANAGER_H__

#include "loader/TypeManager.h"
#include <vector>
#include <set>
#include <fstream>

namespace cg
{
	class CField
		: public cdf::CRefShared
	{
	public:
		CField(const CTypePtr & type, const std::string & name)
			:_type(type), _name(name){}

		const CTypePtr & getType(){ return _type; }
		const std::string & getName(){ return _name; }

	private:
		CTypePtr _type;
		std::string _name;
	};
	typedef cdf::CHandle<CField> CFieldPtr;
	typedef std::vector<CFieldPtr> SeqField;
	typedef std::vector<std::vector<std::string> > FieldConfig;

	class CStructBase
		: public virtual cdf::CRefShared
	{
	public:
		CStructBase(){}
		~CStructBase(){}

		virtual const std::string & getName() = 0;
		virtual EType getDataType() = 0;
		virtual void toCpp(std::ostream & Hpp, std::ostream & Cpp) = 0;
		virtual void toJava(std::ostream & Java) = 0;
		virtual void toTs(std::ostream & Ts) = 0;
	};
	typedef cdf::CHandle<CStructBase> CStructBasePtr;
	typedef std::vector<CStructBasePtr> SeqStructBase;

	class CStruct
		: public virtual CStructBase
	{
	public:
		CStruct(const std::string & name);
		void addField(const CTypePtr & type, const std::string & name);
		bool hasField(const std::string & name);

		virtual const std::string & getName(){ return _name; }
		virtual EType getDataType(){ return EType::STRUCT; }
		virtual void toCpp(std::ostream & Hpp, std::ostream & Cpp);
		virtual void toJava(std::ostream & Java);
		virtual void toTs(std::ostream & Ts);

	private:
		std::string _name;
		SeqField _fields;
		std::set<std::string> _fieldNameSet;
	};
	typedef cdf::CHandle<CStruct> CStructPtr;

	class CList
		: public virtual CStructBase
	{
	public:
		CList(const std::string & name, const CTypePtr & elemType)
			:CStructBase(), _name(name), _elemType(elemType){}
		//const std::string & getName(){ return _name; }
		const CTypePtr & getElemType(){ return _elemType; }

		virtual const std::string & getName(){ return _name; }
		virtual EType getDataType(){ return EType::LIST; }
		virtual void toCpp(std::ostream & Hpp, std::ostream & Cpp);
		virtual void toJava(std::ostream & Java);
		virtual void toTs(std::ostream & Ts);

	private:
		std::string _name;
		CTypePtr _elemType;
	};
	typedef cdf::CHandle<CList> CListPtr;

	class CEnum
		: public virtual CStructBase
	{
	public:
		CEnum(const std::string & name);
		//const std::string & getName();
		bool hasElem(const std::string & elemName);
		bool isElemValueOk(int val);
		void addElem(const std::string & elemName, int val);
		int getMaxValue();

		virtual const std::string & getName(){ return _name; }
		virtual EType getDataType(){ return EType::ENUM; }
		virtual void toCpp(std::ostream & Hpp, std::ostream & Cpp);
		virtual void toJava(std::ostream & Java);
		virtual void toTs(std::ostream & Ts);

	private:
		std::string _name;
		std::vector<std::pair<std::string, int> > _elems;
		std::set<std::string> _elemNameSet;
	};
	typedef cdf::CHandle<CEnum> CEnumPtr;

	class CStructManager
	{
	public:
		static CStructManager * instance();
		bool loadConfig(const std::string & configFilePath);
		void toCpp(const std::string & outCppPath);
		void toJava(const std::string & outJavaDir);
		void toTs(const std::string & outTsDir);

	public:
		static bool parseFields(const std::string & strFields, FieldConfig & fields);
		bool addNewJavaArrayType(const std::string & javaArrayType);
	private:
		CStructManager();
		~CStructManager();

		bool parseStruct(const std::string & name, const FieldConfig & fileds);
		bool parseList(const std::string & name, const std::string & baseTypeName);
		bool parseEnum(const std::string & name, const FieldConfig & fileds);

		static void genJavaHeaders(std::ostream & Java);
	private:
		SeqStructBase _structs;
		std::set<std::string> _javaListSet;
	};
}

#endif