<?php
echo md5('867662021616627');
echo urldecode('http%3A%2F%2Fe.tf.360.cn%2Fb%2Fthird%2FUniqueID%3D%7BUniqueID%7D%26activetime%3D%7Bactivetime%7D%26OS%3D%7BOS%7D%26devicetype%3D%7Bdevicetype%7D%26imei_md5%3D%7Bimei_md5%7D%26IDFA%3D%7BIDFA%7D%26MAC_MD5%3D%7BMAC_MD5%7D%26convert_type%3D2%26UA%3D%26')."\n";

echo urlencode('http://sp1.tf.360.cn/b/third/UniqueID={UniqueID}&activetime={activetime}&OS={OS}&devicetype={devicetype}&imei_md5={imei_md5}&IDFA={IDFA}&MAC_MD5={MAC_MD5}&convert_type=2&UA=&');
echo "\n";
$a = array("zs"=>array("rpid"=>111));
echo urlencode(json_encode($a));
