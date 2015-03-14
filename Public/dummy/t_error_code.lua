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
 {   errorCode = 20004,   errorName = "Error_userDataError",   errorStr = "用户数据有错，请重新登录" }
}
return t_error_code
