#!/bin/awk -f
####################
#  入门DEMO
####################
#
#@desc：如何写一个awk脚本文件，且如何运行这个awk脚本.
#用法：./demo.awk test.data 

#说明：
#   1.首行#!/bin/awk -f指定运行awk的解释器，-f：调用脚本,如：awk -f script.awk  file
#   2.格式：
#       BEGIN{code}
#       {
#           code; #两行代码之间用分号分割；
#           code;
#       }
#       END{code}
#

BEGIN{sum=0}
{
    if($1>20){
        print $1;sum+=$1
    }
    if($1~/21/){
        print "匹配输出"$0
    }
}
END{print sum}
