/*************************************************************************
    > File Name: server.c
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 一  3/ 9 22:58:22 2020
 ************************************************************************/
/**
socket本质：
1. socket是伪文件；
2. socket必须是成对出现；
3. bind的是IP+PORT，通过IP+PORT找到对方socket；
4. 一个fd对应两个buffer(读buffer和写buffer,实现双向全双工):socket是在内核实现的，两个buffer也是内核buffer;
   读写都是通过这个fd实现。

  */

/**
desc:创建socket服务端
1. 创建socket；
2. bind:绑定本机ip+port；
3. listen:用来设置监听连接上限数，也就是同时允许多少个客户端与服务端建立连接(本质上是：处于三次握手过程中的连接数)。
4. 【重点】accept:阻塞从socket上接收一个连接，并且创建一个新的socket用于同客户端通信；与客户端建立连接，三次握手.
5. read:从客户端读数据；
6. 处理请求；
7. write:回写数据到客户端；
8. close():关闭连接。

可用nc(net connect)命令当做客户端测试：
nc 127.0.0.1 8000

*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //该头文件包含sys/types.h
#include<sys/socket.h>
#include<arpa/inet.h> //包含struct sockaddr_in结构体.
#include<netinet/in.h>
#include<ctype.h> //包含toupper()函数.
#include<string.h>
#include<strings.h> //包含bzero()

#define SERVER_PORT 8000

int main(void) {
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  int opt = 1;
  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //端口复用
  //man 7 ip 查询sockaddr_in的结构.
  //struct sockaddr_in {
  //   sa_family_t    sin_family; /* address family: AF_INET */
  //   in_port_t      sin_port;   /* port in network byte order */
  //   struct in_addr sin_addr;   /* internet address */
  //};

  ///* Internet address. */ //struct in_addr {
  //   uint32_t       s_addr;     /* address in network byte order */
  //};
  
  struct sockaddr_in addr;
  bzero(&addr, sizeof(addr)); //同memset()功能相似，只是bzero就是清0功能.
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SERVER_PORT);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //htonl(INADDR_ANY), INADDR_ANY：系统生成本地任意有效IP
  int bres = bind(sfd, (struct sockaddr *)&addr, sizeof(addr));  
  if (bres == -1) {
    perror("bind fail.\n"); //bind fail.: Address already in use => 2MSL时间存在
  }

  int lres = listen(sfd, 128);
  if (lres == -1) {
    perror("listen setting fail.\n");
  }

  struct sockaddr_in client_addr; //是传出参数
  socklen_t socklen = sizeof(client_addr); //是传入传出参数.传入：在函数内读一次，传出：在函数内改一次. 作用：指定容器addr在传入前/传入后的大小.
  int cfd;
  cfd = accept(sfd, (struct sockaddr *) &client_addr, &socklen); //别忘了加struct
  if (cfd == -1) {
    perror("accept fail.\n");
  }
  char buf_client[BUFSIZ];
  inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, buf_client, sizeof(buf_client));
  printf("client ip:%s, port:%d\n",buf_client, ntohs(client_addr.sin_port));

  char rbuf[BUFSIZ]; //char rbuf[BUFSIZ]   BUFSIZ:系统内嵌宏，用于缓存大小.
  while(1) { //循环和客户端进行交互.
    int n = read(cfd, rbuf, sizeof(rbuf)); //返回的n是表示读到的字节数.
    printf("%s, length=%lu\n", rbuf, strlen(rbuf)); //这里rbuf不用解引用
    if(n > 0) {
      //for (int i = 0; i < sizeof(rbuf); i++) { //虽然数据读到rbuf中了，但是这里不应该用sizeof(rbuf)，而应该用读到的字节数n. 疑问：实际上sizeof(rbuf)==n.
      for (int i = 0; i < n; i++) {
        rbuf[i] = toupper(rbuf[i]);//toupper()需要ctype.h. toupper(int c):把char型向上取整，取成int型了.
      }
      //int ww = write(cfd, rbuf, sizeof(rbuf));  //回写的时候也应该是有多少字符，就传多少n.
      int ww = write(cfd, rbuf, n); 
    }
  }
  close(cfd);
  close(sfd); 

  return 0;
}
