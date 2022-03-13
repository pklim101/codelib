/*************************************************************************
    > File Name: server.c
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  3/12 21:31:27 2020
 ************************************************************************/

//翻译：  poll->民意调查->轮训.

/**
epoll
核心思想：同select、poll一样，将事件发生监听交给内核(select/poll/epoll函数)c处理。

epoll优点：
1. 不受1024个文件描述符的限制；
2. select和poll只是知道了有几个事件发生了，但是不知道是哪几个事件发生了，所以要遍历所有文件句柄；而epoll能返回发生了哪些事件，直接处理即可。

epoll本质：
1. 是一颗红黑树，创建一个根节点(也是一个文件描述符，最后需要关闭)，每个节点就是一个监听的文件描述符。

epoll使用方法：
1. int epoll_create(int size);  创建一个epoll实例，返回一个红黑树根节点，也就是一个fd，参数size表示创建多少个节点，是个建议值；
2. int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event); 添加/删除/修改监听的文件描述符fd,参数event是一个结构体的指针，一般只用传events和data.fd即可；成功返回0，失败返回-1；
注意容易疑惑的点：参数event是在该参数添加节点的时候挂在节点上的数据，在epoll_wait()返回的事件的时候，epoll_wait()中传输参数events里就是这个节点上挂的数据.
3. int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout); 阻塞等待监听的事件发生.注意参数events是个数组的首地址,maxevents是这个数组的大小. 返回值：大于零表示有事件发生的文件描述符数量，等于零表示timeout超时，-1表示出错.
*/

/**
libevent介绍：
1. 基于epoll实现；
2. 监听到读事件后读取内容到节点的buf中，然后改变红黑树上的当前节点的读事件为写事件，来监听对方是否可写，解决了写阻塞问题.(因为滑动窗口，客户端的缓冲区可能已经满了，此时服务端无法继续向客户端写数据而阻塞);
3. 回调函数:利用epoll_event.data.ptr这个指针，传递一个结构体，该结构体包含:监听的fd，void* arg, void (*call_back)(void *arg).一旦事件满足，则回调该函数.
struct epoll_event里的*ptr说明：
该成员可以是一个结构体，作为回调函数，如：
struct Fdopt {
  int fd;
  void *args;
  void (*func)(void *args);
}
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include <sys/epoll.h>
#include<arpa/inet.h> //转为网络字节序：htons(8000) inet_addr("127.0.0.1")
#include<strings.h>
#include<ctype.h> //toupper()

#define SERVER_PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAX_OPEN 5000

int main(void) {
  int lfd = socket(AF_INET, SOCK_STREAM, 0); 
  int opt = 1;
  setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //端口复用.防止在2MSL期间内无法重启服务.

  struct sockaddr_in addr;
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SERVER_PORT);
  addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  bind(lfd, (struct sockaddr *)&addr, sizeof(addr));

  listen(lfd, 128);

  int epfd, connfd;
  int nready; //已经就绪的监听fd数量.
  struct epoll_event tempevt, evts[MAX_OPEN];
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  int sock;
  int n;
  char buf[BUFSIZ], str[BUFSIZ];

  epfd = epoll_create(MAX_OPEN);
  tempevt.events = EPOLLIN;
  tempevt.data.fd = lfd;
  epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &tempevt);

  while(1) {
    nready = epoll_wait(epfd, evts, MAX_OPEN, -1);
    if (nready < 0) {
      perror("epoll_wait error.\n");
    }
    for (int i = 0; i < nready; i++) {
      sock = evts[i].data.fd;
      if (sock == lfd) {
        bzero(&client_addr, sizeof(client_addr)); 
        connfd = accept(lfd, (struct sockaddr *)&client_addr, &client_addr_len);
        printf("received from %s at PORT %d\n",
                    inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)),
                    ntohs(client_addr.sin_port));
        tempevt.events = EPOLLIN;
        tempevt.data.fd = connfd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &tempevt);
      } else {
        n = read(sock, buf, sizeof(buf));
        if (n == 0) {           //当client关闭连接时，服务端也关闭对应连接，并且从监听红黑树上删除该节点.
          perror("read error.\n");
          tempevt.events = EPOLLIN;
          tempevt.data.fd = sock;
          close(sock);   //注意：我认为这里是需要关闭该sock的.
          epoll_ctl(epfd, EPOLL_CTL_DEL, sock, &tempevt);
        } else if (n > 0) {     //将读到的n字节回写到客户端.
          for (int j = 0; j < n; j++) {
            buf[j] = toupper(buf[j]);
          }
          write(sock, buf, n);
          write(STDOUT_FILENO, buf, n);
        }
      }
    }

  }
  close(lfd);
  close(epfd); //epoll的树根也是一个文件描述符，所以也要关闭.
  return 0;
}
