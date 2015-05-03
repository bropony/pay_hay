module("MainGame.Resource.CN.config" );

local t_error_code=
{
 {   errorCode = 10000,   errorName = "ExceptionCodeUnkown",   errorStr = "未知错误" }, 
 {   errorCode = 10001,   errorName = "Error_invalidOperation",   errorStr = "无效操作" }, 
 {   errorCode = 10002,   errorName = "ExceptionBadJsData",   errorStr = "数据出错" }, 
 {   errorCode = 10003,   errorName = "Error_nullUserPtr",   errorStr = "请先登录或注册" }, 
 {   errorCode = 10004,   errorName = "Error_SerializeError",   errorStr = "序列化错误" }, 
 {   errorCode = 10005,   errorName = "Error_NotRegisterdRmiCall",   errorStr = "未注册的远程方法调用" }, 
 {   errorCode = 20001,   errorName = "Error_accountOrPasswd",   errorStr = "账号或者密码错误" }, 
 {   errorCode = 20002,   errorName = "Error_accountExisted",   errorStr = "账号已存在" }, 
 {   errorCode = 20003,   errorName = "Error_nicknameUsed",   errorStr = "昵称已被使用" }, 
 {   errorCode = 20004,   errorName = "Error_userDataError",   errorStr = "用户数据有错，请重新登录" }, 
 {   errorCode = 20005,   errorName = "Error_accountTooShort",   errorStr = "账号长度必须不少于5个字符" }, 
 {   errorCode = 20006,   errorName = "Error_nicknameNeeded",   errorStr = "请设置昵称" }, 
 {   errorCode = 20007,   errorName = "Error_passwdNeeded",   errorStr = "请设置密码" }, 
 {   errorCode = 20010,   errorName = "Error_avatarImgToLarge",   errorStr = "头像图片太大" }, 
 {   errorCode = 20011,   errorName = "Error_saveAvatarImgError",   errorStr = "保存头像失败" }, 
 {   errorCode = 20015,   errorName = "Error_noSuchImg",   errorStr = "没有该图片" }, 
 {   errorCode = 20020,   errorName = "Error_postNotFound",   errorStr = "该帖子已经不存在" }, 
 {   errorCode = 20025,   errorName = "Error_imgNumInvalid",   errorStr = "图片数量必须在0到10之间" }, 
 {   errorCode = 20026,   errorName = "Error_allImgUploaded",   errorStr = "所有图片已经上传完毕" }, 
 {   errorCode = 20027,   errorName = "Error_postImgIndexError",   errorStr = "图片索引错误" }
}
return t_error_code
