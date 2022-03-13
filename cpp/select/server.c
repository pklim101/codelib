/*************************************************************************
    > File Name: server.c
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 三  3/11 14:49:00 2020
 ************************************************************************/

/**
select:实现核心思想：把监听连接的事情交给内核做，让内核监听连接.
accept()：select实现的情况下，accept()不会阻塞，因为是先有了连接过来(由内核select通知)再调用的accept().

select:优点：将连接监听交给内核select去做，而不需要服务器应用来做，提升了并发性能.
select:缺点:
1. 监听的最大fd是1024，如果要突破，则需要修改内核select； 而poll可突破该限制，限制对应ulimit -a；/proc/sys/fs/file-max
2. 监听的fd是传入传出参数，且读、写、异常事件都是分离的，处理很麻烦； 而poll通过第一个参数可解决：各事件都合并到该参数;
3. 需要遍历0~maxfd这么多次描述符看什么事件发生了[可用数组clent[]解决]；而poll通过第一个参数解决了该数组的形式. 

使用select关键点：
1. listenfd: 监听server端的监听连接文件描述符listenfd(socket()创建的),有新连接过来了后可用accept()创建通信文件描述符connfd; 
2. connfd: 监听通信描述符connfd，看是否有数据发过来了(即是否可读);
3. client[]: 为了避免无用遍历(0~maxfd),将需要监听的fd放入数组client[maxi]中,之后只用遍历client[]数组即可.

实现步骤：
1. 创建监听连接的socket: lfd = socket();
2. 设置端口复用: setsockopt();
3. bind();
4. listen();
5. 将监听数组client[]初始化为1024个长度，且值都初始化为-1;
6. 将lfd添加到监听read_fds(即allset)中;
7. select()监听;
8. 遍历创建connfd : 如果step7中返回值>0,即有监听的事件发生，说明有客户端连接过来了，则调用accept()创建通信socket:connfd,且将该fd添加到client[]中;
9. 遍历client[] : FD_ISSET判断看有什么事件发生则处理什么事件.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<ctype.h>
#include<strings.h>

#define SERVER_PORT 8000
#define SERVER_IP "127.0.0.1"

int main(void) {
  int lfd = socket(AF_INET, SOCK_STREAM, 0);
  int opt = 1;
  setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in addr;
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SERVER_PORT);
  addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
  listen(lfd, 128); //默认128

  int client[FD_SETSIZE]; //自定义数组clinet[],防止遍历1024个文件描述符  FD_SETSIZE默认为1024.
  for (int i = 0; i < FD_SETSIZE; i++) {
    client[i] = -1; //全部读初始化-1,后面添加connfd的时候，寻找client[]里第一个为-1的元素，替换为需要遍历的connfd.
  }

  fd_set rset, allset; //rset是需要监听读事件的文件描述符集合，allset是暂存需要监听的fd集合，防止select传入传出参数read_fds覆盖了rset.
  FD_ZERO(&allset);
  FD_SET(lfd, &allset);  //将lfd放到监听集合中

  int nready;
  int maxi = -1;
  int maxfd = lfd;
  while(1) { //循环监听lfd和connfd.
    rset = allset; //暂存起来，防止select()传入传出参数被修改.
    nready = select(maxfd+1, &rset, NULL, NULL, NULL); //最后一个参数为NULL表示无限期等待. 此处阻塞，直到有nready个事件发生后返回. 注意:最大fd+1

    if (nready < 0) {
      continue;
    }
    for (int i = 0; i < nready; i++) {
      if (FD_ISSET(lfd, &rset)) {
        struct sockaddr_in client_addr;
        bzero(&client_addr, sizeof(client_addr));
        socklen_t client_addr_len = sizeof(client_addr); //如果不取sizeof,则无法读取到client_addr里客户端ip和端口.
        //因为有了select反馈来的连接后再通过accept创建connf，所以不会阻塞。而之前是没有连接过来而需要accept阻塞等待客户端连接过来.
        int connfd = accept(lfd, (struct sockaddr *)&client_addr, &client_addr_len); 
        char ipbuf[BUFSIZ];
        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ipbuf, sizeof(ipbuf));
        printf("client IP:%s, port:%d\n", ipbuf, ntohs(client_addr.sin_port));

        FD_SET(connfd, &allset);
        for (int j = 0; j < FD_SETSIZE; j++) {
          if (client[j] < 0) {
            client[j] =  connfd;
            maxi = j;
            break;
          }
        }
        if (connfd > maxfd) {
          maxfd = connfd;   //注意这里一定要保证交换到最大的文件描述符:maxfd.
        }
        if (i > maxi) {
          maxi = i;   //注意这里一定要保证maxi是client[]里最后一个元素的下标，保证下面的循环.
        }
      }
    }
    //上面获得内核事件反馈后，下面开始交互读写数据.
    for (int k = 0; k <= maxi; k++) {
      int sockfd = client[k];
      if (sockfd < 0) {
        continue;
      }
      if (FD_ISSET(sockfd, &rset)) {
        char buf[BUFSIZ];
        int n = read(sockfd, buf, sizeof(buf)); 
        if (n > 0) {
          //printf("read from connfd:%s\n", buf);  //这样竟然会附带一些乱码.
          write(STDOUT_FILENO, buf, n);
          for (int m = 0; m < n; m++) {
            buf[m] = toupper(buf[m]);
          }
          write(sockfd, buf, n); //注意这里不能是:sizeof(buf)，而应该是实际要写的字节数n，否则客户端读到的有很多脏数据.
          write(STDOUT_FILENO, buf, n);
        } else if (n == 0) {
          close(sockfd);
          FD_CLR(sockfd, &allset);
          client[k] = -1;
          printf("read end!");
          close(sockfd);
        } else {
          perror("read error!");
        }
      }
    }
  }
  close(lfd);
  
  return 0;
}

