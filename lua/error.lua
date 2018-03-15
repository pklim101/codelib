#!/usr/bin/lua

--assert第一个参数为真，则可通过，否则报错且提示message.
--[[
local a = 3
print('assert-start.')
assert(type(a)=='number','a is no a number!')
print('assert-end.')
]]--

--[[
local function test(a,b)
    print("start")
    error("the line is wroing!")
    print("end"..a..b)
end
print('C')
test('A','B')
print('D')
]]--

--[[
语法：pcall( f , arg1,···)
返回值：


    函数执行状态 (boolean)

        没有错误返回 true

        有错误返回 false

    发生错误返回错误信息，否则返回函数调用返回值
]]--
--pcall 指的是 protected call 类似其它语言里的 try-catch, 使用pcall 调用函数，如果函数 f 中发生了错误， 它并不会抛出一个错误，而是返回错误的状态, 为被执行函数提供一个保护模式，保证程序不会意外终止
--如果在错误发生时，我们不希望代码停止运行，而是做一些紧急措施，那么，可以使用pcall捕获错误。
--使用pcall调用test函数，如果test不报错，则pcall返回ture，否则，返回false。
--pcall除了会返回true或者false外，还能返回函数的错误信息
--[[
function test()
    print(a[1]);
end
local status, err = pcall(test);
if status then
    print("正常，呵呵");
else
    print("哎，函数出错了，我正在帮你处理，放心吧，等我睡醒就...不是，等你睡醒就没事了~");
    print(err);
end

function square(a)
  return a * "a"
end

local status, retval = pcall(square,10);

print ("Status: ", status)        -- 打印 "false"
print ("Return Value: ", retval)  -- 打印 Return Value:   ./error.lua:52: attempt to perform arithmetic on a string value

]]--


--[[
语法：xpcall (f, msgh [, arg1, ···])
xpcall 类似 pcall xpcall接受两个参数：调用函数、错误处理函数
]]--
--xpcall：可定制错误输出函数。
function myfunction (a)
    print(a)
    return a
end

function myerrorhandler( err )
    print( "ERROR:", err )
end
status = xpcall( myfunction, myerrorhandler ,3)  -- 这里能参数3吗？
print( status)
------------------stdout:
--ERROR: test2.lua:2: attempt to perform arithmetic on global 'n' (a nil value)
--false

