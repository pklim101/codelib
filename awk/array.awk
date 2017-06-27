#!/bin/awk -f
##################
#   awk数组使用
##################
#
#@desc：awk里的多纬数组本质上是一个一位数组，只是通过SUBSEP(\034)连接后在逻辑上形成二维数组.
#       比如p["t","a"] = 1;就相当于是p["t\034a"] = 1
#使用方法：./array.awk test.data



BEGIN{
    arr["a","b","c"]=20
    p["t","a"] = 1;
    p["t","b"] = 2;
    p["t","c"] = 3;

}
{
    arr["a","b","c"]--;
    for(one in arr){   #这里的one相当于["a","b","c"]
        split(one,arr2,SUBSEP);
        print arr2[1],arr2[2],arr2[3],arr[one]
    }

    for(i in p){
        #print p[i]    
    }
    
    #以下方式错误.
    #for(i in p["t"]){
        #print i
        #print p["t"][i]    
    #}
}
