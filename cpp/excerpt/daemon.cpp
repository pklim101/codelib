/*************************************************************************
    > File Name: daemon.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年07月06日 星期一 10时17分47秒
 ************************************************************************/

#include<iostream>
#include <unistd.h>
using namespace std;

/**
daemon()：让程序脱离终端在后台运行。
原理：调用daemon()后fork出子进程在后端运行。同时父进程退出。
*/

int main() {
  int pid = getpid();
  int ppid = getppid();
  printf("main pid:%d, ppid:%d\n", pid,ppid);
  sleep(1);
  daemon(1, 1);

  while (1) {
    int dpid = getpid();
    FILE* fd = fopen("a.log","a+");
    char buf[20];
    snprintf(buf, 20, "daemon:%d\n", dpid);
    cout << buf << endl;
    fwrite(buf, 1, 20, fd);
    fclose(fd);
    sleep(1);
  }
  return 0;
}


