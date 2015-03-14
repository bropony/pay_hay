#ifndef __TYPE_MANAGER_H__
#define __TYPE_MANAGER_H__

#include "framework/util/refshared.h"
#include <string>
#include <map>

#define ENDL std::endl
#define Ident0 cg::CIdent::getIdent(0)
#define Ident1 cg::CIdent::getIdent(1)
#define Ident2 cg::CIdent::getIdent(2)
#define Ident3 cg::CIdent::getIdent(3)
#define Ident4 cg::CIdent::getIdent(4)
#define Ident5 cg::CIdent::getIdent(5)
#define Ident6 cg::CIdent::getIdent(6)

namespace cg
{
	enum EType
	{
		BASIC = 0,
		STRUCT = 1,
		LIST = 2,
		ENUM = 3,
	};

	class CIdent
	{
	public:
		static const std::string & getIdent(int i)
		{
			if (_mapIdent.find(i) == _mapIdent.end())
			{
				std::string ident = "";
				for (int x = 0; x < i; x++)
				{
					ident += '\t';
				}
				_mapIdent[i] = ident;
			}

			return _mapIdent[i];
		}
	private:
		static std::map<int, std::string> _mapIdent;
	};

	class CType;
	typedef cdf::CHandle<CType> CTypePtr;
	class CType:
		public virtual cdf::CRefShared
	{
	public:
		CType(EType type, const std::string & name) :
			_type(type), _name(name), _typeId(++_typeIdBase){}

		int getTypeId(){ return _typeId; }
		EType getType(){ return _type; }
		const std::string & getName(){ return _name; }
		void setListBase(const CTypePtr & b);
		const CTypePtr & getListBase(){ return _listBase; }
		const std::string getCppType();
		const std::string getJavaType();
		const std::string & getNewJavaArray();
		const std::string & getNewZeroJavaArray();
		bool isBasicType(){ return (_type == EType::BASIC); }
		bool isCompositeType();

	public:
		static std::string Byte;
		static std::string Bool;
		static std::string Short;
		static std::string Int;
		static std::string Long;
		static std::string Float;
		static std::string Double;
		static std::string String;
		static std::string Date;
		static std::string Image;

	private:
		EType _type;
		int _typeId;
		std::string _name;
		CTypePtr _listBase;
		std::string _javaArrayType;
		std::string _javaNewArrayType;
		std::string _javaNewZeroArrayType;

	private:
		static int _typeIdBase;
	};
	typedef std::map<int, CTypePtr> MapIntType;
	typedef std::map<std::string, CTypePtr> MapStrType;

	class CTypeManager
	{
	public:
		static CTypeManager * instance();
		void addType(EType type, const std::string & name);
		void addType(const CTypePtr & type);
		bool hasType(const std::string & name);

		const CTypePtr getType(int typeId);
		const CTypePtr getType(const std::string & name);

	private:
		CTypeManager();
		~CTypeManager();

	private:
		static CTypeManager * _inst;
		MapIntType _mapIntType;
		MapStrType _mapStrType;
	};
}

#endif