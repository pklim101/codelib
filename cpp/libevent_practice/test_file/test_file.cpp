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
using namespace std;

/**
  监听文件
思路：
1. 设置feature为EV_FEATURE_FDS才能监听文件事件. event_config_require_features(); 
2. open()以何种方式打开文件,lseek()从文件哪里读；read()每次读多少字节到buf中.
*/

void read_file(evutil_socket_t fd, short events, void* arg){
  char buf[1024] = {0};  //初始化为0后就不用在末尾追加\0，因为在字节中，每个char都表示的是asscii码，0表示\0，也就是结束符。初始化列表元素少于数组个数的时候，都用默认值初始化.
  int len = read(fd, buf, sizeof(buf)-1);
  if(len>0) {
    cout << "+" << endl;
    cout << buf << endl;
  } else {
    cout << "." << endl;
    //this_thread::sleep_for(500ms);
    this_thread::sleep_for(std::chrono::seconds(1));
  }
}



int main(){
  //1. 配置文件监听feature:EV_FEATURE_FDS;
  event_config *conf = event_config_new();
  event_config_require_features(conf,EV_FEATURE_FDS);

  //2. 用配置的conf创建libevent上下文;
  event_base* base  = event_base_new_with_config(conf);
  if(!base){
    cerr << "event_base_new_with_config faild." << endl;
    return -1;
  }

  //3. 创建文件监听事件;
  const char* pathname = "/tmp/test.log";
  int sock = open(pathname, O_RDONLY);
  if(sock == -1){
    cerr << "open file faild." << endl;
    return -2;
  }
  //将文件指针移动到结尾处.
  lseek(sock, 0, SEEK_END);

  event* fev = event_new(base, sock, EV_READ|EV_PERSIST, read_file, 0);//注意：监听读事件需要将EV_READ加进去. 
  if(!fev){
    cerr << "event_new failed." << endl;
    return -1; 
  }
  //4. 添加文件监听事件;
  if(event_add(fev, NULL) != 0){
    cerr << "add event_new failed." << endl;
  }


  //5. 进入事件主循环
  event_base_dispatch(base);
  event_free(fev);
  event_base_free(base);
  return 0;
}

