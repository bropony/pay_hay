#ifndef __WEBSERVERAPP_CORE_POST_UPLOADER_H__
#define __WEBSERVERAPP_CORE_POST_UPLOADER_H__

#include "Message/Public/CdlPublic.h"
#include "framework/json/value.h"

namespace WebServerApp
{
	class CPostInst
	{
	public:
		cdf::CDateTime postDt;
		std::string title;
		std::string content;
		Json::Value jsImages;
		unsigned imgIdex;
		Message::Public::SeqInt msgIdList;
	};
	typedef std::map<int, CPostInst> MapPostInst;

	class CPostUploader
	{
	public:
		static CPostUploader * instance();
		void startPost(int userId, const std::string & title, const std::string & content, const Json::Value & jsImages);
		void addImg(int userId, const std::string & img);
		int endPost(int userId, cdf::CDateTime & postDt);
	private:
		CPostUploader(){}
		~CPostUploader(){}

	private:
		MapPostInst _mapPostInst;
	};
}

#endif