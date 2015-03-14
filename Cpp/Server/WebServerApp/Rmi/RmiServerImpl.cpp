#include "RmiServerImpl.h"
#include "Config/ErrorCodeManager.h"
#include "Resource/ImageManager.h"

using namespace Rmi;

void CRmiServerImpl::test(cdf::CDateTime & dt, const CTestCallbackPtr & testCB)
{
	testCB->response(dt);
}

void CRmiServerImpl::showError(cdf::CDateTime & dt, const CShowErrorCallbackPtr & showErrorCB)
{
	WebServerApp::CErrorCodeManager::throwException("Error_userDataError");
}

void CRmiServerImpl::uploadImage(std::string & img, const CUploadImageCallbackPtr & uploadImageCB)
{
	WebServerApp::CImagePtr newImg = WebServerApp::CImageManager::instance()->createImage("test.jpg", "null", img);
	
	uploadImageCB->response(newImg->getTUserImg().imgPath);
}

void CRmiServerImpl::echo(STest & input, const CEchoCallbackPtr & echoCB)
{
	echoCB->response(input);

	int res = 0;

}