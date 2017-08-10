<?php
function test($a,$b,$c){
    $n = func_num_args();
    $arr = func_get_args();
    var_dump($n,$arr);
}

test(111,222,333);
/**
int(3)
array(3) {
  [0]=>
  int(111)
  [1]=>
  int(222)
  [2]=>
  int(333)
}
*/
?>
