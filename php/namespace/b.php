<?php
namespace p\a;

class B{
    function __construct(){
        echo "this is class B!";    
        
        $a = new A();
    }    
}

var_dump(new B());

