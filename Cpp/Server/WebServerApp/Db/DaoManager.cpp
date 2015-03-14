#include "DaoManager.h"

using namespace WebServerApp;

CDaoManager * CDaoManager::instance()
{
	static CDaoManager _inst;

	return &_inst;
}

CDaoManager::CDaoManager()
{
	_userDao = new ::Dao::Impl::CUserDaoImpl();
	_userCommentDao = new ::Dao::Impl::CUserCommentDaoImpl();
	_userImgDao = new ::Dao::Impl::CUserImgDaoImpl();
	_userPostDao = new ::Dao::Impl::CUserPostDaoImpl();
}

CDaoManager::~CDaoManager()
{

}
