<?php
function diff(){
    $a1=array("a"=>"red","b"=>"green","c"=>"blue","d"=>"yellow");
    $a2=array("e"=>"red","f"=>"black","g"=>"purple");
    $a3=array("a"=>"red","b"=>"black","h"=>"yellow");

    $result=array_diff($a1,$a2,$a3);
    print_r($result);
}
//diff();

/**
 * 第2~n个数组【这些数组对第一个数组并列&&求交集】与第一个数组进行键名对比；
 * 如果键名相同，则返回第一个数组里的键值对作为元素的数组，
 */
function intersect(){
    $a1=array("a"=>"red","b"=>"green","c"=>"blue");
    $a2=array("a"=>"red","c"=>"blue2","d"=>"pink");
    $a3=array("d"=>"red3","c"=>"blue2","d"=>"pink"); //虽然第一个和第二个数组有"a"=>"red"这个交集，但是第一个数组与第三个数组没有这个交集，所以这个元素不是最后返回的结果.

    $result=array_intersect_key($a1,$a2,$a3);
    print_r($result);    
}
intersect();
?>
