#ifndef __WEBSERVERAPP_CORE_EVENT_COMMON_H__
#define __WEBSERVERAPP_CORE_EVENT_COMMON_H__

#include <string>

#define JS_STR JS_STRING
#define JS_STRING(js, key) (js[key].isString() ? js[key].asString() : "")
#define JS_INT(js, key) (js[key].isInt() ? js[key].asInt() : 0)
#define JS_DOUBLE(js, key) (js[key].isDouble() ? js[key].asDouble() : 0.0)
#define JS_UINT(js, key) (js[key].isUint() ? js[key].asUInt() : 0)
#define JS_BOOL(js, key) (js[key].isBool() ? js[key].asBool() : false)
#define JS_JSON(js, key) (js[key])
#define JS_DATE(js, key) (js[key].isInt() ? cdf::CDateTime(js[key].asInt() * 1000) : cdf::CDateTime())

namespace WebServerApp
{
	namespace MsgId
	{
		const int imgMsgId = 100000;
	}

	namespace ImageType
	{
		enum IMAGETYPE
		{
			POST = 1,
			AVATAR = 2,
		};
	}

	namespace EventKey
	{
		const std::string event = "event";
		const std::string msgId = "msg_id";
	}

	namespace EventType
	{
		const std::string error = "error";
		const std::string login = "login";
		const std::string signup = "signup";
		const std::string reconnect = "reconnect";

		const std::string start_post = "start_post";
		const std::string end_post = "end_post";
		const std::string delete_post = "delete_post";
		const std::string upload_img = "upload_img";

		const std::string get_post_list = "get_post_list";
		const std::string view_post = "view_post";
		const std::string comment_post = "comment_post";
		const std::string like_post = "like_post";
		const std::string dislike_post = "dislike_post";
	};

	namespace ParameterKey
	{
		const std::string what = "what";
		const std::string code = "code";
		const std::string account = "account";
		const std::string passwd = "passwd";
		const std::string nickname = "nickname";
		const std::string deviceId = "device_id";
		const std::string sessionKey = "session_key";
		const std::string title = "title";
		const std::string content = "content";
		const std::string image = "image";
		const std::string postId = "post_id";
		const std::string firstPostId = "first_post_id";
		const std::string lastPostId = "last_post_id";
		const std::string forNewPost = "for_new_post";
		const std::string postIdList = "post_id_list";
		const std::string postDt = "post_dt";
		const std::string userId = "user_id";
		const std::string comment = "comment";
		const std::string filename = "filename";
		const std::string shortDesc = "short_desc";
		const std::string imgBinary = "img_binary";
	}
}

#endif