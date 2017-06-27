<?php
##################################
#  在实例中可以直接创建属性.
##################################

class MyClass{
    public $name;
    public function say(){
        echo "please say your name:".$this->name;    
        echo "please say your age:".$this->age;    
    }    
}

$p = new MyClass();
$p->name = "john";
$p->age = 19;
$p->say();

