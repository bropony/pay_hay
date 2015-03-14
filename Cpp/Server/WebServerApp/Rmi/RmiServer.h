#ifndef __RMI_RMI_SERVER_H__
#define __RMI_RMI_SERVER_H__

#include "framework/websocket/websocketcontext.h"
#include "framework/serialize/simpleserializer.h"
#include "framework/websocket/websocketserver.h"
#include "Rmi/DataStructDef.h"
#include "Rmi/RmiCallbackBase.h"

namespace Rmi
{
	class CTestCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CTestCallback(const cdf::CWSContextPtr & context, int msgId);

		void response(cdf::CDateTime & testOut);
	};
	typedef cdf::CHandle<CTestCallback> CTestCallbackPtr;

	class CShowErrorCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CShowErrorCallback(const cdf::CWSContextPtr & context, int msgId);

		void response(std::string & out);
	};
	typedef cdf::CHandle<CShowErrorCallback> CShowErrorCallbackPtr;

	class CUploadImageCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CUploadImageCallback(const cdf::CWSContextPtr & context, int msgId);

		void response(std::string & fileName);
	};
	typedef cdf::CHandle<CUploadImageCallback> CUploadImageCallbackPtr;

	class CEchoCallback
		: public virtual CRmiCallbackBase
	{
	public:
		CEchoCallback(const cdf::CWSContextPtr & context, int msgId);

		void response(STest & output);
	};
	typedef cdf::CHandle<CEchoCallback> CEchoCallbackPtr;

	class CRmiServer
		: public virtual cdf::CRefShared
	{
	public:
		void __test(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void test(cdf::CDateTime & dt, const CTestCallbackPtr & testCB) = 0;
	
		void __showError(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void showError(cdf::CDateTime & dt, const CShowErrorCallbackPtr & showErrorCB) = 0;
	
		void __uploadImage(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void uploadImage(std::string & img, const CUploadImageCallbackPtr & uploadImageCB) = 0;
	
		void __echo(cdf::CSimpleSerializer & __is, int __msgId, const cdf::CWSContextPtr & context);
		virtual void echo(STest & input, const CEchoCallbackPtr & echoCB) = 0;
	
		void __call(cdf::CSimpleSerializer & __is, const cdf::CWSContextPtr & context);

		void onError(int msgId, const std::string & what, int code, const cdf::CWSContextPtr & context);
	};
	typedef cdf::CHandle<CRmiServer> CRmiServerPtr;
} //end of namespace Rmi
#endif // end of __RMI_RMI_SERVER_H__

