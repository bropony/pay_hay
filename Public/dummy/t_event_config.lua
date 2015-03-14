module("MainGame.Resource.CN.config" );

local t_event_config=
{
 {   eventId = 12,   event = "test",   inParams = "dt:date",   outParams = "testOut:date" }, 
 {   eventId = 13,   event = "showError",   inParams = "dt:date",   outParams = "out:string" }, 
 {   eventId = 14,   event = "uploadImage",   inParams = "img:image",   outParams = "fileName:string" }, 
 {   eventId = 15,   event = "echo",   inParams = "input:STest",   outParams = "output:STest" }
}
return t_event_config
