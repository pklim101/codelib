<?php
/**
#################################################################
# register_shutdown_function()中注册的函数总是在showdown后再执行.
#################################################################
输出:
End :log locale test.
Start:log locale test.
*/

function loglocale($start){
    error_log($start."log locale test.\n",3,"loglocale.log");
}

register_shutdown_function('loglocale','Start:');


error_log("End :log locale test.\n",3,"loglocale.log");



