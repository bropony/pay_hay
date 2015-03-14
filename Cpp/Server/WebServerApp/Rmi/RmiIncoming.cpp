#include "RmiIncoming.h"

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

void CRmiIncoming::setRmiServer(const CRmiServerPtr & rmiServer)
{
	_rmiServer = rmiServer;
}
