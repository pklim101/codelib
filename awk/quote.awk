#!/bin/awk -f
#########################
#  引号使用
#########################
#
#@desc:
#       1.shell命令部分需要用双引号包含起来，
#       2.正则匹配等使用到字符串的部分，需要用单引号包含起来；或者用双引号的话对引号加转义符.
#





{
    "/bin/hostname |  egrep -o '(apple|orange|green)'"|getline fruit;            #仅仅使用单引号包含字符串.
    "date +%Y%m%d%H%M -d \"-1 mins\""|getline time                               #使用双引号包含字符串，但是加了转义符\.
    "/sbin/ifconfig eth1 |grep \"inet addr\"| cut -f 2 -d \":\"|cut -f 1 -d \" \""|getline addip;
}
