<?php
ini_set('default_socket_timeout', -1);
ini_set('display_errors', 1);


/**
 * implode()结果：
 * 1.如果数组为空；
 * 2.如果数组只有一个元素
 *
**/

function implodeTest(){
    $arr0 = array("apple", "orange");    
    var_dump(implode("|", $arr0));
    
    $arr1 = array("apple");    
    var_dump(implode("|", $arr1));

    $arr2 = array();    
    var_dump(implode("|", $arr2));
}

//implodeTest();



//empty($arr)  如果$arr没有元素，返回真假
//空数组、空字符串、null、0都返回true
function emptyTest(){
    $arr0 = array();
    $arr1 = "";
    $arr2 = null;
    $arr3 = 0;
    var_dump(empty($arr0));
    var_dump(empty($arr1));
    var_dump(empty($arr2));
    var_dump(empty($arr3));
}

//emptyTest();


//isset($arr)  如果$arr没有元素，返回真假
//空数组和空字符串都返回true
function issetTest(){
    $arr0 = array();
    $arr1 = "";
    $arr2 = null;
    $arr3 = 0;
    var_dump(isset($arr0)); //true
    var_dump(isset($arr1)); //true
    var_dump(isset($arr2)); //false
    var_dump(isset($arr3)); //true
}

//issetTest();


//foreach()  如果$arr没有元素，是否报错
function foreachTest(){
    $arr0 = array();
    foreach($arr0 as $k=>$v){
        var_dump($v);    
    }    
    echo "foreach里，arr没有元素也不影响程序正常运行.";
    $arr1 = '';
    foreach($arr1 as $k1=>$v1){
        var_dump($v1);    
    }    
    echo "foreach里可以是空数组，但必须是个数组，不能是其它类型的数据.";
}
//foreachTest();


//array => merge and +
function arrayMerge(){
    $arr0 = array("apple","orange","banana");
    $arr1 = array("yezi","orange","apple");
    echo "数字索引->array_merge():";
    var_dump(array_merge($arr0,$arr1));    
    echo "\n";
    $arr2 = array("red"=>"apple","o"=>"orange","green"=>"banana");
    $arr3 = array("red"=>"yezi","g"=>"orange","green"=>"apple");
    echo "字符串索引-> +:";
    var_dump(array_merge($arr2,$arr3));    
    echo "\n";
}


function arrayMulti(){
    $arr0 = array("apple","orange","banana");
    $arr1 = array("yezi","orange","apple");
    echo "数字索引->array_merge():";
    var_dump($arr0+$arr1);    
    echo "\n";
    $arr2 = array("red"=>"apple","o"=>"orange","green"=>"banana");
    $arr3 = array("red"=>"yezi","g"=>"orange","green"=>"apple");
    echo "字符串索引 +:";
    var_dump($arr2+$arr3);    
    echo "\n";
}
//echo "array_merge():数字索引数组merge则是追加；字符串索引数组merge，如果key相同则覆盖；
//      array + :数字索引数组相加,不管数字索引还是字符串索引都不覆盖\n .";

//arrayMerge();
//arrayMulti();


//php7与php5的区别
//如果php7在windows上这样操作会报错: [] operate not supported for string.
function arrdiff(){
    $arr['index'] = "";
    $arr['index'][] = "aa";
    var_dump($arr);    
}
//arrdiff();

//字符串的[]操作
function strindex(){
    $str = "abcdef";    
    echo $str[2];
}
//strindex();

//打印出2
//if(array()){echo 1;}else{echo 2;};

//unset($arr)
function unsetArr(){
    $arr = array("fruit"=>"apple",2=>10);    
    unset($arr);
    var_dump($arr); //输出NULL
}
//unsetArr();

function shift(){
    //$arr = array('apple'=>'fruit','tools'=>'phone');    
    //$arr = array(); // NULL
    $arr = ''; //warning.  param must be a array.
    $t = array_shift($arr);
    var_dump($t);
}
//shift();







