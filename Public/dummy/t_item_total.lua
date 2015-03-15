module("MainGame.Resource.CN.config" ,package.seeall);

local t =
{

}
local t_item_total = {}
local item_total_mt = { }
setmetatable( t_item_total, {__index = function(_, i) local rec = t[i] if rec ~= nil then setmetatable(rec,item_total_mt[ math.floor(i / 10000000) ]) return rec end end})

function t_item_total.iter( )return  function (t,k)local rk, rv if k then rk,rv = next(t,k)else rk,rv = next(t)end if rk then setmetatable(rv,item_total_mt[ math.floor(rk / 10000000) ]) end return rk,rv end, t end
return t_item_total
