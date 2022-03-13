#########################################################################
# File Name: start.sh
# Author: tony
# mail: tony@z.com
# Created Time: 2020年06月19日 星期五 18时23分43秒
#########################################################################
#!/bin/bash


LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/libo-ps/test/practice/project/fcgi2-master/mytest/libs/
export LD_LIBRARY_PATH
gcc -L./libs -lfcgi test_cgi.c 
