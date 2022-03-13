/*************************************************************************
    > File Name: firstlibevent.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月19日 星期日 00时05分08秒
 ************************************************************************/

#include<iostream>
#include<event2/event.h>
#include<event2/listener.h>
#include<event2/bufferevent.h>
#include<string.h> //memset()
#include <stdio.h>
using namespace std;

/**
在even_base的基础上使用bufferevent.
思路：
1. 创建libevent上线文：event_base_new；
2. 创建监听(socket创建、端口绑定、backlog、回调函数)：evconnlistener_new_bind；
=> evconnlistener_new_bind里的回调函数创建的客户端通信socket连接里使用bufferevent进行读、写监听.
3. 时间分发处理：event_base_dispatch();
4. evconnlistener清理;
5. event_base清理;
*/
#include <string>
static string recvStr = "";
static string recvCount = "";
static string sendCount = "";

#define SERV_PORT 8001
//错误、超时、断开连接时会通知.
void event_cb(bufferevent* bev, short events, void* arg){
  cout << "[E]" << endl;
  //读取超时时间发生，数据读取停止
  if(events & BEV_EVENT_TIMEOUT && events & BEV_EVENT_READING){
    cout << "BEV_EVENT_TIMEOUT- BEV_EVENT_READING" << endl;
    //读取缓冲区数据，防止因为水位而少量数据在缓冲中没有读取出来.
    FILE* fp = (FILE*)arg;
    char data[1024] = {0};
    int len = fread(data, 1, sizeof(data)-1, fp); //1:表示
    cout << recvStr << endl;
    cout << "recvCount="<< recvCount << "sendCount=" << sendCount<< endl;;
    //超时后重新让它可读.
    bufferevent_enable(bev, EV_READ);
    //超时后清理掉
    //如果超时就释放bev，防止连接长期占用资源.
    bufferevent_free(bev);
    return;
  } else if (events & BEV_EVENT_EOF) { //服务端的关闭事件
    cout << "BEV_EVENT_EOF"<< endl;
    bufferevent_free(bev);
  }else if (events & BEV_EVENT_ERROR) {
    cout << "BEV_EVENT_ERROR" << endl;
    //如果错误就释放bev，防止连接长期占用资源.
    bufferevent_free(bev);
    return;
  } else if (events & BEV_EVENT_CONNECTED) {
    cout << "BEV_EVENT_CONNECTED" << endl;
    //触发write
    bufferevent_trigger(bev, EV_WRITE, 0);
  } else {
    cout << "OTHERS" << endl;
  }
}
void write_cb(bufferevent* bev, void* arg){
  cout << "[W]" << endl;
  FILE* fp = (FILE*)arg;
  char data[1024] = {0};
  int len = fread(&data, 1, sizeof(data)-1, fp); //1:表示每次读取1个单位字节.
  if(len<=0){
    //读到文件结尾或者文件出错.
    fclose(fp);
    //立刻清理，可能会造成缓冲数据没有发送结束.所以这里不能清理.
    //bufferevent_free(bev);
    //不让继续写，禁掉写
    bufferevent_disable(bev, EV_WRITE);
    return ;
  } 
  sendCount += len;
  //写入buf
  bufferevent_write(bev, data, len);
}
void read_cb(bufferevent* bev, void* arg){
  cout << "[R]" << endl;
  char data[1024] = {0};
  //读取输入缓冲中的数据
  int len = bufferevent_read(bev, data, sizeof(data)-1);
  //cout << data << endl;
  cout << data << flush;

  if(len<=0) return;
  recvStr += data;
  recvCount += len;
  /**
  if(strstr(data, "quit")){
    cout << "quit"<<endl;
    bufferevent_free(bev);
  }
  */
  //发送数据. 写入到输出缓冲区
  bufferevent_write(bev, data, sizeof(data));
}

void listener_cb(struct evconnlistener * l, evutil_socket_t s, struct sockaddr * a, int socklen, void *arg) {
	cout << "listener_cb."<< endl;;
  event_base* base = (event_base*)arg;
  
  //bufferevent使用步骤：
  //1. 创建bufferevent上下文. BEV_OPT_CLOSE_ON_FREE清理bufferevent时关闭socket.
  bufferevent* bev = bufferevent_socket_new(base, s, BEV_OPT_CLOSE_ON_FREE);

  //2. 添加监听事件
  bufferevent_enable(bev, EV_READ|EV_WRITE);

  //3. 设置水位
  //读取水位
  bufferevent_setwatermark(bev, EV_READ,
      5, //低水位:只有发送过来的数据超过该字节数才会通知读事件回调读函数.0表示无限制，默认为0. 
      10 //低水位:当发送过来的数据超过该字节时会通知两次读事件来读该数据.0表示无限制，默认为0. 
      );
  //写水位
  bufferevent_setwatermark(bev, EV_WRITE,
      5, //低水位:缓冲数据低于5，写入回调被调用.0表示无限制，默认是0.
      0 //高水位无效.
      );

  //4. 超时时间: 超时的话会进入event_cb().
  timeval t1 = {3, 0};
  bufferevent_set_timeouts(bev, &t1, 0);

  //5. 设置回调函数
  bufferevent_setcb(bev, read_cb, write_cb, event_cb, base);
}

int main(){
	//创建libevent上下文，后面所有操作都是基于该上下文做
	event_base *base = event_base_new();
	if (base) {
		cout << "event_base_new success." << endl;
	}
/**
	sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));  //对sa清零. 可以不设置ip地址，表示可以连接到该主机的任意地址.
	sa.sin_family = AF_INET;
	sa.sin_port = htons(SERV_PORT);

	evconnlistener *ev = evconnlistener_new_bind(
			base,        //libevent的上下文
			listener_cb,  //当有新连接进来后执行该回调函数
			base,         //传给回调函数的参数arg
			LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, //LEV_OPT_* flags. 地址重用.evconnlistener关闭的同时关闭socket.
			10,          //listen()中设置的backlog. 连接的缓冲队列长度.如果该长度太长，当服务器处理不过来，则客户端需要等待很久；可以设置短点，客户端连接不上来后可以重连或者做其它事.
			(sockaddr*)&sa, //绑定的服务器端口和地址.
			sizeof(sa)
			);
      */


  //调用客户端代码
  //-1表示内部创建socket
  bufferevent* bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
  sockaddr_in sin;
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(8001);
  evutil_inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr.s_addr);

  //打开文件
  FILE* fp = fopen("test_buff_client.cpp", "rb"); //rb:二进制读.
  if (fp == NULL) {
    cout << "fopen file error!" << endl;
  } else {
    cout << "fopen file fp:" << fp << endl;
  }


  //设置回调函数
  bufferevent_setcb(bev, read_cb, write_cb, event_cb, fp); //将fp传进去.
  //设置权限:读写权限.
  bufferevent_enable(bev, EV_READ|EV_WRITE);
  //建立连接
  int re = bufferevent_socket_connect(bev, (sockaddr*)&sin, sizeof(sin));
  if(re == 0){
    cout << "connect" << endl;
  }



	event_base_dispatch(base);

  /**
	if(ev)
		evconnlistener_free(ev);
    */
	if(base)
		event_base_free(base);
  return 0;
}

