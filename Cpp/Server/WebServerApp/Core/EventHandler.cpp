#include "framework/websocket/websocketserver.h"
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

void CEventHandler::onError(int errorCode, const std::string & errorMsg, int msgId, const cdf::CWSContextPtr & context)
{
    Json::Value jsError;
    jsError["event"] = "error";
    jsError["msg_id"] = msgId;
    jsError["what"] = errorMsg;
    jsError["code"] = errorCode;

    cdf::CWebsocketServer::instance()->sendData(context, jsError.toFastString());
}

