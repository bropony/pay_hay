module("MainGame.Resource.CN.config" );

local t_struct_config=
{
 {   id = 1,   name = "SeqShort",   type = 2,   fields = "short",   descr = "" }, 
 {   id = 2,   name = "SeqLong",   type = 2,   fields = "long",   descr = "" }, 
 {   id = 3,   name = "SeqInt",   type = 2,   fields = "int",   descr = "" }, 
 {   id = 4,   name = "SeqBool",   type = 2,   fields = "bool",   descr = "" }, 
 {   id = 5,   name = "SeqString",   type = 2,   fields = "string",   descr = "" }, 
 {   id = 6,   name = "STest",   type = 1,   fields = "s:SeqShort#l:SeqLong#i:SeqInt#b:SeqBool#ss:SeqString",   descr = "" }, 
 {   id = 7,   name = "SeqSeqInt",   type = 2,   fields = "SeqInt",   descr = "" }, 
 {   id = 8,   name = "SGoo",   type = 1,   fields = "st:STest#ilist:SeqSeqInt",   descr = "" }
}
return t_struct_config
