#ifndef __RMI_RIM_INCOMING_H__
#define __RMI_RIM_INCOMING_H__

#include "framework/websocket/websocketmessagehandler.h"
#include "Rmi/RmiServer.h"

namespace Rmi
{
	class CRmiIncoming
		: public virtual cdf::CWsMessageHandler
	{
	public:
		void onMessage(const cdf::CWSContextPtr & context,
			const std::string & data,
			websocketpp::frame::opcode::value operCode);

		virtual const std::string & getImage(int imgId, std::string & imgType);

		void setRmiServer(const CRmiServerPtr & rmiServer);

	private:
		CRmiServerPtr _rmiServer;
	};
	typedef cdf::CHandle<CRmiIncoming> CRmiIncomingPtr;
}

#endif