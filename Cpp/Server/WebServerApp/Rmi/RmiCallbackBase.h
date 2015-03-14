#ifndef __RMI_RMI_CALL_BACK_BASE_H__
#define __RMI_RMI_CALL_BACK_BASE_H__

#include "framework/websocket/websocketcontext.h"
#include "framework/serialize/simpleserializer.h"
#include "framework/websocket/websocketserver.h"

namespace Rmi
{
	class CRmiCallbackBase
		: public virtual cdf::CRefShared
	{
	public:
		CRmiCallbackBase(const cdf::CWSContextPtr & context, int msgId);
		const cdf::CWSContextPtr & getContext();
	protected:
		void __response(cdf::CSimpleSerializer & __os);

	protected:
		int _msgId;
		cdf::CWSContextPtr _context;
	};
	typedef cdf::CHandle<CRmiCallbackBase> CRmiCallbackBasePtr;
};

#endif