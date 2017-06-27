<?php
#############################
##  yii2 init()方法的思想
#############################
#
# @desc :因为控制器的基类需要__constuct()方法做一些初始化的工作（比如初始化模板引擎），
#        如果你在控制器里实现了__construct，你还需要在__construct里调用parent::__construct()就太麻烦了。
#        所以通常会在基类里定义一个空的init方法，并且在__construct里（通常是末尾）调用$this->init()，
#        这样开发的时候就只需要实现init方法.

class A{
    function __construct(){
        echo "this is class A counstruct.\n";    
        $this->init();
    }    
}

class B extends A{
    function init(){
        echo "this is class B init.\n";    
    }    
}

class C extends B{
    function init(){
        echo "this is class C init.\n";    
    }    
}

$p = new C();
