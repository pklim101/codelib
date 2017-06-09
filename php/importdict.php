<?php
$c = require_once 'params.php';

if(!array_key_exists($argv[1],$c)){
   echo "该业务不存在!"; 
   exit;
}

function db($address, $username, $passwd, $dbname, $table){
    $mysqli= new mysqli($address,$username,$passwd, $dbname);
    if($mysqli->connect_errno){
        echo "Failed to connect to MySQL: ".$mysql->connect_error;    
    }
    $res = $mysqli->query("select * from mrp");
    while($row = $res->fetch_assoc()){
        var_dump($row);
    }
    if(!$stmt = $mysqli->prepare("INSERT INTO mobiledict (`dicttype`,`key`,`value`,`createtime`,`updatetime`,`reason`) values (?,?,?,?,?,?)")){
        echo "Prepare Failed: (".$mysqli->errno. ")".$mysqli->error;    
    }

    if(!$stmt->bind_param("isssss", $dicttype, $key, $value, $createtime, $updatetime, $reason)){
        echo "Binding parameters failed: (". $stmt->errno . ")". $stmt->error;    
    }


    if(!$stmt->execute()){
        echo "Execute failed: (". $stmt->errno . ")" . $stmt->error;    
    }
}


$p = db("localhost", "root", "admin", "dictmgr", "mrp");
print_r($p);
    


