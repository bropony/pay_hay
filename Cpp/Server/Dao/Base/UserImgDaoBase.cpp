#include "Dao/Base/UserImgDaoBase.h"
Dao::IUserImgDaoBase::IUserImgDaoBase()
{
}
Dao::IUserImgDaoBase::~IUserImgDaoBase()
{
}

const std::string Dao::IUserImgDaoBase::_tableName = "t_user_img";
const std::string Dao::IUserImgDaoBase::_imgId = "img_id";
const std::string Dao::IUserImgDaoBase::_imgPath = "img_path";
const std::string Dao::IUserImgDaoBase::_shortDesc = "short_desc";