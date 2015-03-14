#include "Generator.h"
#include <locale>
#include "framework/util/stringfun.h"

using namespace cg;

bool CCodeGenerator::init(const std::string & outPath, const std::string & jsPath, std::string & headRoot)
{
	_outPath = outPath;
	_jsPath = jsPath;
	_headRoot = headRoot;

	_msgHpp.open(outPath + "/MessageHandler.h", std::ios::out);
	_msgCpp.open(outPath + "/MessageHandler.cpp", std::ios::out);

	_eventHpp.open(outPath + "/EventHandler.h", std::ios::out);
	_eventCpp.open(outPath + "/EventHandler.cpp", std::ios::out);

	_js.open(jsPath + "/" + "rmi.js", std::ios::out);

	_eventHandlerName = "_eventHandler";
	_eventClassName = "CEventHandler";

	return true;
}

void CCodeGenerator::genMsgCode()
{
	std::string ident1 = CTypes::getIdent(1);
	std::string ident2 = CTypes::getIdent(2);
	std::string ident3 = CTypes::getIdent(3);
	std::string ident4 = CTypes::getIdent(4);
	std::string className = "CMassageHandler";

	states(_msgHpp);
	//Macro def starts
	_msgHpp << "#ifndef __MHZ_MSG_HANDLER_H_MHZ__\n";
	_msgHpp << "#define __MHZ_MSG_HANDLER_H_MHZ__\n\n";

	//headers;
	_msgHpp << "#include \"framework/websocket/websocketmessagehandler.h\"\n";
	_msgHpp << "#include \"" << _headRoot << "/EventHandler.h\"\n";
	_msgHpp << "\n";

	//namespace starts;
	_msgHpp << "namespace cg\n";
	_msgHpp << "{\n";

	//class begin
	_msgHpp << ident1 << "class " << className << "\n";
	_msgHpp << ident2 << ": public virtual cdf::CWsMessageHandler\n";
	_msgHpp << ident1 << "{\n";
	_msgHpp << ident1 << "public:\n";
	_msgHpp << ident2 << "virtual void onMessage(const cdf::CWSContextPtr & context,\n";
	_msgHpp << ident3 << "const std::string & data,\n";
	_msgHpp << ident3 << "websocketpp::frame::opcode::value operCode);\n\n";

	_msgHpp << ident2 << "inline void setEventHandler(const CEventHandlerPtr & eventHandler)\n";
	_msgHpp << ident2 << "{\n";
	_msgHpp << ident3 << _eventHandlerName << " = " << "eventHandler;\n";
	_msgHpp << ident2 << "}\n";

	_msgHpp << ident1 << "private:\n";
	_msgHpp << ident2 << "CEventHandlerPtr " << _eventHandlerName << ";\n";

	//class ends
	_msgHpp << ident1 << "};\n";
	_msgHpp << ident1 << "typedef cdf::CHandle<" << className << "> " << className << "Ptr;\n";
	_msgHpp << "\n";

	//namespace ends;
	_msgHpp << "} //close namespace cg;\n\n";

	//macro def ends;
	_msgHpp << "#endif //__MHZ_MSG_HANDLER_H_MHZ__\n";

	_msgCpp << "#include \"" << _headRoot << "/MessageHandler.h\"\n";
	_msgCpp << "#include \"" << _headRoot << "/EventCommon.h\"\n";
	_msgCpp << "#include \"Config/ErrorCodeManager.h\"\n";
	_msgCpp << "#include \"framework/json/value.h\"\n";
	_msgCpp << "#include \"framework/websocket/websocketserver.h\"\n";
	_msgCpp << "\n";
	_msgCpp << "using namespace cg;\n";
	_msgCpp << "using namespace WebServerApp;\n";
	_msgCpp << "\n";

	//func starts
	_msgCpp << "void " << className << "::onMessage(const cdf::CWSContextPtr & context,\n";
	_msgCpp << ident1 << "const std::string & data,\n";
	_msgCpp << ident1 << "websocketpp::frame::opcode::value operCode)\n";
	_msgCpp << "{\n";

	//body
	_msgCpp << ident1 << "if (operCode == websocketpp::frame::opcode::binary)\n";
	_msgCpp << ident1 << "{\n";
	_msgCpp << ident2 << "int msgId = int(data[0]);\n";
	_msgCpp << ident2 << "int type = int(data[1]);\n";
	_msgCpp << ident2 << "try\n" << ident2 << "{\n";
	_msgCpp << ident3 << _eventHandlerName << "->onUploadImg(type, data.substr(2), context);\n";
	_msgCpp << ident3 << "Json::Value __res;\n";
	_msgCpp << ident3 << "__res[\"msg_id\"] = msgId;\n";
	_msgCpp << ident3 << "cdf::CWebsocketServer::instance()->sendData(context, __res.toFastString());\n";
	_msgCpp << ident2 << "}\n";
	_msgCpp << ident2 << "catch (const cdf::CException & ex)\n" << ident2 << "{\n";
	_msgCpp << ident3 << "CEventHandler::onError(ex.code(), ex.what(), msgId, context);\n";
	_msgCpp << ident2 << "}\n";
	_msgCpp << ident2 << "catch (...)\n" << ident2 << "{\n";
	_msgCpp << ident3 << "CEventHandler::onError(10000, \"ExceptionCodeUnkown\", msgId, context);\n";
	_msgCpp << ident2 << "}\n\n";
	_msgCpp << ident2 << "return;\n";
	_msgCpp << ident1 << "}\n\n";

	_msgCpp << ident1 << "Json::Value js;\n";
	_msgCpp << ident1 << "try\n" << ident1 << "{\n";
	_msgCpp << ident2 << "js.parse(data);\n";
	_msgCpp << ident1 << "}\n";
	_msgCpp << ident1 << "catch(...)\n" << ident1 << "{\n";
	_msgCpp << ident2 << _eventClassName << "::onError(10002, \"ExceptionBadJsData\", 0, context);\n";
	_msgCpp << ident1 << "}\n\n";

	std::string eventType = "eventType";
	_msgCpp << ident1 << "int msgId = js[\"msg_id\"].asInt();\n";
	_msgCpp << ident1 << "std::string " << eventType << " = js[\"event\"].asString();\n";
	_msgCpp << "\n";
	_msgCpp << ident1 << "try\n" << ident1 << "{\n";
	
	bool isFirstIf = true;
	const SeqEvent & events = CEventManager::instance()->getEvents();
	for (auto event : events)
	{
		_msgCpp << ident2;
		if (!isFirstIf)
		{
			_msgCpp << "else ";
		}
		isFirstIf = false;
		_msgCpp << "if (" << eventType << " == \"" << event.getName() << "\")\n";
		_msgCpp << ident2 << "{\n";
		_msgCpp << ident3 << event.getCbName() << "Ptr cb = new ";
		_msgCpp	<< event.getCbName() << "(msgId, \"" << event.getName() << "\", context);\n\n";
		_msgCpp << ident3 << _eventHandlerName << "->" << event.getName() << "(\n";

		bool isFirstParam = true;
		for (auto param : event.getInParams())
		{
			if (!isFirstParam)
			{
				_msgCpp << ", \n";
			}
			isFirstParam = false;

			std::string paramFmt = "JS_" + cdf::CStrFun::to_upper(param.type.c_str()) + "(js, \"" + param.name + "\")";
			_msgCpp << ident4 << paramFmt;
		}
		if (!isFirstParam)
		{
			_msgCpp << ", \n";
		}
		_msgCpp << ident4 << "cb\n";
		_msgCpp << ident3 << ");\n";
		_msgCpp << ident2 << "}\n";
	}

	_msgCpp << ident2 << "else\n" << ident2 << "{\n";
	_msgCpp << ident3 << "CDF_LOG_TRACE(\"onMessage\", \"InvalidEventType: \" << eventType);\n";
	_msgCpp << ident3 << "CErrorCodeManager::throwException(\"Error_invalidOperation\");\n";
	_msgCpp << ident2 << "}\n";

	//catch
	_msgCpp << ident1 << "}\n";
	_msgCpp << ident1 << "catch (const cdf::CException & ex)\n" << ident1 << "{\n";
	_msgCpp << ident2 << "CEventHandler::onError(ex.code(), ex.what(), msgId, context);\n";
	_msgCpp << ident1 << "}\n";
	_msgCpp << ident1 << "catch (...)\n" << ident1 << "{\n";
	_msgCpp << ident2 << "CEventHandler::onError(10000, \"ExceptionCodeUnkown\", msgId, context);\n";
	_msgCpp << ident1 << "}\n";

	//func ends
	_msgCpp << "}\n";
}

void CCodeGenerator::genEventCode()
{
	std::string ident1 = CTypes::getIdent(1);
	std::string ident2 = CTypes::getIdent(2);
	std::string ident3 = CTypes::getIdent(3);
	std::string ident4 = CTypes::getIdent(4);
	std::string className = "CEventHandler";

	states(_eventHpp);
	//macros start
	_eventHpp << "#ifndef __MHZ_EVENT_HANDLER_MHZ_H__\n";
	_eventHpp << "#define __MHZ_EVENT_HANDLER_MHZ_H__\n\n";

	_eventHpp << "#include \"framework/websocket/websocketcontext.h\"\n";
	_eventHpp << "#include \"framework/json/value.h\"\n";
	_eventHpp << "#include \"Core/EventCommon.h\"\n";
	_eventHpp << "\n";

	//namespace starts
	_eventHpp << "namespace cg\n{\n";

	_eventCpp << "#include \"framework/websocket/websocketserver.h\"\n";
	_eventCpp << "#include \"framework/util/endian.h\"\n";
	_eventCpp << "#include \"" << _headRoot << "/EventHandler.h\"\n";
	_eventCpp << "\n";

	_eventCpp << "using namespace cg;\n\n";

	for (auto event : CEventManager::instance()->getEvents())
	{
		event.gencallback(_eventHpp, _eventCpp);
	}

	_eventHpp << "\n" << ident1 << "//EventHandler\n";
	_eventHpp << ident1 << "class " << className << "\n";
	_eventHpp << ident2 << ": public virtual cdf::CRefShared\n";
	_eventHpp << ident1 << "{\n"; //class starts
	_eventHpp << ident1 << "public:\n";

	//onError
	_eventHpp << ident2 << "static void onError(";
	_eventHpp << "int errorCode, const std::string & errorMsg, int msgId, const cdf::CWSContextPtr & context);\n\n";

	_eventHpp << ident2 << "virtual void onUploadImg(int type, const std::string & img, const cdf::CWSContextPtr & context) = 0;\n\n";

	for (auto event : CEventManager::instance()->getEvents())
	{
		_eventHpp << ident2 << "virtual void " << event.getFuncSig() << " = 0;\n";
	}

	_eventHpp << ident1 << "};\n"; //class ends
	_eventHpp << ident1 << "typedef cdf::CHandle<" << className << "> " << className << "Ptr;\n";

	//namespace ends
	_eventHpp << "} //close namespace cg\n\n";
	//macros end
	_eventHpp << "#endif //__MHZ_EVENT_HANDLER_MHZ_H__\n";

	_eventCpp << "void " << className << "::onError(";
	_eventCpp << "int errorCode, const std::string & errorMsg, int msgId, const cdf::CWSContextPtr & context)\n";
	_eventCpp << "{\n";
	_eventCpp << ident1 << "Json::Value jsError;\n";
	_eventCpp << ident1 << "jsError[\"event\"] = \"error\";\n";
	_eventCpp << ident1 << "jsError[\"msg_id\"] = msgId;\n";
	_eventCpp << ident1 << "jsError[\"what\"] = errorMsg;\n";
	_eventCpp << ident1 << "jsError[\"code\"] = errorCode;\n\n";
	_eventCpp << ident1 << "cdf::CWebsocketServer::instance()->sendData(context, jsError.toFastString());\n";
	_eventCpp << "}\n\n";
}

void CCodeGenerator::genJsCode()
{
	std::string ident1 = CTypes::getIdent(1);
	std::string ident2 = CTypes::getIdent(2);
	std::string ident3 = CTypes::getIdent(3);
	std::string ident4 = CTypes::getIdent(4);
	std::string ident5 = CTypes::getIdent(5);

	states(_js);
	_js << "var rmiDef = {\n"; //starts
	for (auto event : CEventManager::instance()->getEvents())
	{
		_js << ident1 << event.getName() << ": function(callback";

		for (auto param : event.getInParams())
		{
			_js << ", " << param.name;
		}

		_js << "){\n"; //function body

		_js << ident2 << "var jsData = {}\n";
		_js << ident2 << "jsData.msg_id = this.getMsgId();\n";
		_js << ident2 << "jsData.event = \"" << event.getName() << "\";\n";
		_js << ident2 << "callback.event = jsData.event;\n";

		_js << ident2 << "if (callback && (typeof(callback) != \"object\")){\n";
		_js << ident3 << "cc.log(\"Param callback of " << event.getName()
			<< " expects an object type data\");\n";
		_js << ident3 << "return;\n";
		_js << ident2 << "}\n";

		//_js << ident2 << "jsData[\"callback\"] = callback;\n\n";

		for (auto param : event.getInParams())
		{
			_js << ident2 << "if (typeof(" << param.name << ") != \""<< param.getJsonType() << "\"){\n";
			_js << ident3 << "cc.log(\"Param " << param.name << " of " << event.getName() 
				<< " expects a(n) " << param.type << " type data\");\n";
			_js << ident3 << "return;\n";
			_js << ident2 << "}\n";

			if (param.type == "date")
			{
				_js << ident2 << "jsData[\"" << param.name << "\"] = " << param.name << ".getTime();\n\n";
			}
			else
			{
				_js << ident2 << "jsData[\"" << param.name << "\"] = " << param.name << ";\n\n";
			}
		}
		
		_js << ident2 << "this.send(callback, jsData);\n";
		_js << ident1 << "},\n\n\n"; // end of function body
	}

	_js << ident1 << "onCallback: function(cb, eventName, jsData){\n";
	_js << ident2 << "if (!cb){ return; }\n\n";
	//_js << ident2 << "var eventName = jsDate.event;\n\n";

	_js << ident2 << "if (eventName == \"error\"){\n";
	_js << ident3 << "if (cb.onError){cb.onError(jsData.what, jsData.code);}\n";
	_js << ident3 << "else{ViewManager.navigator.addChild(new ErrorLabel(jsData.what, jsData.code));}\n";
	_js << ident3 << "return;\n";
	_js << ident2 << "}\n";
	_js << ident2 << "else if (!cb.onResponse){\n";
	_js << ident3 << "return;\n";
	_js << ident2 << "}\n\n";

	for (auto event : CEventManager::instance()->getEvents())
	{
		_js << ident2 << "if (eventName == \"" << event.getName() << "\"){\n";
		_js << ident3 << "cb.onResponse(";
		bool isFirst = true;
		for (auto param : event.getOutParams())
		{
			if (!isFirst){ _js << ", "; }
			isFirst = false;
			if (param.type == "date")
			{
				_js << "new Date(jsData." << param.name << ")";
			}
			else
			{
				_js << "jsData." << param.name;
			}
		}
		_js << ");\n";
		_js << ident3 << "return;\n";
		_js << ident2 << "}\n";
	}
	_js << ident1 << "},\n";

	_js << "};\n\n"; //ends

	_js << "//the Rmi Instance\n";
	_js << "var Rmi = RmiBase.extend(rmiDef);\n";
}

void CCodeGenerator::close()
{
	_msgHpp.close();
	_msgCpp.close();
	_eventHpp.close();
	_eventCpp.close();

	_js.close();
}

void CCodeGenerator::states(std::ofstream & of)
{
	of << "/******************************************************************************\n";
	of << "* This file is AUTO-GENERATED by CodeGenerator.\n";
	of << "* DONNOT modify it by hands UNLESS you know what you are doing.\n";
	of << "*\n";
	of << "* To aquire for source codes of the Generator or for any help,\n";
	of << "* please mail to [ahda86@gmail.com].\n";
	of << "*\n";
	of << "* Bug Reports & Improvement Suggestions are Appreciated.\n";
	of << "******************************************************************************/\n\n\n";
}