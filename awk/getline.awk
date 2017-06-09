#!/bin/awk -f
#################
#  getline用法
#################
#
#@desc:将管道符|前面的输出赋值给time
#用法：./getline.awk test.data
#


{
    "date +%Y%m%d%H%M -d \"-1 mins\""|getline time
    print time 
    ##注意：shell命令部分需要用双引号包含起来，正则匹配的字符串部分，需要用单引号包含起来.
    "hostname|egrep -o '(bjdt|shjc|dev|gzst|zzzc)'"|getline name   
    print name
}
