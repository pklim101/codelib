/*************************************************************************
    > File Name: firstlibevent.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月19日 星期日 00时05分08秒
 ************************************************************************/

#include<iostream>
#include<event2/event.h>
#include<event2/http.h>
#include<event2/bufferevent.h>
#include<event2/buffer.h>
#include<event2/listener.h>
#include<string.h> //memset()
#include<string> //memset()
using namespace std;

/**
用libevent创建一个http客户端
思路：
*/

#define SERV_PORT 8001
//服务端处理完毕，发回response响应后调用该回调函数.(本质：客户端注册事件，监听READ，服务端回写的时候epoll轮训通知客户端，得到通知后调用该回调函数)
//如果请求失败(服务端没响应)，也会调用回调函数.
void http_client_cb(struct evhttp_request* req, void* arg){
  cout << "http_client_cb" << endl;
  event_base* base = (event_base*)arg;
  //服务端响应错误
  if (req == NULL) {
    int errcode = EVUTIL_SOCKET_ERROR();
    cout << "socket error:" << evutil_socket_error_to_string(errcode)<<endl;
    return;
  }

  //获取path
  const char* path = evhttp_request_get_uri(req); 
  cout << "request path is :" << path << endl;

  string filepath = ".";
  filepath += path;
  cout << "filepath="<<filepath<<endl;

  //获取返回的code: 200 404
  cout << "response :" << evhttp_request_get_response_code(req);
  cout << " " << evhttp_request_get_response_code_line(req)<<endl;

  FILE* fp = fopen("bbb.png","wb");
  if (!fp) {
    cout << "open file bbb.png failed."<<endl;
  }
  char buf[1024] = {0};
  evbuffer* inbuf = evhttp_request_get_input_buffer(req);
  for(;;){
    int len = evbuffer_remove(inbuf, buf, sizeof(buf)-1);
    if (len <= 0) break;
    buf[len] = 0;
    //cout << buf << flush;
    if(!fp){
      continue;
    }
    fwrite(buf, 1, len, fp);
  }
  if (fp) {
    fclose(fp);
  }
  cout << "check response" << endl;
  timeval t = {1,0};
  event_base_loopexit(base, &t); //中断循环.  如果不中断，则会一直请求等待.
}

int main(){
	//创建libevent上下文，后面所有操作都是基于该上下文做
	event_base *base = event_base_new();
	if (base) {
		cout << "event_base_new success." << endl;
	}

  //生成请求信息: GET请求
  string http_url = "http://127.0.0.1:8001/index.html?a=1&b=2";
  //http_url = "http://dspt11.adsys.lycc.qihoo.net:8001/basetool.png?a=1&b=2";
  //分析url地址：
  //uri:资源地址
  evhttp_uri * uri = evhttp_uri_parse(http_url.c_str());
  //scheme: http/https
  const char* scheme = evhttp_uri_get_scheme(uri);
  if (!scheme) {
    cerr << "scheme is null." << endl;
    return -1;
  }
  //host
  const char* host = evhttp_uri_get_host(uri);
  if (!host) {
    cerr << "host is null." << endl;
    return -1;
  }
  //port
  int port = evhttp_uri_get_port(uri);
  //path不会为null，但会为一个空串"\0"
  const char* path = evhttp_uri_get_path(uri);
  if (!path || strlen(path) == 0) {
    path = "/"; //const char*
  }
  cout << "scheme="<< scheme << endl;
  cout << "host="<< host<< endl;
  cout << "port="<< port<< endl;
  cout << "path="<< path<< endl;

  //获取uri中?后的部分
  const char* query = evhttp_uri_get_query(uri);
  if (query) {
    cout << "query is " << query << endl;
  } else {
    cout << "query is null " << endl;
  }

  //用bufferevent 连接http服务器
  //-1: 让其内部创建socket
  //BEV_OPT_CLOSE_ON_FREE: 释放bev的时候关闭socket连接.
  bufferevent* bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
  //建立连接信息
  evhttp_connection* evconn = evhttp_connection_base_bufferevent_new(base,NULL,bev,host,port);
  //创建请求.   http client 请求, 回调函数设置.
  evhttp_request* req = evhttp_request_new(http_client_cb, base);
  //设置请求的header消息报头信息
  evkeyvalq* out_headers = evhttp_request_get_output_headers(req);
  evhttp_add_header(out_headers, "Host", host);
  //发起请求：这一步才是真正开始发起请求，然后再回调函数中收到响应信息.
  /**
  evconn:连接信息:host+port，网络层
  req:请求信息:消息报头
    */
  evhttp_make_request(evconn, req, EVHTTP_REQ_GET, path);
  cout << "xxxxxxxxxxxxx" << endl;

	event_base_dispatch(base);
  //event_base_loop(base , EVLOOP_ONCE);

  cout << "yyyyyyyyyyyyyyyyxxxxxxxxxxxxx" << endl;
	if(base)
		event_base_free(base);
  return 0;
}

