#include "Core/MessageHandler.h"
#include "Core/EventCommon.h"
#include "Config/ErrorCodeManager.h"
#include "framework/json/value.h"

using namespace cg;
using namespace WebServerApp;

void CMassageHandler::onMessage(const cdf::CWSContextPtr & context,
    const std::string & data,
    websocketpp::frame::opcode::value operCode)
{
    if (operCode == websocketpp::frame::opcode::binary)
    {
        try
        {
            _eventHandler->onUploadImg(data, context);
        }
        catch (const cdf::CException & ex)
        {
            CEventHandler::onError(ex.code(), ex.what(), -1, context);
        }
        catch (...)
        {
            CEventHandler::onError(10000, "ExceptionCodeUnkown", -1, context);
        }

        return;
    }

    Json::Value js;
    try
    {
        js.parse(data);
    }
    catch(...)
    {
        CEventHandler::onError(10002, "ExceptionBadJsData", 0, context);
    }

    int msgId = js["msg_id"].asInt();
    std::string eventType = js["event"].asString();

    try
    {
        if (eventType == "login")
        {
            CLogin_callbackPtr cb = new CLogin_callback(msgId, "login", context);

            _eventHandler->login(
                JS_STRING(js, "account"), 
                JS_STRING(js, "passwd"), 
                JS_STRING(js, "deviceId"), 
                cb
            );
        }

        else if (eventType == "signup")
        {
            CSignup_callbackPtr cb = new CSignup_callback(msgId, "signup", context);

            _eventHandler->signup(
                JS_STRING(js, "account"), 
                JS_STRING(js, "nickname"), 
                JS_STRING(js, "passwd"), 
                JS_STRING(js, "deviceId"), 
                cb
            );
        }

        else if (eventType == "reconnect")
        {
            CReconnect_callbackPtr cb = new CReconnect_callback(msgId, "reconnect", context);

            _eventHandler->reconnect(
                JS_STRING(js, "account"), 
                JS_STRING(js, "sessionKey"), 
                cb
            );
        }

        else if (eventType == "startPost")
        {
            CStartPost_callbackPtr cb = new CStartPost_callback(msgId, "startPost", context);

            _eventHandler->startPost(
                JS_STRING(js, "title"), 
                JS_STRING(js, "content"), 
                JS_JSON(js, "imgNames"), 
                cb
            );
        }

        else if (eventType == "endPost")
        {
            CEndPost_callbackPtr cb = new CEndPost_callback(msgId, "endPost", context);

            _eventHandler->endPost(
                cb
            );
        }

        else if (eventType == "deletePost")
        {
            CDeletePost_callbackPtr cb = new CDeletePost_callback(msgId, "deletePost", context);

            _eventHandler->deletePost(
                JS_INT(js, "postId"), 
                cb
            );
        }

        else if (eventType == "getPostList")
        {
            CGetPostList_callbackPtr cb = new CGetPostList_callback(msgId, "getPostList", context);

            _eventHandler->getPostList(
                JS_INT(js, "userId"), 
                JS_INT(js, "lastPostId"), 
                JS_BOOL(js, "forNewPost"), 
                cb
            );
        }

        else if (eventType == "viewPost")
        {
            CViewPost_callbackPtr cb = new CViewPost_callback(msgId, "viewPost", context);

            _eventHandler->viewPost(
                JS_INT(js, "postId"), 
                cb
            );
        }

        else if (eventType == "commentPost")
        {
            CCommentPost_callbackPtr cb = new CCommentPost_callback(msgId, "commentPost", context);

            _eventHandler->commentPost(
                JS_INT(js, "postId"), 
                JS_STRING(js, "comment"), 
                cb
            );
        }

        else if (eventType == "likePost")
        {
            CLikePost_callbackPtr cb = new CLikePost_callback(msgId, "likePost", context);

            _eventHandler->likePost(
                JS_INT(js, "postId"), 
                cb
            );
        }

        else if (eventType == "dislikePost")
        {
            CDislikePost_callbackPtr cb = new CDislikePost_callback(msgId, "dislikePost", context);

            _eventHandler->dislikePost(
                JS_INT(js, "postId"), 
                cb
            );
        }

        else if (eventType == "test")
        {
            CTest_callbackPtr cb = new CTest_callback(msgId, "test", context);

            _eventHandler->test(
                JS_DATE(js, "testIn"), 
                cb
            );
        }

        else
        {
            CDF_LOG_TRACE("onMessage", "InvalidEventType: " << eventType);
            CErrorCodeManager::throwException("Error_invalidOperation");
        }
    }
    catch (const cdf::CException & ex)
    {
        CEventHandler::onError(ex.code(), ex.what(), msgId, context);
    }
    catch (...)
    {
        CEventHandler::onError(10000, "ExceptionCodeUnkown", msgId, context);
    }
}
