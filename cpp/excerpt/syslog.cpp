/*************************************************************************
    > File Name: syslog.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2019年10月18日 星期五 15时54分56秒
 ************************************************************************/

#include<iostream>
#include <sys/syslog.h>
using namespace std;

int main(){
  syslog(LOG_LOCAL1|LOG_INFO,"what you what print in log %s", "hello");
  return 0;
}

