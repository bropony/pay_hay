#ifndef __WEBSERVERAPP_CORE_POST_UPLOADER_H__
#define __WEBSERVERAPP_CORE_POST_UPLOADER_H__

#include "Message/Public/CdlPublic.h"

namespace WebServerApp
{
	class CPostInst
	{
	public:
		cdf::CDateTime postDt;
		std::string title;
		std::string content;
		Message::Public::SeqInt msgIdList;
	};
	typedef std::map<int, CPostInst> MapPostInst;

	class CPostUploader
	{
	public:
		static CPostUploader * instance();
		void startPost(int userId, const std::string & title, const std::string & content);
		void addImg(int userId, const std::string & fileName, const std::string & shortDesc, const std::string & img);
		int endPost(int userId, cdf::CDateTime & postDt);
	private:
		CPostUploader(){}
		~CPostUploader(){}

	private:
		MapPostInst _mapPostInst;
	};
}

#endif