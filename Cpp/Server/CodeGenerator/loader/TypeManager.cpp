#include "TypeManager.h"
#include "framework/log/loggerutil.h"

using namespace cg;

std::map<int, std::string> CIdent::_mapIdent;


std::string CType::Byte = "byte";
std::string CType::Bool = "bool";
std::string CType::Short = "short";
std::string CType::Int = "int";
std::string CType::Long = "long";
std::string CType::Float = "float";
std::string CType::Double = "double";
std::string CType::String = "string";
std::string CType::Date = "date";
std::string CType::Image = "image";

int CType::_typeIdBase = 0;

void CType::setListBase(const CTypePtr & b)
{
	_listBase = b;
	_javaArrayType = b->getJavaType() + "[]";
	if (b->getType() != EType::LIST)
	{
		if (b->getName() == "image")
		{
			_javaNewArrayType = "byte[size][]";
			_javaNewZeroArrayType = "byte[0][]";
		}
		else
		{
			_javaNewArrayType = b->getJavaType() + "[size]";
			_javaNewZeroArrayType = b->getJavaType() + "[0]";
		}
	}
	else
	{
		_javaNewArrayType = b->getNewJavaArray() + "[]";
		_javaNewZeroArrayType = b->getNewZeroJavaArray() + "[]";
	}
}

const std::string CType::getCppType()
{
	switch (_type)
	{
	case EType::BASIC:
		{
			if (_name == Bool ||
				_name == Int ||
				_name == Float ||
				_name == Double)
			{
				return _name;
			}

			if (_name == Byte)
			{
				return "byte_t";
			}

			if (_name == Long)
			{
				return "long64_t";
			}

			if (_name == String ||
				_name == Image)
			{
				return "std::string";
			}

			if (_name == Date)
			{
				return "cdf::CDateTime";
			}
		}
		break;
	default:
		{
			return _name;
		}
		break;
	}

	return _name;
}

const std::string CType::getJavaType()
{
	switch (_type)
	{
	case cg::EType::BASIC:
		if (_name == Byte ||
			_name == Int ||
			_name == Long ||
			_name == Float ||
			_name == Double)
		{
			return _name;
		}
		if (_name == Bool)
		{
			return "boolean";
		}
		if (_name == String)
		{
			return "String";
		}
		if (_name == Date)
		{
			return "Date";
		}
		if (_name == Image)
		{
			return "byte[]";
		}
		break;
	case cg::EType::STRUCT:
		return _name;
		break;
	case cg::EType::LIST:
		return _javaArrayType;
		break;
	case cg::EType::ENUM:
		return _name;
		break;
	default:
		return _name;
		break;
	}

	return _name;
}

const std::string & CType::getNewJavaArray()
{
	return _javaNewArrayType;
}

const std::string & CType::getNewZeroJavaArray()
{
	return _javaNewZeroArrayType;
}

bool CType::isCompositeType()
{
	if (_name == Bool ||
		_name == Byte ||
		_name == Short ||
		_name == Int ||
		_name == Float ||
		_name == Long ||
		_name == Double)
	{
		return false;
	}

	return true;
}

CTypeManager * CTypeManager::_inst = nullptr;
CTypeManager * CTypeManager::instance()
{
	if (nullptr == _inst)
	{
		_inst = new CTypeManager();
	}

	return _inst;
}

void CTypeManager::addType(EType type, const std::string & name)
{
	CTypePtr typePtr = new CType(type, name);
	addType(typePtr);
}

void CTypeManager::addType(const CTypePtr & type)
{
	if (hasType(type->getName()))
	{
		CDF_LOG_TRACE("CTypeManager::addType", "DuplicatedType: " << type->getName());
		assert(false);
		return;
	}

	_mapIntType[type->getTypeId()] = type;
	_mapStrType[type->getName()] = type;
}

bool CTypeManager::hasType(const std::string & name)
{
	bool res = (_mapStrType.find(name) != _mapStrType.end());

	return res;
}

CTypeManager::CTypeManager()
{
	addType(EType::BASIC, CType::Byte);
	addType(EType::BASIC, CType::Bool);
	addType(EType::BASIC, CType::Short);
	addType(EType::BASIC, CType::Int);
	addType(EType::BASIC, CType::Long);
	addType(EType::BASIC, CType::Float);
	addType(EType::BASIC, CType::Double);
	addType(EType::BASIC, CType::String);
	addType(EType::BASIC, CType::Date);
	addType(EType::BASIC, CType::Image);
}

CTypeManager::~CTypeManager()
{
	if (nullptr != _inst)
	{
		delete _inst;
	}

	_inst = nullptr;
}

const CTypePtr CTypeManager::getType(int typeId)
{
	auto found = _mapIntType.find(typeId);
	if (found != _mapIntType.end())
	{
		return found->second;
	}

	return NULL;
}

const CTypePtr CTypeManager::getType(const std::string & name)
{
	auto found = _mapStrType.find(name);
	if (found != _mapStrType.end())
	{
		return found->second;
	}

	return NULL;
}


