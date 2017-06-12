#!/bin/bash
####################
#     数组的使用
####################
#
#@desc 数组为一个列表，无key，用()包含，元素之间用空格分割，不支持二维数组.
#

arr=(
    "apple"
    "orange"
    "water"
)

#遍历这个数组
for i in ${arr[*]}
do
    echo $i
done
exit

echo ${arr[1]}  #获取数组某个元素，下标从0开始.
echo ${arr[*]}  #获取数组所有元素.
echo ${#arr[*]} #获取数组长度.



#遍历一个列表
for i in 1 2 3 
do
    echo $i
done

for FILE in $HOME/.bash*
do
    echo $FILE
done

for line in `cat ./dictlist.conf` 
do
    echo ${line[1]}
done
