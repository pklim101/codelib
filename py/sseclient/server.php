<?php
header("Content-Type: text/event-stream");
header('Cache-Control: no-cache');


while(true){

  echo "data:".date("Y-m-d H:i:s")."\r\n\r\n";

  @ob_flush();@flush();

  sleep(1);

}
?>
