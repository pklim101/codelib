/*************************************************************************
    > File Name: 1.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年07月01日 星期三 11时35分27秒
 ************************************************************************/
#include<iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
int main(){
  int fd1 = open("a.log",O_RDWR|O_APPEND);
  int fd2 = open("b.log",O_RDWR|O_APPEND);
  dup2(fd1, fd2); //把新的文件描述符指向旧的文件描述符指向的文件.
  close(fd1);
  write(fd1,"aaa", 3);
  write(fd2,"bbb", 3);
  cout << fd1 << endl;

  return 0;
}
