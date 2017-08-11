<?php
/**
####################################################
#  spl_autoload_register() 也能把被继承的类加载进来.
####################################################

*/
$n = 0;
function loadprint($class){
    global $n;
    $n++;
    $file = $class.'.class.php';
    /**
        这里最终会输出如何内容:         
        1:A.class.php
        2:PrintIt.class.php
    */
    echo $n.":".$file."\n";
    if(is_file($file)){
        include_once($file);
    }
}

spl_autoload_register('loadprint');

$a = new A();
$a->t();         //this is class A,it is saying t.
$a->doPrint();   //IT

