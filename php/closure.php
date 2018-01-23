<?php

function foo($name){
    function inner_foo($inner_name){
        echo "name : ".$name."\n", "inner_name : ".$inner_name;
    }
    return 'inner_foo';

}

$f = foo("outer-tom");
var_dump($f);
$f("inner-tom");
