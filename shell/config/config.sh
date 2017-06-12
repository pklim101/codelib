#!/bin/bash
###################
#   如何做配置文件
###################
#
#@desc 该文件是主脚本文件，它加载配置文件dict.conf.
#      而配置文件采用数组 + 函数的形式配置类似二维数组一样的配置.
#

if [ ! -f "dict.conf" ]; then
    echo "error."
    exit 0  # or print error before exit
fi

#和source一样，执行文件导入shell.
. dict.conf

dicttype=$1 # $1获取参数不能直接使用.
function load_config()
{
    local table=$(echo $1 | tr A-Z.- a-z__)  # 特殊符号转换
    $table &>/dev/null  # 执行函数，将集群的配置赋值给对应的全局变量.把所有输出转向到/dev/null.
}

for i in ${searchdict[*]}
do
    load_config $i 
done

#可以输出配置文件dict.conf里的变量.
#echo $table
