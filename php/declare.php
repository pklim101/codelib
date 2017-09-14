 <?php
function profile()
{
    global $tmp;
    printf("Now tmp is %d.\n",$tmp);
}
   
register_tick_function("profile");

declare(ticks=3) {
                $tmp = 1;
                $tmp = 2;
                $tmp = 3;
                $tmp = 4;
                $tmp = 5;
                $tmp = 6;
                $tmp = 7;
                $tmp = 8;
    //unregister_tick_function("profile");
}

$tmp=0;
while(1){
    $tmp++;
    declare(ticks=1);
    
}
?>
