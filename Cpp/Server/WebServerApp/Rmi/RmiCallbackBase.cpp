#include "RmiCallbackBase.h"

Rmi::CRmiCallbackBase::CRmiCallbackBase(const cdf::CWSContextPtr & context, int msgId)
:_context(context)
, _msgId(msgId)
{

}

const cdf::CWSContextPtr & Rmi::CRmiCallbackBase::getContext()
{
	return _context;
}

void Rmi::CRmiCallbackBase::__response(cdf::CSimpleSerializer & __os)
{
	__os.encrypt();
	cdf::CWebsocketServer::instance()->sendData(_context, __os.getBuffer(), websocketpp::frame::opcode::value::BINARY);
}
