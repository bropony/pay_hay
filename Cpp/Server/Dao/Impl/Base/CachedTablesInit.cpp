#include "Dao/Impl/Base/CachedTablesInit.h"
#include "Dao/Impl/Base/UserCached.h"
#include "Dao/Impl/Base/UserCommentCached.h"
#include "Dao/Impl/Base/UserImgCached.h"
#include "Dao/Impl/Base/UserPostCached.h"
void Dao::Impl::initCachedTables()
{
    CUserCached::regist();
    CUserCommentCached::regist();
    CUserImgCached::regist();
    CUserPostCached::regist();
}