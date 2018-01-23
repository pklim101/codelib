<?php
/*
xdebug地址：https://github.com/xdebug/xdebug/tree/XDEBUG_2_5_5
安装方法：见上面地址介绍.
xdebug.so 是一个zend_extension扩展.
*/

//注意：如果refcount是1，那么is_ref永远是false.
$a = "hello";//创建了一个符号名：a 和一个新的变量容器zval[该容器包含类型string和值hello]

//xdebug_debug_zval('a');// 打印结果为：a: (refcount=1, is_ref=0)='hello'

$b = $a;
xdebug_debug_zval('a');// refcount=2，因为这个变量容器zval同时被a和b连接.
unset($b);
xdebug_debug_zval('a');// refcount=1


//符合类型array和object存储它们的属性到符号表里，且每个属性会创建一个对应的zval容器.
$a = array('meaning'=>'life', 'number'=> 92);
xdebug_debug_zval('a');
/* 打印结果为
a: (refcount=2, is_ref=0)=array (
    'meaning' => (refcount=1, is_ref=0)='life', 
    'number' => (refcount=0, is_ref=0)=92)
有三个zval容器：a, meaning, number.
*/

