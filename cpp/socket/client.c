/*************************************************************************
    > File Name: client.c
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 二  3/10 00:08:34 2020
 ************************************************************************/
/**
desc: 客户端socket连接.
1. 创建客户端socket；
2. bind():可以不写，依赖“隐式创建”，即会生成随机的端口号；
3. connect():向服务端发起连接；
4. write():向服务端写数据；
5. read():从服务端读数据；
6. close():关闭连接。
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>  //socket.h头文件是在sys目录里
#include<arpa/inet.h>
#include<netinet/in.h> //in :internet
#include<string.h> //strlen()  memset()

#define SERVER_PORT 8000
#define SERVER_IP "127.0.0.1" 

int main(void) {
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr)); //对addr的内存块里的前n个字节初始化为0，防止后续使用的时候addr里有随机值脏数据.
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SERVER_PORT);
  addr.sin_addr.s_addr = inet_addr(SERVER_IP); //也可用inet_pton()
  int cres = connect(sfd, (struct sockaddr *)&addr, sizeof(addr)); //是把struct sockaddr_in转为struct sockaddr，别转反了.
  if (cres == -1) {
    perror("connect fail.\n");
  }

  while(1) { //能反复地从键盘读
    /**
    char input[20]; //如果这里用char* input;则会出错，原因是scanf要往开辟好的内存的里写出具.
    scanf("%s", input);
    //printf("s=%s\n",input); //如果不加\n，将看到的是没打印出来，但实际上是打印出来的数字因为没换行而从行首开始把输入的数字给覆盖了.
    */
    char buf[BUFSIZ];
    fgets(buf, sizeof(buf), stdin); // fgets是读取一行。键盘输入hello ---> fgets ---> fgets实际读到的是: "hello\n\0"
    int wres = write(sfd, buf, strlen(buf)); // 因为fgets实际读取到的字符串以\0结尾，所以可用strlen()函数计算字符串长度.
    if (wres == -1) {
      perror("write buf fail.\n");
    }
    int n= read(sfd, buf, sizeof(buf));
    if (n == -1){
      perror("read buf fail.\n");
    }
    //write(STDOUT_FILENO, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, n);
  }
  close(sfd);

  return 0;
}





