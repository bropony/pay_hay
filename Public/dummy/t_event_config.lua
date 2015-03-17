module("MainGame.Resource.CN.config" );

local t_event_config=
{
 {   eventId = 1,   event = "login",   inParams = "account:string#passwd:string",   outParams = "userInfo:SLoginReturn" }, 
 {   eventId = 2,   event = "signup",   inParams = "account:string#passwd:string#nickname:string",   outParams = "userInfo:SLoginReturn" }, 
 {   eventId = 3,   event = "changeAvatar",   inParams = "sessionKey:string#avatar:image",   outParams = "" }, 
 {   eventId = 20,   event = "getPosts",   inParams = "lastPostId:int#forNew:bool#requestNum:int",   outParams = "postList:SeqPost" }, 
 {   eventId = 21,   event = "getImage",   inParams = "imgId:int",   outParams = "img:image#shortDesc:string" }, 
 {   eventId = 22,   event = "getMyPosts",   inParams = "sessionKey:string#lastPostId:int#forNew:bool",   outParams = "postList:SeqPost" }, 
 {   eventId = 30,   event = "startPost",   inParams = "sessionKey:string#title:string#content:string",   outParams = "" }, 
 {   eventId = 31,   event = "uploadPostImg",   inParams = "sessionKey:string#img:image#descrpt:string",   outParams = "imgId:int" }, 
 {   eventId = 32,   event = "endPost",   inParams = "sessionKey:string",   outParams = "postId:int" }, 
 {   eventId = 40,   event = "likePost",   inParams = "sessionKey:string#postId:int",   outParams = "" }, 
 {   eventId = 41,   event = "dislikePost",   inParams = "sessionKey:string#postId:int",   outParams = "" }, 
 {   eventId = 42,   event = "commentPost",   inParams = "sessionKey:string#postId:int#comments:string",   outParams = "" }
}
return t_event_config
