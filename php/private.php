<?php
/**
 * @desc 不可以用当前类的实例来访问该类的private变量.
 *
**/

class A{
    private $name;    
}

$p = new A();
//$p->name = 'susan';
echo $p->name;
var_dump($p);
