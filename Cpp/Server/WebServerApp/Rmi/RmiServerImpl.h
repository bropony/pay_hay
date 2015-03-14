#ifndef __RMI_RMI_SERVER_IMPL_H__
#define __RMI_RMI_SERVER_IMPL_H__

#include "Rmi/RmiServer.h"

namespace Rmi
{
	class CRmiServerImpl
		: public virtual CRmiServer
	{
	public:
		virtual void test(cdf::CDateTime & dt, const CTestCallbackPtr & testCB);
		virtual void showError(cdf::CDateTime & dt, const CShowErrorCallbackPtr & showErrorCB);
		virtual void uploadImage(std::string & img, const CUploadImageCallbackPtr & uploadImageCB);
		virtual void echo(STest & input, const CEchoCallbackPtr & echoCB);

	};
}

#endif