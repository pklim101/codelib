#!/usr/bin/lua

local json = require("cjson")
--local tb = {"name":"tom","age":12} 
local tb = {} 
tb["name"] = "tom"
tb["age"]  = 12

local str = json.encode(tb)
print(str)
