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
using namespace std;

/**
用信号Ctrl+c中断事件.
思路：
1. 创建libevent上下文: event_base_new;
2. 创建信号事件:初始化事件,此时处理non-pending状态;
3. 添加信号事件:此时处理pending状态; 
4. 事件分发处理-进入事件主循环：event_base_dispatch();
5. 事件清理:event_free();
6. event_base清理;
*/

#define SERV_PORT 8001
static void signal_cb(evutil_socket_t sig, short events, void* arg){
  //如下不处理的情况下，按Ctrl+z可以先挂起，然后再kill掉该进程.
  cout << "Ctrl+C." << endl;
  event_base *base = (event_base*)arg;
  //执行完当前处理的事件函数就退出
  //event_base_loopbreak(base);

  //1.运行完>>所有<<的活动事件再退出.
  //2.事件循环没有运行时也有等运行一次再退出.
  timeval t = {3,0}; //超时时间：至少运行三秒后退出.
  event_base_loopexit(base, &t);

}
//pkill test_signal
static void Kill(evutil_socket_t sig, short events, void* args){
  cout << "kill." << endl;
  event* ev = (event*)args;
  //对于非持久状态的事件，这里可以判断为非持久状态后，再放到pending中.
  if(!evsignal_pending(ev, NULL)){
    event_del(ev);
    event_add(ev, NULL);
  }
}

int main(){
  //1. 创建libevent上下文
  event_base* base  = event_base_new();
  //2. 创建SIGINT中断信号事件
  //evsignal_new是调用的宏，隐藏掉了状态: EVSIGAL|EV_PERSIST.
  event* sigc = evsignal_new(base, SIGINT, signal_cb, base);
  //3. 添加Ctrl_c事件
  if(!sigc){
    cerr << "evsignal_new failed." << endl;
    return -1; 
  }
  if(event_add(sigc, 0) != 0){
    cerr << "event_add failed." << endl;
    return -1;
  }

  //添加kill信号事件.
  //非持久状态:该事件只进入一次pendding状态.
  //event_self_cbarg():传递当前event(即sigk)到pendding状态中.
  //event* sigk = evsignal_new(base, SIGTERM, kill, event_self_cbarg());
  event *sigk = event_new(base, SIGTERM, EV_SIGNAL, Kill, event_self_cbarg());
  if(!sigk){
    cerr << "event_new sigk failed." << endl;
    return -1; 
  }
  if(event_add(sigk, 0) != 0){
    cerr << "event_add sigk failed." << endl;
    return -1;
  }

  //4. 进入事件主循环
  //event_base_dispatch(base);
  //循环事件
  //EVLOOP_ONCE:等待一个事件运行，直到没有活动事件就退出，返回0；
  //EVLOOP_NONBLOCK:有活动事件就处理，没有就退出，返回0；
  /**
  bool isexit = false;
  while(!isexit){
    event_base_loop(base, EVLOOP_NONBLOCK);
  }
  */
  //EVLOOP_NO_EXIT_ON_EMPTY：没有注册事件也不返回，用于事件后期多线程添加.
  event_base_loop(base, EVLOOP_NO_EXIT_ON_EMPTY);
  event_free(sigc);
  event_base_free(base);
  return 0;
}

