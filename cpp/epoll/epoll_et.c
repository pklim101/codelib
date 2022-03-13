/*************************************************************************
    > File Name: epoll_et.c
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年03月13日 星期五 10时02分33秒
 ************************************************************************/

/**
epoll有两种触发模式：(这里触发是指epoll_wait()有事件返回.)
epoll ET:只触发一次，如果缓冲区读取没读完，就不读.
epoll LT(default):只要缓冲区有数据，epoll就不停的触发，直至缓冲区数据读取完成.

ET模式使用场景：
1. 可以先读取前n个字节(这段消息的概述)，再决定是否要继续读剩下数据；
2. 决定要读取n个字段，但是发过来的数据不足n个的时候，发生阻塞了,这个时候epoll_wail()也无法监听.

epoll不仅能监听指向伪文件socket的fd，还可以监听管道fd、文件fd.

使用ET/LT的demo步骤：
1. 创建管道，创建父子进程，父进程关闭读，进程关闭写;
2. 父进程中组合两组数据一次性写入写缓冲区;
3. 子进程设置epoll为ET/LT模式,然后监听触发epoll_wait(),看输出结果能证明ET/LT模式.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //pipe(), fork(), sleep()
#include<sys/epoll.h>

#define MAXLINE 10
#define MAX_OPEN 500

int main(void) {
  int epfd;
  int nready; //返回触发事件的个数.
  int n; //读取到的字节数.
  int pfd[2];//用于创建管道,两个元素分别表示读fd[0]/写fd[1]缓冲区.
  pid_t pid;
  char buf[MAXLINE], ch = 'a';

  pipe(pfd); //unistd.h中,man 2 pipe.
  pid = fork();

  if (pid == 0) {
    close(pfd[0]);
    while(1){
      int i;
      for (i = 0; i < MAXLINE/2; i++) { //如果i在for中声明，则作用域只在for循环内.
        buf[i] = ch;
      }
      buf[i-1] = '\n';
      ch++;
      for (; i < MAXLINE; i++) {  //i从5开始.
        buf[i] = ch;
      }
      ch++;
      buf[i-1] = '\n';
      write(pfd[1], buf, MAXLINE);
      sleep(5);
    }
    close(pfd[1]); //注意：父进程结束前需要关闭对应的fd.
  } else if (pid > 0) {
    close(pfd[1]);
    epfd = epoll_create(MAX_OPEN);
    struct epoll_event tmpevt, evts[MAX_OPEN];
    //tmpevt.events = EPOLLIN;
    tmpevt.events = EPOLLIN | EPOLLET;
    tmpevt.data.fd = pfd[0];
    epoll_ctl(epfd, EPOLL_CTL_ADD, pfd[0], &tmpevt);
    while(1) {
      nready = epoll_wait(epfd, evts, MAX_OPEN, -1); //注意：水平触发模式下，只有缓冲区还有数据没读完，该函数就会触发.
      if (nready < 0) {
        continue; 
      }
      if (evts[0].data.fd == pfd[0]) {
        n = read(pfd[0], buf, MAXLINE/2);
        write(STDOUT_FILENO, buf, MAXLINE/2);
        printf("stdout=%d\n",evts[0].data.fd);
      }
    }
    close(pfd[0]);
    close(epfd);
  }
  return 0;
}

