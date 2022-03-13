/*************************************************************************
    > File Name: firstlibevent.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月19日 星期日 00时05分08秒
 ************************************************************************/
#include <event2/event-config.h>
#include<iostream>
#include<event2/event.h>
#include<event2/http.h>
#include<event2/keyvalq_struct.h>
#include<event2/buffer.h>
#include<signal.h>
#include<string.h> //memset()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <sys/socket.h>
#include <error.h>
#include <string>
using namespace std;

/**
用libevent实现http服务器
思路：
*/

#define SERV_PORT 8001
#define WEB_ROOT "."

void http_cb(struct evhttp_request* request, void* arg){
  cout << "http_cb." << endl;
  //1. 获取浏览器的请求信息
  const char* uri = evhttp_request_get_uri(request);
  cout << uri << endl;
  string cmdtype;
  switch(evhttp_request_get_command(request)) {
    case EVHTTP_REQ_GET:
      cmdtype = "GET";
      break;
    case EVHTTP_REQ_POST:
      cmdtype = "POST";
      break;
  }
  cout << cmdtype << endl;

  //消息报头
  evkeyvalq* headers = evhttp_request_get_input_headers(request);
  cout << "headers===========" << endl;
  for (evkeyval *p = headers->tqh_first; p!=NULL; p = p->next.tqe_next) {
    cout << p->key << ":" << p->value << endl;
  }

  //获取请求正文:<event2/buffer.h>
  evbuffer* inbuf = evhttp_request_get_input_buffer(request);
  char buf[1024] = {0};
  cout << "==========input data=======" << endl;
  while(evbuffer_get_length(inbuf)) {
    int n = evbuffer_remove(inbuf, buf, sizeof(buf)-1); //每次从evbuffer里读取n个字节.
    if (n>0) {
      buf[n] = '\0';
      cout << buf << endl;
    }
  }

  //2. 回复浏览器
  //状态行 消息报头 响应正文

  string filepath = WEB_ROOT;
  if(strcmp(uri,"/") == 0){
    filepath += "/index.html";
  } else {
    filepath += uri;
  }
  //消息报头
  evkeyvalq* outhead = evhttp_request_get_output_headers(request);
  //获取文件后缀： ./root/index.html
  int pos = filepath.rfind(".");
  string suffix = filepath.substr(pos+1, filepath.size()-(pos+1));
  if(suffix == "jpg" || suffix == "gif" || suffix == "png") {
    string tmp = "image/" + suffix;
    evhttp_add_header(outhead, "Content-Type", tmp.c_str());
  } else if (suffix == "zip") {
    evhttp_add_header(outhead, "Content-Type", "application/zip");
  } else if (suffix == "html") {
    //evhttp_add_header(outhead, "Content-Type", "text/html");
    evhttp_add_header(outhead, "Content-Type", "text/html;charset=UTF8");
  } else if (suffix == "css"){
    evhttp_add_header(outhead, "Content-Type", "text/css");
  }
  //sleep(100);
 // while(1){

 // }
  cout << filepath << endl;
  FILE* fp = fopen(filepath.c_str(), "rb");
  if (!fp) {
    evhttp_send_reply(request, HTTP_NOTFOUND, "NOT_FOUND", 0);
    return;
  }

  evbuffer *outbuf = evhttp_request_get_output_buffer(request);
  for(;;){
    int len = fread(buf, 1, sizeof(buf), fp);
    if(len<=0) break;
    evbuffer_add(outbuf, buf, len);
  }
  evhttp_send_reply(request, HTTP_OK, "OK!", outbuf);
  fclose(fp);



}

int main(){
  //1. 创建libevent上下文;
  event_base* base  = event_base_new();
  if(!base){
    cerr << "event_base_new faild." << endl;
    return -1;
  }

  //2. 创建evhttp上下文
  evhttp* evh = evhttp_new(base);

  //3. 绑定服务端地址和端口
  if (evhttp_bind_socket(evh, "0.0.0.0", SERV_PORT) != 0) {
    cout << " evhttp_bind_socket faild." << endl;
  }

  //4. 设置回调函数
  evhttp_set_gencb(evh, http_cb, 0);

  //5. 进入事件主循环
  event_base_dispatch(base);
  event_base_free(base);
  if(evh)
    evhttp_free(evh);
  return 0;
}

