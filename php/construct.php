<?php
/**
 *       构造方法可以被继承.
 * @desc 如果子类没有构造方法，则实例化子类的时候是执行父类的构造方法；
 *       如果子类有构造方法 ， 则实例化子类的时候会覆盖父类的构造方法；
 *       如果在子类中调用parent::__construct()，则实例化子类的时候，会父类和子类的构造方法都会被执行。
 *
 * $params $config 定义的父类构造方法的参数$config，在子类中不能直接传入，必须从子类从透传。
**/

class A{
    function __construct($config){
        echo "this is parent class A.";    
        var_dump($config);
    }    

    function say(){
        echo "the parent class A is say.....";    
    }
}

class B extends A{
    function __construct($a){
        parent::__construct($a);
        echo "this is son class B.";    
    }

    function run(){
        echo "this son class B is running.....";    
    }    
}

$p = new B(['a'=>1]);

