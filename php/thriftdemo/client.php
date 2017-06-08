<?php
namespace Img;

error_reporting(E_ALL);

require_once 'lib/Thrift/ClassLoader/ThriftClassLoader.php';

use Thrift\ClassLoader\ThriftClassLoader;

$GEN_DIR = realpath(dirname(__FILE__)) . '/gen-php';
$loader = new ThriftClassLoader();
$loader->registerNamespace('Thrift', 'lib');
$loader->registerDefinition('Img', $GEN_DIR);
$loader->register();

use Thrift\Protocol\TBinaryProtocol;
use Thrift\Transport\TSocket;
use Thrift\Transport\THttpClient;
use Thrift\Transport\TBufferedTransport;
use Thrift\Exception\TException;

try {
    if(array_search('--http', $argv)) {
        $socket = new ThttpClient('127.0.0.1', 8000, '/server.py');    
    }else{
        $socket = new Tsocket('ad.app.server', 8080);    
    } 
    $transport = new TBufferedTransport($socket, 1024, 1024);
    $protocol  = new TBinaryProtocol($transport);
    $client    = new \Img\ImgInfoClient($protocol);
    $transport->open();
    
    $ret = $client->getimgInfo('BAAA你好');
    echo $ret;
    echo "<br /> \r\n";
    $transport->close();
} catch (TException $te) {
    print "TException: " . $te->getMessage() . "\n";    
}
