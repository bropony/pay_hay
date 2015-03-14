#include "framework/websocket/websocketserver.h"
#include "framework/util/endian.h"
#include "Core/EventHandler.h"

using namespace cg;

CLogin_callback::CLogin_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CLogin_callback::response(const std::string & sessionKey, const std::string & nickname, int userId)
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "login";
    __res["sessionKey"] = sessionKey;
    __res["nickname"] = nickname;
    __res["userId"] = userId;

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CLogin_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CSignup_callback::CSignup_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CSignup_callback::response(const std::string & sessionKey, int userId)
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "signup";
    __res["sessionKey"] = sessionKey;
    __res["userId"] = userId;

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CSignup_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CReconnect_callback::CReconnect_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CReconnect_callback::response(int res)
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "reconnect";
    __res["res"] = res;

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CReconnect_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CStartPost_callback::CStartPost_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CStartPost_callback::response()
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "startPost";

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CStartPost_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CEndPost_callback::CEndPost_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CEndPost_callback::response(int postId)
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "endPost";
    __res["postId"] = postId;

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CEndPost_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CDeletePost_callback::CDeletePost_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CDeletePost_callback::response()
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "deletePost";

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CDeletePost_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CGetPostList_callback::CGetPostList_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CGetPostList_callback::response(const Json::Value & res)
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "getPostList";
    __res["res"] = res;

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CGetPostList_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CViewPost_callback::CViewPost_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CViewPost_callback::response(const Json::Value & res)
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "viewPost";
    __res["res"] = res;

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CViewPost_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CCommentPost_callback::CCommentPost_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CCommentPost_callback::response()
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "commentPost";

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CCommentPost_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CLikePost_callback::CLikePost_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CLikePost_callback::response()
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "likePost";

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CLikePost_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CDislikePost_callback::CDislikePost_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CDislikePost_callback::response()
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "dislikePost";

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CDislikePost_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CTest_callback::CTest_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CTest_callback::response(const cdf::CDateTime & testOut)
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "test";
    __res["testOut"] = testOut.getTotalSecond();

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CTest_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


CGetImage_callback::CGetImage_callback(int msgId, const std::string & event, const cdf::CWSContextPtr & context)
    :_msgId(msgId), _event(event), _context(context)
{
}

void CGetImage_callback::response(const std::string & imge)
{
    Json::Value __res;
    __res["msg_id"] = _msgId;
    __res["event"] = "getImage";
    __res["imge"] = imge;

    cdf::CWebsocketServer::instance()->sendData(_context, __res.toFastString());
}

void CGetImage_callback::responseB(const std::string & data)
{
    std::string __res;
    __res.resize(4);
    int msgId = cdf::endian(_msgId);
    for (int i = 0; i < 4; i++){__res[i] = ((char*)(&msgId))[i];}
    __res += data;
    cdf::CWebsocketServer::instance()->sendData(_context, __res, websocketpp::frame::opcode::binary);
}


void CEventHandler::onError(int errorCode, const std::string & errorMsg, int msgId, const cdf::CWSContextPtr & context)
{
    Json::Value jsError;
    jsError["event"] = "error";
    jsError["msg_id"] = msgId;
    jsError["what"] = errorMsg;
    jsError["code"] = errorCode;

    cdf::CWebsocketServer::instance()->sendData(context, jsError.toFastString());
}

