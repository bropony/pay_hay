#include "Dao/Base/UserPostDaoBase.h"
Dao::IUserPostDaoBase::IUserPostDaoBase()
{
}
Dao::IUserPostDaoBase::~IUserPostDaoBase()
{
}

const std::string Dao::IUserPostDaoBase::_tableName = "t_user_post";
const std::string Dao::IUserPostDaoBase::_postId = "post_id";
const std::string Dao::IUserPostDaoBase::_userId = "user_id";
const std::string Dao::IUserPostDaoBase::_title = "title";
const std::string Dao::IUserPostDaoBase::_content = "content";
const std::string Dao::IUserPostDaoBase::_imgList = "img_list";
const std::string Dao::IUserPostDaoBase::_nlike = "nlike";
const std::string Dao::IUserPostDaoBase::_ndislike = "ndislike";
const std::string Dao::IUserPostDaoBase::_ncomment = "ncomment";
const std::string Dao::IUserPostDaoBase::_postDt = "post_dt";