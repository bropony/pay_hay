#include "Dao/Base/UserCommentDaoBase.h"
Dao::IUserCommentDaoBase::IUserCommentDaoBase()
{
}
Dao::IUserCommentDaoBase::~IUserCommentDaoBase()
{
}

const std::string Dao::IUserCommentDaoBase::_tableName = "t_user_comment";
const std::string Dao::IUserCommentDaoBase::_commentId = "comment_id";
const std::string Dao::IUserCommentDaoBase::_postId = "post_id";
const std::string Dao::IUserCommentDaoBase::_fromUserId = "from_user_id";
const std::string Dao::IUserCommentDaoBase::_fromNickname = "from_nickname";
const std::string Dao::IUserCommentDaoBase::_content = "content";
const std::string Dao::IUserCommentDaoBase::_commentDt = "comment_dt";