<?php
/**
### spl_autoload_register()
将__autoload换成loadprint函数。但是loadprint不会像__autoload自动触发，
这时spl_autoload_register()就起作用了，它告诉PHP碰到没有定义的类就执行loadprint()。 

区别：本质是一样，只是实现方式不同。
*/

function loadprint($class) {
    $file = $class .'.class.php';  
    if(is_file($file)) {  
        require_once($file);  
    } 
} 
 
spl_autoload_register( 'loadprint' ); 
 
$obj = new PrintIt();  //注意：这里类名要和require_once()进来的类名一致.
$obj->doPrint();
?>


<?php 
/**
####  __autoload()
**/
class PRINTIT { 
    function doPrint() {
    echo 'hello world';
    }
}
?> 
 
<?
function __autoload( $class ) {
    $file = $class . '.class.php';  
    if(is_file($file)){  
        require_once($file);  
    }
} 
$obj = new PRINTIT();
$obj->doPrint();
?>
