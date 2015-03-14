#ifndef __WEBSERVERAPP_DB_DAOMANAGER_H__
#define __WEBSERVERAPP_DB_DAOMANAGER_H__

#include "Dao/Impl/UserDaoImpl.h"
#include "Dao/Impl/UserCommentDaoImpl.h"
#include "Dao/Impl/UserImgDaoImpl.h"
#include "Dao/Impl/UserPostDaoImpl.h"

namespace WebServerApp
{
	class CDaoManager
	{
	public:
		static CDaoManager * instance();
		
		::Dao::IUserDao * getIUserDao(){ return _userDao; }
		::Dao::IUserCommentDao * getIUserCommentDao(){ return _userCommentDao; }
		::Dao::IUserImgDao * getIUserImgDao(){ return _userImgDao; }
		::Dao::IUserPostDao * getIUserPostDao(){ return _userPostDao; }

	private:
		CDaoManager();
		~CDaoManager();

	private:
		::Dao::IUserDao * _userDao;
		::Dao::IUserCommentDao * _userCommentDao;
		::Dao::IUserImgDao * _userImgDao;
		::Dao::IUserPostDao * _userPostDao;
	};
}

#endif