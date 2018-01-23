<?php
/**
 * @desc    proc_open — Execute a command and open file pointers for input/output.
 * @param   $cmd     要执行的命令.
 * @param   $pipes   被设置为索引数组，其中的元素是被执行程序（也就是执行的命令$cmd）创建的管道，这些管道对应着php这一端的文件指针.
 * @param   $descriptorspec  一个索引数组。 数组的键表示描述符，数组元素值表示 PHP 如何将这些描述符传送至子进程.
 */

$descriptorspec = array(
   0 => array("pipe", "r"),  // 标准输入，子进程从此管道中读取数据
   1 => array("pipe", "w"),  // 标准输出，子进程向此管道中写入数据
   2 => array("file", "/tmp/error-output.txt", "a") // 标准错误，写入到一个文件
);

$cwd = '/tmp';
$env = array('some_option' => 'aeiou');

$process = proc_open('php 1.php', $descriptorspec, $pipes, $cwd, $env); //这里会生成一个子进程 php 1.php

sleep(100);

if (is_resource($process)) {
    // $pipes 现在看起来是这样的：
    // 0 => 可以向子进程标准输入写入的句柄
    // 1 => 可以从子进程标准输出读取的句柄
    // 错误输出将被追加到文件 /tmp/error-output.txt

    fwrite($pipes[0], "TEST\n");
    fclose($pipes[0]);

    echo stream_get_contents($pipes[1]);
    fclose($pipes[1]);
    

    // 切记：在调用 proc_close 之前关闭所有的管道以避免死锁。
    $return_value = proc_close($process);

    echo "command returned $return_value\n";
}
?>
