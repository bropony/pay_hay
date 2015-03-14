#include "EventConfigManager.h"
#include "Message/Db/Tables/Loader/TEventConfigLoader.h"
#include "framework/log/loggerutil.h"

using namespace cg;

//class CMethod
CMethod::CMethod(int eventId, const std::string & name)
:_eventId(eventId)
,_name(name)
,_cbName(name)
{
	if (_cbName[0] >= 'a' && _cbName[0] <= 'z')
	{
		_cbName[0] -= 32;
	}

	_javaCbName = _cbName + "Callback";

	_cbName = "C" + _cbName;
	_cbName += "Callback";
}

CMethod::~CMethod()
{

}

bool CMethod::parseParams(const FieldConfig & inFields, const FieldConfig & outFiels)
{
	std::set<std::string> usedNameSet;
	usedNameSet.insert(_name);

	if (parseFields(inFields, _inParams, usedNameSet, true) &&
		parseFields(outFiels, _outParams, usedNameSet, false))
	{
		return true;
	}

	return false;
}

bool CMethod::parseFields(const FieldConfig & fields, SeqField & params, std::set<std::string> & usedNameSet, bool isIn)
{
	std::string & sig = isIn ? _inSignature : _outSignature;

	if (isIn)
	{
		sig = _name + "(";
	}
	else
	{
		sig = "response(";
	}

	bool isFirst = true;
	for (auto field : fields)
	{
		std::string fieldName = field[0];
		std::string typeName = field[1];
		if (usedNameSet.count(fieldName) > 0)
		{
			CDF_LOG_TRACE("CMethod::parseFields", "field name " << fieldName << " is used");
			assert(false);
			return false;
		}
		usedNameSet.insert(fieldName);

		CTypePtr fieldTypePtr = CTypeManager::instance()->getType(typeName);
		if (NULL == fieldTypePtr)
		{
			CDF_LOG_TRACE("CMethod::parseFields", "field type " << typeName << " is not defined");
			assert(false);
			return false;
		}

		CFieldPtr fieldPtr = new CField(fieldTypePtr, fieldName);
		params.push_back(fieldPtr);

		if (isFirst)
		{
			isFirst = false;
		}
		else
		{
			sig += ", ";
		}

		sig += fieldTypePtr->getCppType();
		if (fieldTypePtr->isCompositeType())
		{
			sig += " &";
		}
		sig += " ";
		sig += fieldName;
	}

	if (isIn)
	{
		if (!isFirst)
		{
			sig += ", ";
		}

		sig += "const " + _cbName + "Ptr & " + _name + "CB";
	}
	sig += ")";

	return true;
}

void CMethod::callbacksToCpp(std::ofstream & Hpp, std::ofstream & Cpp)
{
	Hpp << Ident1 << "class " << _cbName << ENDL;
	Hpp << Ident2 << ": public virtual CRmiCallbackBase" << ENDL;
	Hpp << Ident1 << "{" << ENDL;
	Hpp << Ident1 << "public:" << ENDL;
	Hpp << Ident2 << _cbName << "(const cdf::CWSContextPtr & context, int msgId);" << ENDL;
	Hpp << ENDL;
	Hpp << Ident2 << "void " << _outSignature << ";" << ENDL;
	Hpp << Ident1 << "};" << ENDL;
	Hpp << Ident1 << "typedef cdf::CHandle<" << _cbName << "> " << _cbName << "Ptr;" << ENDL;
	Hpp << ENDL;
	 
	//cpp
	Cpp << _cbName << "::" << _cbName << "(const cdf::CWSContextPtr & context, int msgId)" << ENDL;
	Cpp << ":CRmiCallbackBase(context, msgId)" << ENDL;
	Cpp << "{\n}" << ENDL;
	Cpp << ENDL;

	Cpp << "void " << _cbName << "::" << _outSignature << ENDL;
	Cpp << "{" << ENDL; //begin of callback

	Cpp << Ident1 << "cdf::CSimpleSerializer __os;" << ENDL;
	Cpp << Ident1 << "__os.startToWrite();" << ENDL;
	Cpp << ENDL;
	Cpp << Ident1 << "__os.write(_msgId);" << ENDL;
	Cpp << Ident1 << "__os.write(true);" << ENDL;
	Cpp << ENDL;

	for (auto field : _outParams)
	{
		const cg::CTypePtr fieldTypePtr = field->getType();
		const cg::EType dataType = fieldTypePtr->getType();
		if (dataType == cg::EType::BASIC)
		{
			Cpp << Ident1 << "__os.write(" << field->getName() << ");" << ENDL;
		}
		else if (dataType == cg::EType::LIST)
		{
			if (fieldTypePtr->getListBase()->isBasicType())
			{
				Cpp << Ident1 << "__os.write(" << field->getName() << ");" << ENDL;
			}
			else
			{
				Cpp << Ident1 << "::Rmi::__write(" << field->getName() << ");" << ENDL;
			}
		}
		else
		{
			Cpp << Ident1 << field->getName() << ".__write(__os);" << ENDL;
		}
	}

	Cpp << ENDL;
	Cpp << Ident1 << "__response(__os);" << ENDL;

	Cpp << "}" << ENDL; //end of callback

	Cpp << ENDL << ENDL;
}

void CMethod::methodsToCpp(std::ofstream & Hpp, std::ofstream & Cpp)
{
	std::string scope = "CRmiServer::";

	Hpp << Ident2 << "void " << "__" << _name << "(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);" << ENDL;
	Hpp << Ident2 << "virtual void " << _inSignature << " = 0;" << ENDL;
	Hpp << Ident1 << ENDL;

	Cpp << "void " << scope << "__" << _name << "(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)" << ENDL;
	Cpp << "{" << ENDL; //begin of func

	for (auto field : _inParams)
	{
		const CTypePtr & fieldTypePtr = field->getType();
		Cpp << Ident1 << fieldTypePtr->getCppType() << " " << field->getName();
		if (!fieldTypePtr->isCompositeType())
		{
			if (fieldTypePtr->getName() != "bool")
			{
				Cpp << " = 0";
			}
			else
			{
				Cpp << " = false";
			}
		}
		Cpp << ";" << ENDL;
		
		EType dataType = fieldTypePtr->getType();
		if (dataType == EType::BASIC)
		{
			Cpp << Ident1 << "__is.read(" << field->getName() << ");" << ENDL;
		}
		else if (dataType == EType::LIST)
		{
			if (fieldTypePtr->getListBase()->isBasicType())
			{
				Cpp << Ident1 << "__is.read(" << field->getName() << ");" << ENDL;
			}
			else
			{
				Cpp << Ident1 << "::Rmi::__read(__is, " << field->getName() << ", " << fieldTypePtr->getName() << "__U__());" << ENDL;
			}
		}
		else
		{
			Cpp << Ident1 << field->getName() << ".__read(__is);" << ENDL;
		}

		Cpp << ENDL;
	}

	Cpp << Ident1 << _cbName << "Ptr" << " __cb = new " << _cbName << "(context, __msgId);" << ENDL;

	Cpp << Ident1 << _name << "(";
	for (auto field : _inParams)
	{
		Cpp << field->getName() << ", ";
	}

	Cpp << "__cb);" << ENDL;

	Cpp << "}" << ENDL; //end of func
	Cpp << ENDL;
}

void CMethod::callbacksToJava(std::ofstream & Java)
{
	Java << Ident1 << "public static abstract class " << _javaCbName;
	Java << " extends RmiCallbackBase {" << ENDL; //begin of CCCBBB

	Java << Ident2 << "public " << _javaCbName << "(){}" << ENDL;
	Java << ENDL;

	bool isFirst = true;
	Java << Ident2 << "public abstract void onResponse(";
	for (auto field : _outParams)
	{
		if (!isFirst)
		{
			Java << ", ";
		}
		else
		{
			isFirst = false;
		}

		Java << field->getType()->getJavaType() << " " << field->getName();
	}
	Java << ");" << ENDL;
	Java << Ident2 << "public abstract void onError(String what, int code);" << ENDL;
	Java << Ident2 << "public abstract void onTimeout();" << ENDL;
	Java << ENDL;

	Java << Ident2 << "@Override" << ENDL;
	Java << Ident2 << "public void __onResponse(SerializeStream __is){" << ENDL; //begin of __onResponse
	for (auto field : _outParams)
	{
		cg::CTypePtr fieldTypePtr = field->getType();
		cg::EType dataType = fieldTypePtr->getType();
		Java << Ident3 << fieldTypePtr->getJavaType() << " " << field->getName() << " = ";
		if (dataType == cg::EType::BASIC)
		{
			if (!fieldTypePtr->isCompositeType())
			{
				if (fieldTypePtr->getName() != "bool")
				{
					Java << "0;" << ENDL;
				}
				else
				{
					Java << "false;" << ENDL;
				}
			}
			else
			{
				Java << "null;" << ENDL;
			}

			Java << Ident3 << field->getName() << " = __is.read(" << field->getName() << ");" << ENDL;
		}
		else if (dataType == cg::EType::LIST)
		{
			Java << "null;" << ENDL;

			if (fieldTypePtr->getListBase()->isBasicType())
			{
				Java << Ident3 << field->getName() << " = __is.read(" << field->getName() << ");" << ENDL;
			}
			else
			{
				Java << Ident3 << field->getName() << " = ListReader.read(__is, " << field->getName() << ");" << ENDL;
			}
		}
		else
		{
			Java << "new " << fieldTypePtr->getName() << "();" << ENDL;

			Java << Ident3 << field->getName() << ".read(__is);" << ENDL;
		}
		Java << ENDL;
	}

	Java << Ident3 << "onResponse(";
	isFirst = true;
	for (auto field : _outParams)
	{
		if (!isFirst)
		{
			Java << ", ";
		}
		else
		{
			isFirst = false;
		}
		Java << field->getName();
	}

	Java << ");" << ENDL;

	Java << Ident2 << "}" << ENDL; // end of __onResponce
	Java << ENDL;

	Java << Ident2 << "@Override" << ENDL;
	Java << Ident2 << "public void __onError(String what, int code){" << ENDL;
	Java << Ident3 << "onError(what, code);" << ENDL;
	Java << Ident2 << "}" << ENDL;
	Java << ENDL;

	Java << Ident2 << "@Override" << ENDL;
	Java << Ident2 << "public void __onTimeout(){" << ENDL;
	Java << Ident3 << "onTimeout();" << ENDL;
	Java << Ident2 << "}" << ENDL;
	Java << ENDL;

	Java << Ident1 << "}" << ENDL; //end of CCCBBB
	Java << ENDL;
}

void CMethod::methodsToJava(std::ofstream & Java)
{
	Java << Ident2 << "public static void " << _name << "(" << _javaCbName << " clientCB__";
	for (auto field : _inParams)
	{
		Java << ", " << field->getType()->getJavaType() << " " << field->getName();
	}
	Java << "){" << ENDL; //begin of func
	Java << Ident3 << "SerializeStream __os = new SerializeStream();" << ENDL;
	Java << Ident3 << "__os.startToWrite();" << ENDL;
	Java << ENDL;
	Java << Ident3 << "__msgIdBase++;" << ENDL;
	Java << Ident3 << "__os.write(__msgIdBase);" << ENDL;
	Java << Ident3 << "__os.write(" << _eventId << ");" << ENDL;
	Java << ENDL;
	for (auto field : _inParams)
	{
		cg::CTypePtr fieldTypePtr = field->getType();
		cg::EType dataType = fieldTypePtr->getType();

		if (dataType == cg::EType::BASIC)
		{
			Java << Ident3 << "__os.write(" << field->getName() << ");" << ENDL;
		}
		else if (dataType == cg::EType::LIST)
		{
			if (fieldTypePtr->getListBase()->isBasicType())
			{
				Java << Ident3 << "__os.write(" << field->getName() << ");" << ENDL;
			}
			else
			{
				Java << Ident3 << "ListReader.write(__os, " << field->getName() << ");" << ENDL;
			}
		}
		else
		{
			Java << Ident3 << field->getName() << ".write(__os);" << ENDL;
		}
	}
	Java << ENDL;
	Java << Ident3 << "RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);" << ENDL;
	Java << Ident2 << "}" << ENDL; //end of func
	Java << ENDL;
}


//class CEventConfigManager
CEventConfigManager * CEventConfigManager::instance()
{
	static CEventConfigManager _inst;

	return &_inst;
}

bool CEventConfigManager::loadConfig(const std::string & configFile)
{
	Message::Db::Tables::SeqTEventConfig allConfigs;
	Message::Db::Tables::Loader::loadFile(configFile, allConfigs);

	for (auto config : allConfigs)
	{
		std::string methodName = config.event;
		if (_methodNameSet.count(methodName) > 0)
		{
			CDF_LOG_TRACE("CEventConfigManager::loadConfig", "duplicated definition of " << methodName);
			assert(false);
			return false;
		}

		FieldConfig inParams;
		FieldConfig outParams;
		if (!CStructManager::parseFields(config.inParams, inParams))
		{
			CDF_LOG_TRACE("CEventConfigManager::loadConfig", "Error occurs in in-params declaration of " << methodName);
			assert(false);
			return false;
		}

		if (!CStructManager::parseFields(config.outParams, outParams))
		{
			CDF_LOG_TRACE("CEventConfigManager::loadConfig", "Error occurs in out-params declaration of " << methodName);
			assert(false);
			return false;
		}

		CMethodPtr methodPtr = new CMethod(config.eventId, config.event);
		if (!methodPtr->parseParams(inParams, outParams))
		{
			CDF_LOG_TRACE("CEventConfigManager::loadConfig", "Error occurs in parsing declaration of " << methodName);
			assert(false);
			return false;
		}

		_methods.push_back(methodPtr);
		_methodNameSet.insert(methodName);
	}

	return true;
}

void CEventConfigManager::toCpp(const std::string & cppBase)
{
	std::string hppFile = cppBase + "/RmiServer.h";
	std::string cppFile = cppBase + "/RmiServer.cpp";
	std::ofstream Hpp(hppFile);
	if (!Hpp)
	{
		CDF_LOG_TRACE("CEventConfigManager::toCpp", "Cannot open " + hppFile);
		return;
	}
	std::ofstream Cpp(cppFile);
	if (!Cpp)
	{
		CDF_LOG_TRACE("CEventConfigManager::toCpp", "Cannot open " + cppFile);
		return;
	}

	Cpp << "#include \"RmiServer.h\"" << ENDL;
	Cpp << "#include \"Config/ErrorCodeManager.h\"" << ENDL;
	Cpp << ENDL;
	Cpp << "using namespace Rmi;" << ENDL;
	Cpp << ENDL;

	Hpp << "#ifndef __RMI_RMI_SERVER_H__" << ENDL;
	Hpp << "#define __RMI_RMI_SERVER_H__" << ENDL;
	Hpp << ENDL;
	Hpp << "#include \"framework/websocket/websocketcontext.h\"" << ENDL;
	Hpp << "#include \"framework/serialize/simpleserializer.h\"" << ENDL;
	Hpp << "#include \"framework/websocket/websocketserver.h\"" << ENDL;
	Hpp << "#include \"Rmi/DataStructDef.h\"" << ENDL;
	Hpp << "#include \"Rmi/RmiCallbackBase.h\"" << ENDL;
	Hpp << ENDL;
	Hpp << "namespace Rmi" << ENDL;
	Hpp << "{" << ENDL;

	for (auto methodPtr : _methods)
	{
		methodPtr->callbacksToCpp(Hpp, Cpp);
	}

	Hpp << Ident1 << "class CRmiServer" << ENDL;
	Hpp << Ident2 << ": public virtual cdf::CRefShared" << ENDL;
	Hpp << Ident1 << "{" << ENDL;
	Hpp << Ident1 << "public:" << ENDL;

	for (auto methodPtr : _methods)
	{
		methodPtr->methodsToCpp(Hpp, Cpp);
	}

	Hpp << Ident2 << "void __call(cdf::CSimpleSerializer & __is, const cdf::CWSContextPtr & context);" << ENDL;
	__callToCpp(Cpp);

	Hpp << ENDL;
	Hpp << Ident2 << "void onError(int msgId, const std::string & what, int code, const cdf::CWSContextPtr & context);" << ENDL;

	Hpp << Ident1 << "};" << ENDL;
	Hpp << Ident1 << "typedef cdf::CHandle<CRmiServer> CRmiServerPtr;" << ENDL;

	Hpp << "} //end of namespace Rmi" << ENDL;
	Hpp << "#endif // end of __RMI_RMI_SERVER_H__" << ENDL << ENDL;

	Cpp << ENDL;
	Cpp << "void CRmiServer::onError(int msgId, const std::string & what, int code, const cdf::CWSContextPtr & context)" << ENDL;
	Cpp << "{" << ENDL;
	Cpp << Ident1 << "cdf::CSimpleSerializer __os;" << ENDL;
	Cpp << Ident1 << "__os.startToWrite();" << ENDL;
	Cpp << Ident1 << "__os.write(msgId);" << ENDL;
	Cpp << Ident1 << "__os.write(false);" << ENDL;
	Cpp << Ident1 << "__os.write(what);" << ENDL;
	Cpp << Ident1 << "__os.write(code);" << ENDL;
	Cpp << ENDL;
	Cpp << Ident1 << "__os.encrypt();" << ENDL;
	Cpp << Ident1 << "cdf::CWebsocketServer::instance()->sendData(context, __os.getBuffer(), websocketpp::frame::opcode::value::BINARY);" << ENDL;
	Cpp << "}" << ENDL;

	Cpp << ENDL;
}

void CEventConfigManager::__callToCpp(std::ofstream & Cpp)
{
	std::string scope = "CRmiServer::";
	Cpp << "void " << scope << "__call(cdf::CSimpleSerializer & __is, const cdf::CWSContextPtr & context)" << ENDL;
	Cpp << "{" << ENDL; //begin of __call

	Cpp << Ident1 << "int __msgId = 0;" << ENDL;
	Cpp << Ident1 << "int __eventId = 0;" << ENDL;
	Cpp << ENDL;

	Cpp << Ident1 << "try" << ENDL;
	Cpp << Ident1 << "{" << ENDL;
	Cpp << Ident2 << "__is.read(__msgId);" << ENDL;
	Cpp << Ident2 << "__is.read(__eventId);" << ENDL;
	Cpp << Ident1 << "}" << ENDL;
	Cpp << Ident1 << "catch (const cdf::CException & ex)" << ENDL;
	Cpp << Ident1 << "{" << ENDL;
	Cpp << Ident2 << "onError(__msgId, ex.what(), ex.code(), context);" << ENDL;
	Cpp << Ident1 << "}" << ENDL;
	Cpp << ENDL;

	Cpp << Ident1 << "try" << ENDL;
	Cpp << Ident1 << "{" << ENDL;
	Cpp << Ident2 << "switch (__eventId)" << ENDL;
	Cpp << Ident2 << "{" << ENDL; //begin of switch

	for (auto methodPtr : _methods)
	{
		Cpp << Ident2 << "case " << methodPtr->getEventId() << ":" << ENDL;
		Cpp << Ident3 << "__" << methodPtr->getName() << "(__is, __msgId, context);" << ENDL;
		Cpp << Ident3 << "break;" << ENDL;
	}

	Cpp << Ident2 << "default:" << ENDL;
	Cpp << Ident3 << "WebServerApp::CErrorCodeManager::throwException(\"Error_NotRegisterdRmiCall\");" << ENDL;
	Cpp << Ident3 << "break;" << ENDL;

	Cpp << Ident2 << "}" << ENDL; //end of switch

	Cpp << Ident1 << "}" << ENDL;
	Cpp << Ident1 << "catch (const cdf::CException & ex)" << ENDL;
	Cpp << Ident1 << "{" << ENDL;
	Cpp << Ident2 << "onError(__msgId, ex.what(), ex.code(), context);" << ENDL;
	Cpp << Ident1 << "}" << ENDL;

	Cpp << "}" << ENDL; //endof of __call
}

void CEventConfigManager::toJava(const std::string & javaBase)
{
	std::string javaFile = javaBase + "/RmiClient.java";
	std::ofstream Java(javaFile);
	if (!Java)
	{
		CDF_LOG_TRACE("CEventConfigManager::toCpp", "Cannot open " + javaFile);
		return;
	}

	Java << "package rmi.client;" << ENDL;
	Java << ENDL;

	//imports
	Java << "import rmi.SerializeStream;" << ENDL;
	Java << "import rmi.RmiManager;" << ENDL;
	Java << "import rmi.RmiCallbackBase;" << ENDL;
	Java << "import java.util.Date;" << ENDL;
	Java << ENDL;

	Java << "public class RmiClient{" << ENDL; //begin of RmiClient

	Java << Ident1 << "private static int __msgIdBase = 0;" << ENDL;
	Java << ENDL;
	Java << Ident1 << "private RmiClient(){}" << ENDL;
	Java << ENDL;

	Java << Ident1 << "//Method definitions" << ENDL;
	for (auto methodPtr : _methods)
	{
		methodPtr->methodsToJava(Java);
	}

	Java << ENDL;
	Java << Ident1 << "//Callback definitions" << ENDL;
	for (auto methodPtr : _methods)
	{
		methodPtr->callbacksToJava(Java);
	}

	Java << "}" << ENDL; //end of RmiClient
}

