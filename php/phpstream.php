<?php
//打开一个php的内存文件句柄
$fp=fopen('php://memory', 'rw');
//将字符串PHP写入文件
fwrite($fp,'PHP');
//将文件句柄$fp的指针指向0位置.【如果不指向0位置，则读取不到内容，因为当前文件句柄指向了文件末尾】
rewind($fp);
//读取文件
$a=fread($fp,1024);
//$a=stream_get_contents($fp);
var_dump($a);
//一旦文件句柄关闭，则无法再从输入输出流中读取到内容
fclose($fp);
