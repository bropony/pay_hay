#include "RmiIncoming.h"
#include "Resource/ImageManager.h"

using namespace Rmi;

void CRmiIncoming::onMessage(const cdf::CWSContextPtr & context,
	const std::string & data,
	websocketpp::frame::opcode::value operCode)
{
	cdf::CSimpleSerializer __is(data);
	__is.decrypt();
	__is.startToRead();

	_rmiServer->__call(__is, context);
}

const std::string & CRmiIncoming::getImage(int imgId, std::string & imgType)
{
	static std::string emptyImg = "";

	WebServerApp::CImagePtr imgPtr = WebServerApp::CImageManager::instance()->findImage(imgId);
	if (NULL != imgPtr)
	{
		const std::string & fileName = imgPtr->getTUserImg().imgPath;
		std::string::size_type dotFound = fileName.find_last_of('.');
		if (dotFound != std::string::npos)
		{
			imgType = fileName.substr(dotFound + 1);
		}
		else
		{
			imgType = "jpg";
		}
		return imgPtr->getImgBin();
	}

	return emptyImg;
}

void CRmiIncoming::setRmiServer(const CRmiServerPtr & rmiServer)
{
	_rmiServer = rmiServer;
}
