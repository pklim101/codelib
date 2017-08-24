<?php
class A{
    public $name;
    protected $age;
    static $status;
    
    function __construct($name,$age){
        $this->name = $name;
        $this->age = $age;
    }

    function say(){
        echo $this->name.$this->age;
    }
}

$p = new A('Amy',18);
$p->say();

$reflection = new ReflectionClass('A');
$q = $reflection->newInstance('Amy',18);
$q->say();
