<?php
/**
#########################################
总而言之：如果抛出了异常，就必须捕获它.
为什么要引入异常：一种新的面向对象的错误处理方法.
#########################################
 */


/**
 * 一、异常基本使用.
function foo($num){
    if($num>1){
        throw new Exception("The num must be lower 1.\n");
    }
}
try{
    foo(2);
}
catch (Exception $e){       //捕获异常，并创建一个包含异常信息的对象 ($e)
    echo $e->getMessage();
    echo $e->getFile();
    echo $e->getLine();
}
*/

/** 
 * 二、自定义异常类.
    自定义异常类customException， 抛出异常的时候也得用throw new customException()
    同时自定义异常类也继承了Exception的属性和方法getLine,getFile,getMessage.
function foo($num){
    if($num>1){
        throw new customException("The num must be lower 1.\n");
    }
}
class customException extends Exception{
    function errorMessage(){
        $errorMsg = 'Error on line '.$this->getLine().' in '.$this->getFile().': <b>'.$this->getMessage().'</b> is not a valid E-Mail address';
        return $errorMsg;
    }
}

try{
    foo(2);
}
catch (customException $e){
    echo $e->errorMessage();
}
*/

/**
 * 三、多个异常:多次throw，多次catch.
class customException extends Exception{
    function errorMessage(){
        $errorMsg = 'Error on line '.$this->getLine().' in '.$this->getFile().': <b>'.$this->getMessage().'</b> is not a valid E-Mail address';
        return $errorMsg;
    }
}
$num = 2;
try{
    if($num>1){
        throw new Exception("The num must be lower 1.\n");
    }

    if($num==2){
        throw new customException("The num is not equal 2.\n");
    }
}
catch (Exception $e){
    echo $e->getMessage();
}
catch (customException $e){
    echo $e->errorMessage();
}
*/

/**
 * 四、设置顶层异常处理器：处理未被捕获的异常.
设置顶层异常处理器 （Top Level Exception Handler）
set_exception_handler() 函数可设置处理所有未捕获异常的用户定义函数。
*/
function myException($exception){  //这里参数$exception可以随意设置.
    echo "Exception:".$exception->getMessage();
}
set_exception_handler('myException');
throw new Exception('Uncaught exception occurred!');















