module("MainGame.Resource.CN.config" );

local t_struct_config=
{
 {   id = 1,   name = "SeqInt",   type = 2,   fields = "int",   descr = "" }, 
 {   id = 2,   name = "SeqString",   type = 2,   fields = "string",   descr = "" }, 
 {   id = 3,   name = "SeqDate",   type = 2,   fields = "date",   descr = "" }, 
 {   id = 4,   name = "SeqBool",   type = 2,   fields = "bool",   descr = "" }, 
 {   id = 5,   name = "SeqByte",   type = 2,   fields = "byte",   descr = "" }, 
 {   id = 6,   name = "SeqShort",   type = 2,   fields = "short",   descr = "" }, 
 {   id = 7,   name = "SeqDouble",   type = 2,   fields = "double",   descr = "" }, 
 {   id = 8,   name = "SeqLong",   type = 2,   fields = "long",   descr = "" }, 
 {   id = 9,   name = "SeqImage",   type = 2,   fields = "image",   descr = "" }, 
 {   id = 100,   name = "SLoginReturn",   type = 1,   fields = "userId:int#nickname:string#avatar:image#avatarImgId:int#sessionKey:string",   descr = "" }, 
 {   id = 101,   name = "SPost",   type = 1,   fields = "postId:int#title:string#content:string#authorUserId:int#authorAccount:string#authorNickname:string#authorAvatarImgId:int#imgIdList:SeqInt#postDt:date#likes:int#dislikes:int#comments:int",   descr = "" }, 
 {   id = 102,   name = "SeqPost",   type = 2,   fields = "SPost",   descr = "" }, 
 {   id = 103,   name = "SComment",   type = 1,   fields = "userId:int#nickname:string#content:string#commentDt:date",   descr = "" }, 
 {   id = 104,   name = "SeqComment",   type = 2,   fields = "SComment",   descr = "" }
}
return t_struct_config
