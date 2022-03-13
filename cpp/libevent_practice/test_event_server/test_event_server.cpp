/*************************************************************************
    > File Name: firstlibevent.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月19日 星期日 00时05分08秒
 ************************************************************************/
#include <event2/event-config.h>
#include<iostream>
#include<event2/event.h>
#include<signal.h>
#include<string.h> //memset()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <sys/socket.h>
#include <error.h>
using namespace std;

/**
用libevent实现监听网络事件
思路：
1. 创建服务端socket并绑定地址和端口；
2. 创建event事件，设置希望监听的时间events:EV_READ；
3. 回调函数：用accept从监听连接socket sfd上接收一个连接，并且创建一个新的socket用于与客户端通信. 
*/

#define SERV_PORT 8001

//普通读写的方式
void listen_cb1(evutil_socket_t fd, short events, void* arg){
  char buf[1024] = {0};  //初始化为0后就不用在末尾追加\0，因为在字节中，每个char都表示的是asscii码，0表示\0，也就是结束符。初始化列表元素少于数组个数的时候，都用默认值初始化.
  sockaddr_in client_addr;
  //memset(&client_addr, 0, sizeof(client_addr));
  //读取连接信息
  socklen_t size = sizeof(client_addr);
  evutil_socket_t cfd = accept(fd, (sockaddr*)&client_addr, &size);
  //为什么如下在函数中强转(socklen_t*)却得到的ip是0.0.0.0呢？
  //evutil_socket_t cfd = accept(fd, (sockaddr*)&client_addr, (socklen_t*)(sizeof(client_addr)));  //注意：(socklen_t*)强转
  char ip[16] = {0};
  evutil_inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip)-1);
  cout << "client ip is :" << ip << endl;
  int len = read(cfd, buf, sizeof(buf)-1);
  if(len>0) {
    cout << "+" << endl;
    for(int i = 0; i < len; i++){
      buf[i] = toupper(buf[i]);
    }
    cout << buf << endl;
    write(cfd, buf, sizeof(buf));
  } else {
    cout << "." << endl;
    //this_thread::sleep_for(500ms);
    this_thread::sleep_for(std::chrono::seconds(1));
  }
}

//正常断开连接和超时会进入
void client_cb(evutil_socket_t fd, short events, void* arg){
  //下列一行是验证水平触发LT：只要有数据没有处理，就会一直进入(也就是轮询的时候会一直通知)
  //cout << "." << endl; return;
  //边缘触发ET：有数据时，只发一次.
  //判断超时
  if(events & EV_TIMEOUT) {
    //-1:出错, 0:关闭
    cout << "over...." << endl;
    event* ev = (event*)arg;
    event_free(ev);
    evutil_closesocket(fd);
  }

  char buf[1024] = {0};
  //默认是水平触发，如果不recv的话会一直进来.
  //ssize_t len = recv(fd, &buf, sizeof(buf)-1, 0);
  //下列一行验证边缘触发ET：每次只读3个字节，如果发过来的超过3个，则会一直在缓存里积累，越积越多.
  ssize_t len = recv(fd, &buf, 3, 0);
  if (len > 0) {
    send(fd, &buf, sizeof(buf)-1, 0);
  }
}

//用libevent的事件机制读写
void listen_cb(evutil_socket_t fd, short events, void* arg){
  sockaddr_in client_addr;
  socklen_t size = sizeof(client_addr);
  evutil_socket_t cfd = accept(fd, (sockaddr*)&client_addr, &size);
  char ip[16] = {0};
  evutil_inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip)-1);
  cout << "client ip is :" << ip << endl;

  //创建读事件
  event_base *base = (event_base*)arg;
  //event* ev = event_new(base, cfd, EV_READ|EV_PERSIST, client_cb, event_self_cbarg());
  //设置边缘触发ET：
  event* ev = event_new(base, cfd, EV_READ|EV_PERSIST|EV_ET, client_cb, event_self_cbarg());
  timeval t = {10,0};
  event_add(ev, &t);
}



int main(){
  //1. 创建libevent上下文;
  event_base* base  = event_base_new();
  if(!base){
    cerr << "event_base_new faild." << endl;
    return -1;
  }

  //2. 创建socket
  evutil_socket_t sock = socket(AF_INET, SOCK_STREAM, 0);

  //设置地址复用和非阻塞
  evutil_make_socket_nonblocking(sock);
  evutil_make_listen_socket_reuseable(sock);

  sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SERV_PORT);
  int b = ::bind(sock, (sockaddr*)&addr, sizeof(addr));
  if(b == -1) {
    cerr << "bind error:" << strerror(errno) << endl;
    return -1;
  }
  listen(sock, 10);

  //3. 创建监听网络EV_READ事件.
  //开始接受连接事件
  event* ev = event_new(base, sock, EV_READ|EV_PERSIST, listen_cb, base);//注意：监听读事件需要将EV_READ加进去. 
  if(!ev){
    cerr << "event_new failed." << endl;
    return -1; 
  }
  //4. 添加监听事件;
  if(event_add(ev, NULL) != 0){
    cerr << "add event_new failed." << endl;
  }


  //5. 进入事件主循环
  event_base_dispatch(base);
  evutil_closesocket(sock);
  event_free(ev);
  event_base_free(base);
  return 0;
}

