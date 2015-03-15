#include "StructConfigManager.h"
#include "Message/Db/Tables/Loader/TStructConfigLoader.h"
#include "framework/util/stringfun.h"
#include "framework/log/loggerutil.h"

using namespace cg;

//CStruct
CStruct::CStruct(const std::string & name)
:CStructBase()
,_name(name)
{
}

void CStruct::addField(const CTypePtr & type, const std::string & name)
{
	if (!hasField(name))
	{
		_fields.push_back(new CField(type, name));
		_fieldNameSet.insert(name);
	}
}

bool CStruct::hasField(const std::string & name)
{
	if (name == _name)
	{
		return true;
	}

	bool res = (_fieldNameSet.find(name) != _fieldNameSet.end());

	return res;
}

void CStruct::toCpp(std::ostream & Hpp, std::ostream & Cpp)
{
	Hpp << Ident1 << "struct " << _name << ENDL;
	//Hpp << Ident2 << ": public virtual cdf::CRefShared" << ENDL;
	Hpp << Ident1 << "{" << ENDL; //start of class
	//Hpp << Ident1 << "public:" << ENDL;
	//fields declaration
	for (auto field : _fields)
	{
		Hpp << Ident2 << field->getType()->getCppType() << " " << field->getName() << ";" << ENDL;
	}

	Hpp << ENDL;
	Hpp << Ident2 << _name << "();" << ENDL;
	Hpp << Ident2 << "~" << _name << "();" << ENDL;
	Hpp << ENDL;

	//serialize funcs
	Hpp << Ident2 << "void __read(cdf::CSimpleSerializer & __is);" << ENDL;
	Hpp << Ident2 << "void __write(cdf::CSimpleSerializer & __os) const;" << ENDL;

	Hpp << Ident1 << "}; //end of class " << _name << ENDL; //end of class
	//Hpp << Ident1 << "typedef cdf::CHandle<" << _name << "> " << _name << "Ptr;" << ENDL;
	Hpp << ENDL;

	std::string scope = _name + "::";
	Cpp << "//definition of class " << _name << ENDL;

	//constructor
	Cpp << scope << _name << "()" << ENDL;
	bool isFirst = true;
	for (auto field : _fields)
	{
		if (isFirst)
		{
			Cpp << ":";
			isFirst = false;
		}
		else
		{
			Cpp << ",";
		}
		Cpp << field->getName() << "()" << ENDL;
	}
	Cpp << "{\n}" << ENDL;
	Cpp << ENDL;

	//destructor
	Cpp << scope << "~" << _name << "()" << ENDL;
	Cpp << "{\n}" << ENDL;
	Cpp << ENDL;

	//__read
	Cpp << "void " << scope << "__read(cdf::CSimpleSerializer & __is)" << ENDL;
	Cpp << "{" << ENDL;
	for (auto field : _fields)
	{
		EType fieldDataType = field->getType()->getType();

		Cpp << Ident1;
		switch (fieldDataType)
		{
		case EType::BASIC:
			Cpp << "__is.read(" << field->getName() << ");" << ENDL;
			break;
		case EType::LIST:
			if (field->getType()->getListBase()->isBasicType())
			{
				Cpp << "__is.read(" << field->getName() << "); " << ENDL;
			}
			else
			{
				Cpp << "::Rmi::__read(__is, " << field->getName() << ", " << field->getType()->getName() << "__U__());" << ENDL;
			}
			break;
		default:
			Cpp << field->getName() << ".__read(__is);" << ENDL;
			break;
		}
	}
	Cpp << "}\n" << ENDL;

	//__write
	Cpp << "void " << scope << "__write(cdf::CSimpleSerializer & __os) const" << ENDL;
	Cpp << "{" << ENDL;
	for (auto field : _fields)
	{
		EType fieldDataType = field->getType()->getType();

		Cpp << Ident1;
		switch (fieldDataType)
		{
		case EType::BASIC:
			Cpp << "__os.write(" << field->getName() << ");" << ENDL;
			break;
		case EType::LIST:
			if (field->getType()->getListBase()->isBasicType())
			{
				Cpp << "__os.write(" << field->getName() << "); " << ENDL;
			}
			else
			{
				Cpp << "::Rmi::__write(__os, " << field->getName() << ", " << field->getType()->getName() << "__U__());" << ENDL;
			}
			break;
		default:
			Cpp << field->getName() << ".__write(__os);" << ENDL;
			break;
		}
	}
	Cpp << "}\n" << ENDL;
}

void CStruct::toJava(std::ostream & Java)
{
	Java << "public class " << _name << "{" << ENDL; //begin of class

	//fields
	for (auto field : _fields)
	{
		Java << Ident1 << "public " << field->getType()->getJavaType() << " " << field->getName() << ";" << ENDL;
	}
	Java << ENDL;

	//constructor
	Java << Ident1 << "public " << _name << "(){" << ENDL;
	for (auto field : _fields)
	{
		CTypePtr fieldTypePtr = field->getType();
		EType fieldDataType = fieldTypePtr->getType();
		const std::string & fieldName = field->getName();
		Java << Ident2;

		if (fieldDataType == EType::BASIC)
		{
			if (fieldTypePtr->getName() == "bool")
			{
				Java << fieldName << " = false;" << ENDL;
			}
			else if (fieldTypePtr->getName() == "string")
			{
				Java << fieldName << " = \"\";" << ENDL;
			}
			else if (fieldTypePtr->getName() == "date")
			{
				Java << fieldName << " = new Date();" << ENDL;
			}
			else if (fieldTypePtr->getName() == "image")
			{
				Java << fieldName << " = new byte[0];" << ENDL;
			}
			else
			{
				Java << fieldName << " = 0;" << ENDL;
			}
		}
		else if (fieldDataType == EType::LIST)
		{
			Java << fieldName << " = new " << fieldTypePtr->getNewZeroJavaArray() << ";" << ENDL;
		}
		else
		{
			Java << fieldName << " = new " << fieldTypePtr->getJavaType() << "();" << ENDL;
		}
	}
    Java << Ident1 << "}" << ENDL;

	//read
	Java << Ident1 << "public void read(SerializeStream __is){" << ENDL; //start of read
	for (auto field : _fields)
	{
		EType fieldType = field->getType()->getType();
		if (fieldType == EType::BASIC)
		{
			Java << Ident2 << field->getName() << " = __is.read(" << field->getName() << ");" << ENDL;
		}
		else if (fieldType == EType::LIST)
		{
			if (field->getType()->getListBase()->isBasicType())
			{
				Java << Ident2 << field->getName() << " = __is.read(" << field->getName() << ");" << ENDL;
			}
			else
			{
				Java << Ident2 << field->getName() << " = ListReader.read(__is, " << field->getName() << ");" << ENDL;
			}
		}
		else
		{
			Java << Ident2 << field->getName() << ".read(__is);" << ENDL;
		}
	}
	Java << Ident1 << "}" << ENDL; //end of read

	//write
	Java << Ident1 << "public void write(SerializeStream __os){" << ENDL;
	for (auto field : _fields)
	{
		EType fieldType = field->getType()->getType();
		if (fieldType == EType::BASIC)
		{
			Java << Ident2 << "__os.write(" << field->getName() << ");" << ENDL;
		}
		else if (fieldType == EType::LIST)
		{
			if (field->getType()->getListBase()->isBasicType())
			{
				Java << Ident2 << "__os.write(" << field->getName() << ");" << ENDL;
			}
			else
			{
				Java << Ident2 << "ListReader.write(__os, " << field->getName() << ");" << ENDL;
			}
		}
		else
		{
			Java << Ident2 << field->getName() << ".write(__os);" << ENDL;
		}
	}
	Java << Ident1 << "}" << ENDL;

	Java << "}" << ENDL; //end of class
	Java << ENDL;
}
//CStruct ends

//CList
void CList::toCpp(std::ostream & Hpp, std::ostream & Cpp)
{
	Hpp << Ident1 << "typedef std::vector<" << _elemType->getCppType() << "> " << _name << ";" << ENDL;
	if (!_elemType->isBasicType())
	{
		Hpp << Ident1 << "class " << _name << "__U__{};" << ENDL;
		Hpp << Ident1 << "void __read(cdf::CSimpleSerializer & __is, " << _name << "& v, " << _name << "__U__);" << ENDL;
		Hpp << Ident1 << "void __write(cdf::CSimpleSerializer & __os, const " << _name << "& v, " << _name << "__U__);" << ENDL;

		//__read
		Cpp << "//definition of __read and __write of " << _name << ENDL;
		Cpp << "void __read(cdf::CSimpleSerializer & __is, " << _name << "& v, " << _name << "__U__)" << ENDL;
		Cpp << "{" << ENDL;
		Cpp << Ident1 << "unsigned size = 0;\n" << Ident1 << "__is.readSize(size); " << ENDL;
		Cpp << ENDL;
		Cpp << Ident1 << "for(unsigned i = 0; i < size; i++)" << ENDL;
		Cpp << Ident1 << "{" << ENDL;
		Cpp << Ident2 << _elemType->getCppType() << " elem;" << ENDL;
		if (_elemType->getType() == EType::LIST) 
		{
			if (!_elemType->getListBase()->isBasicType())
			{
				Cpp << Ident2 << "::Rmi::__read(__is, elem, " << _elemType->getCppType() << "__U__());" << ENDL;
			}
			else
			{
				Cpp << Ident2 << "__is.read(elem);" << ENDL;
			}
		}
		else
		{
			Cpp << Ident2 << "elem.__read(__is);" << ENDL;
		}
		Cpp << Ident2 << "v.push_back(elem);" << ENDL;
		Cpp << Ident1 << "}" << ENDL;
		Cpp << "}" << ENDL;
		Cpp << ENDL;

		//__write
		Cpp << "void __write(cdf::CSimpleSerializer & __os, const " << _name << "& v, " << _name << "__U__)" << ENDL;
		Cpp << "{" << ENDL;
		Cpp << Ident1 << "unsigned size = v.size();" << ENDL;
		Cpp << Ident1 << "__os.writeSize(size);" << ENDL;
		Cpp << ENDL;
		Cpp << Ident1 << "for (auto elem : v)" << ENDL;
		Cpp << Ident1 << "{" << ENDL;
		if (_elemType->getType() == EType::LIST)
		{
			if (!_elemType->getListBase()->isBasicType())
			{
				Cpp << Ident2 << "::Rmi::__write(__os, elem, " << _elemType->getCppType() << "__U__());" << ENDL;
			}
			else
			{
				Cpp << Ident2 << "__os.write(elem);" << ENDL;
			}
		}
		else
		{
			Cpp << Ident2 << "elem.__write(__os);" << ENDL;
		}
		Cpp << Ident1 << "}" << ENDL;
		Cpp << "}" << ENDL;
		Cpp << ENDL;
	}

	Hpp << ENDL;
}

void CList::toJava(std::ostream & Java)
{
	if (_elemType->isBasicType())
	{
		return;
	}

	CTypePtr myTypePtr = CTypeManager::instance()->getType(_name);
	std::string myJavaArrayTypeName = myTypePtr->getJavaType();
	if (!CStructManager::instance()->addNewJavaArrayType(myJavaArrayTypeName))
	{
		return;
	}

	CTypePtr baseTypePtr = myTypePtr->getListBase();
	EType baseDataType = baseTypePtr->getType();

	Java << Ident1 << "public static " << myTypePtr->getJavaType() << " read(SerializeStream __is, " << myTypePtr->getJavaType() << " res){" << ENDL;
	Java << Ident2 << "int size = __is.readInt();" << ENDL;
	Java << Ident2 << "res = new " << myTypePtr->getNewJavaArray() << ";" << ENDL;
	Java << ENDL;
	Java << Ident2 << "for (int i = 0; i < size; ++i){" << ENDL;

	if (baseDataType == EType::STRUCT)
	{
		Java << Ident3 << baseTypePtr->getJavaType() << " val = new " << baseTypePtr->getJavaType() << "();" << ENDL;
	}
	else
	{
		Java << Ident3 << baseTypePtr->getJavaType() << " val = null;" << ENDL;
	}
	if (baseDataType == EType::BASIC)
	{
		Java << Ident3 << "val = __is.read(val);" << ENDL;
	}
	else if (baseDataType == EType::LIST)
	{
		if (baseTypePtr->getListBase()->isBasicType())
		{
			Java << Ident3 << "val = __is.read(val);" << ENDL;
		}
		else
		{
			Java << Ident3 << "val = ListReader.read(__is, val);" << ENDL;
		}
	}
	else
	{
		Java << Ident3 << "val.read(__is);" << ENDL;
	}
	Java << Ident3 << "res[i] = val;" << ENDL;
	Java << Ident2 << "}" << ENDL << ENDL;
	Java << Ident2 << "return res;" << ENDL;
	Java << Ident1 << "}" << ENDL << ENDL;

	//write
	Java << Ident1 << "public static void write(SerializeStream __os, " << myTypePtr->getJavaType() << " v){" << ENDL;
	Java << Ident2 << "int size = v.length;" << ENDL;
	Java << Ident2 << "__os.write(size);" << ENDL;
	Java << ENDL;
	Java << Ident2 << "for (int i = 0; i < size; i++){" << ENDL;

	if (baseDataType == EType::BASIC)
	{
		Java << Ident3 << "__os.write(v[i]);" << ENDL;
	}
	else if (baseDataType == EType::LIST)
	{
		if (baseTypePtr->getListBase()->isBasicType())
		{
			Java << Ident3 << "__os.write(v[i]);" << ENDL;
		}
		else
		{
			Java << Ident3 << "ListReader.write(__os, v[i]);" << ENDL;
		}
	}
	else
	{
		Java << Ident3 << "v[i].write(__os);" << ENDL;
	}

	Java << Ident2 << "}" << ENDL;
	Java << Ident1 << "}" << ENDL << ENDL;
}
//CList ends

//CEnum
CEnum::CEnum(const std::string & name)
:CStructBase()
,_name(name)
{

}

//const std::string & CEnum::getName()
//{ 
//	return _name; 
//}

bool CEnum::hasElem(const std::string & elemName)
{
	bool res = (_elemNameSet.find(elemName) != _elemNameSet.end());

	return res;
}

bool CEnum::isElemValueOk(int val)
{
	if (val < 0)
	{
		return false;
	}

	if (_elems.empty())
	{
		return true;
	}

	if (val <= _elems.begin()->second)
	{
		return false;
	}

	return true;
}

void CEnum::addElem(const std::string & elemName, int val)
{
	if (!hasElem(elemName) &&
		isElemValueOk(val))
	{
		_elems.push_back({elemName, val});
		_elemNameSet.insert(elemName);
	}
}

int CEnum::getMaxValue()
{
	if (_elems.size() > 0)
	{
		return _elems.begin()->second;
	}

	return 0;
}

void CEnum::toCpp(std::ostream & Hpp, std::ostream & Cpp)
{
	Hpp << Ident1 << "enum " << _name << ENDL;
	Hpp << Ident1 << "{" << ENDL;
	for (auto fPair : _elems)
	{
		Hpp << Ident2 << fPair.first << " = " << fPair.second << "," << ENDL;
	}
	Hpp << Ident1 << "};" << ENDL;
	Hpp << ENDL;
}

void CEnum::toJava(std::ostream & Java)
{
	Java << "public class " << _name << "{" << ENDL;
	Java << Ident1 << "private " << _name << "(){}\n" << ENDL;
	for (auto fPair : _elems)
	{
		Java << Ident1 << "public static int " << fPair.first << " = " << fPair.second << ";" << ENDL;
	}

	Java << "}" << ENDL;
	Java << ENDL;
}
//CEnum ends

//Struct Manager
CStructManager::CStructManager()
{

}

CStructManager::~CStructManager()
{

}

CStructManager * CStructManager::instance()
{
	static CStructManager _inst;

	return &_inst;
}

bool CStructManager::loadConfig(const std::string & configFilePath)
{
	Message::Db::Tables::SeqTStructConfig allConfigs;
	Message::Db::Tables::Loader::loadFile(configFilePath, allConfigs);

	for (auto config : allConfigs)
	{
		FieldConfig fields;
		if (config.type != EType::LIST)
		{
			if (!parseFields(config.fields, fields))
			{
				return false;
			}
		}

		bool res = false;
		switch (config.type)
		{
		case EType::STRUCT:
			res = parseStruct(config.name, fields);
			break;
		case EType::LIST:
			res = parseList(config.name, config.fields);
			break;
		case EType::ENUM:
			res = parseEnum(config.name, fields);
			break;
		default:
			CDF_LOG_TRACE("CStructManager::loadConfig", "StructTypeError: " << config.name);
			assert(false);
			break;
		}

		if (!res)
		{
			return false;
		}
	}

	return true;
}

void CStructManager::toCpp(const std::string & outCppPath)
{
	std::string fileName = outCppPath + "/" + "DataStructDef";
	std::ofstream Hpp(fileName + ".h");
	if (!Hpp)
	{
		CDF_LOG_TRACE("CStructManager::toCpp", "Cannot open file " << fileName << ".h");
		return;
	}

	std::ofstream Cpp(fileName + ".cpp");
	if (!Cpp)
	{
		CDF_LOG_TRACE("CStructManager::toCpp", "Cannot open file " << fileName << ".cpp");
		return;
	}

	Hpp << "#ifndef __RMI_DATA_STRUCT_DEF_H__" << ENDL;
	Hpp << "#define __RMI_DATA_STRUCT_DEF_H__" << ENDL;
	Hpp << ENDL;
	Hpp << "#include \"framework/serialize/simpleserializer.h\"" << ENDL;
	Hpp << "#include \"framework/util/refshared.h\"" << ENDL;
	Hpp << "#include <string>" << ENDL;
	Hpp << "#include <vector>" << ENDL;
	Hpp << "#include <set>" << ENDL;
	Hpp << "#include <map>" << ENDL;
	Hpp << ENDL;
	Hpp << "namespace Rmi" << ENDL;
	Hpp << "{" << ENDL;

	Cpp << "#include \"DataStructDef.h\"" << ENDL;
	Cpp << ENDL;
	Cpp << "namespace Rmi" << ENDL;
	Cpp << "{" << ENDL;
	Cpp << ENDL;

	for (auto structPtr : _structs)
	{
		structPtr->toCpp(Hpp, Cpp);
	}

	Cpp << ENDL;
	Cpp << "} //end of namespace Rmi" << ENDL;
	Cpp << ENDL;

	Hpp << "} // end of namespace Rmi" << ENDL;
	Hpp << "#endif // end of __RMI_DATA_STRUCT_DEF_H__" << ENDL;
	Hpp << ENDL;
}

void CStructManager::toJava(const std::string & outJavaDir)
{
	std::string listReader = outJavaDir + "/ListReader.java";
	std::ofstream fListReader(listReader);
	if (!fListReader)
	{
		CDF_LOG_TRACE("CStructManager::toJava", "Cannot Open " + listReader);
		return;
	}

	genJavaHeaders(fListReader);
	fListReader << "public class ListReader{" << ENDL;
	fListReader << Ident1 << "private ListReader(){}" << ENDL;
	fListReader << ENDL;

	for (auto structPtr : _structs)
	{
		if (structPtr->getDataType() == EType::LIST)
		{
			structPtr->toJava(fListReader);
		}
		else
		{
			std::string structReader = outJavaDir + "/" + structPtr->getName() + ".java";
			std::ofstream fStructReader(structReader);
			if (!fStructReader)
			{
				CDF_LOG_TRACE("CStructManager::toJava", "Cannot Open " + structReader);
				continue;
			}

			genJavaHeaders(fStructReader);
			structPtr->toJava(fStructReader);
		}
	}

	fListReader << "}" << ENDL << ENDL;
}

bool CStructManager::parseFields(const std::string & strFields, FieldConfig & fields)
{
	std::vector<std::string> fieldPairs;
	cdf::CStrFun::split(fieldPairs, strFields.c_str(), '#');
	for (auto fp : fieldPairs)
	{
		std::vector<std::string> fPair;
		cdf::CStrFun::split(fPair, fp.c_str(), ':');
		if (fPair.size() != 2)
		{
			CDF_LOG_TRACE("CStructManager::parseFields", "FieldConfigError: " << strFields);
			assert(false);
			return false;
		}

		fields.push_back(fPair);
	}

	return true;
}

bool CStructManager::addNewJavaArrayType(const std::string & javaArrayType)
{
	if (_javaListSet.count(javaArrayType) > 0)
	{
		return false;
	}

	_javaListSet.insert(javaArrayType);
	return true;
}

bool CStructManager::parseStruct(const std::string & name, const FieldConfig & fileds)
{
	if (CTypeManager::instance()->hasType(name))
	{
		CDF_LOG_TRACE("CStructManager::parseStruct", "Duplicated definition of " << name);
		assert(false);
		return false;
	}

	CStructPtr structPtr = new CStruct(name);
	for (auto fPair : fileds)
	{
		std::string fieldName = fPair[0];
		std::string fieldType = fPair[1];

		if (structPtr->hasField(fieldName))
		{
			CDF_LOG_TRACE("CStructManager::parseStruct", 
				"Duplicated definition of field " << fieldName << " within struct " << name);
			assert(false);
			return false;
		}

		CTypePtr typePtr = CTypeManager::instance()->getType(fieldType);
		if (NULL == typePtr)
		{
			CDF_LOG_TRACE("CStructManager::parseStruct",
				"Type " << fieldName << " within struct " << name << " is not defined");
			assert(false);
			return false;
		}

		structPtr->addField(typePtr, fieldName);
	}

	_structs.push_back(structPtr);
	CTypeManager::instance()->addType(EType::STRUCT, name);

	return true;
}

bool CStructManager::parseList(const std::string & name, const std::string & baseTypeName)
{
	if (CTypeManager::instance()->hasType(name))
	{
		CDF_LOG_TRACE("CStructManager::parseList", "Duplicated definition of " << name);
		assert(false);
		return false;
	}

	CTypePtr listBasetypePtr = CTypeManager::instance()->getType(baseTypeName);
	if (NULL == listBasetypePtr)
	{
		CDF_LOG_TRACE("CStructManager::parseList", 
			"Base type " << baseTypeName << " for List type " << name << " is not defined");
		assert(false);
		return false;
	}

	CListPtr listPtr = new CList(name, listBasetypePtr);
	_structs.push_back(listPtr);

	CTypePtr listTypePtr = new CType(EType::LIST, name);
	listTypePtr->setListBase(listBasetypePtr);
	CTypeManager::instance()->addType(listTypePtr);

	return true;
}

bool CStructManager::parseEnum(const std::string & name, const FieldConfig & fileds)
{
	if (CTypeManager::instance()->hasType(name))
	{
		CDF_LOG_TRACE("CStructManager::parseEnum", "Duplicated definition of " << name);
		assert(false);
		return false;
	}

	CEnumPtr enumPtr = new CEnum(name);
	for (auto fPair : fileds)
	{
		if (!cdf::CStrFun::is_num(fPair[1].c_str()))
		{
			CDF_LOG_TRACE("CStructManager::parseEnum", "Value of enum type must be a num. See definition of " << name);
			assert(false);
			return false;
		}

		std::string elemName = fPair[0];
		int elemVal = cdf::CStrFun::str_to_int32(fPair[1].c_str());
		if (enumPtr->hasElem(elemName))
		{
			CDF_LOG_TRACE("CStructManager::parseEnum", "Deplicated declaration of " << elemName << ". See definition of " << name);
			assert(false);
			return false;
		}
		if (elemVal < 0)
		{
			CDF_LOG_TRACE("CStructManager::parseEnum", "Enum Value must ge 0. See definition of " << name);
			assert(false);
			return false;
		}

		if (!enumPtr->isElemValueOk(elemVal))
		{
			CDF_LOG_TRACE("CStructManager::parseEnum", 
				"Enum Value must gt " << enumPtr->getMaxValue() << ". See definition of " << name);
			assert(false);
			return false;
		}

		enumPtr->addElem(elemName, elemVal);
	}

	_structs.push_back(enumPtr);
	CTypeManager::instance()->addType(EType::ENUM, name);

	return true;
}

void CStructManager::genJavaHeaders(std::ostream & Java)
{
	Java << "package rmi.client;" << ENDL;
	Java << ENDL;
	Java << "import rmi.SerializeStream;" << ENDL;
	Java << "import java.util.Date;" << ENDL;
	Java << ENDL;
}
