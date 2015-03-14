#include "RmiServer.h"
#include "Config/ErrorCodeManager.h"

using namespace Rmi;

CTestCallback::CTestCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CTestCallback::response(cdf::CDateTime & testOut)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	__os.write(testOut);

	__response(__os);
}


CShowErrorCallback::CShowErrorCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CShowErrorCallback::response(std::string & out)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	__os.write(out);

	__response(__os);
}


CUploadImageCallback::CUploadImageCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CUploadImageCallback::response(std::string & fileName)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	__os.write(fileName);

	__response(__os);
}


CEchoCallback::CEchoCallback(const cdf::CWSContextPtr & context, int msgId)
:CRmiCallbackBase(context, msgId)
{
}

void CEchoCallback::response(STest & output)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();

	__os.write(_msgId);
	__os.write(true);

	output.__write(__os);

	__response(__os);
}


void CRmiServer::__test(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	cdf::CDateTime dt;
	__is.read(dt);

	CTestCallbackPtr __cb = new CTestCallback(context, __msgId);
	test(dt, __cb);
}

void CRmiServer::__showError(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	cdf::CDateTime dt;
	__is.read(dt);

	CShowErrorCallbackPtr __cb = new CShowErrorCallback(context, __msgId);
	showError(dt, __cb);
}

void CRmiServer::__uploadImage(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	std::string img;
	__is.read(img);

	CUploadImageCallbackPtr __cb = new CUploadImageCallback(context, __msgId);
	uploadImage(img, __cb);
}

void CRmiServer::__echo(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context)
{
	STest input;
	input.__read(__is);

	CEchoCallbackPtr __cb = new CEchoCallback(context, __msgId);
	echo(input, __cb);
}

void CRmiServer::__call(cdf::CSimpleSerializer & __is, const cdf::CWSContextPtr & context)
{
	int __msgId = 0;
	int __eventId = 0;

	try
	{
		__is.read(__msgId);
		__is.read(__eventId);
	}
	catch (const cdf::CException & ex)
	{
		onError(__msgId, ex.what(), ex.code(), context);
	}

	try
	{
		switch (__eventId)
		{
		case 12:
			__test(__is, __msgId, context);
			break;
		case 13:
			__showError(__is, __msgId, context);
			break;
		case 14:
			__uploadImage(__is, __msgId, context);
			break;
		case 15:
			__echo(__is, __msgId, context);
			break;
		default:
			WebServerApp::CErrorCodeManager::throwException("Error_NotRegisterdRmiCall");
			break;
		}
	}
	catch (const cdf::CException & ex)
	{
		onError(__msgId, ex.what(), ex.code(), context);
	}
}

void CRmiServer::onError(int msgId, const std::string & what, int code, const cdf::CWSContextPtr & context)
{
	cdf::CSimpleSerializer __os;
	__os.startToWrite();
	__os.write(msgId);
	__os.write(false);
	__os.write(what);
	__os.write(code);

	__os.encrypt();
	cdf::CWebsocketServer::instance()->sendData(context, __os.getBuffer(), websocketpp::frame::opcode::value::BINARY);
}

