#!/bin/bash

start=`date +%s`
for i in $(seq 0 1000000)
    do
        echo $i >> ~/1.txt
    done;
end=`date +%s`
((sum=end-start))
echo $start
echo $end
#((sum2=$sum/1000000))
echo "scale=2;$sum" | bc
