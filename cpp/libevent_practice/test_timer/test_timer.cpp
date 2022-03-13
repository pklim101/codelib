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
  定时器：
  函数原型：
  struct event *event_new(struct event_base *, evutil_socket_t, short, event_callback_fn, void *);
  #define evtimer_new(b, cb, arg)   event_new((b), -1, 0, (cb), (arg))
思路：
1. evtimer_new同evsignal_new一样，通过宏展开的，设置的是非持久事件，只进入事件循环一次；
2. event_new则可以指定是否为持久事件.
*/

static timeval t1 = {1,0};
static void timer1(evutil_socket_t sig, short events, void* args){
  cout << "[timer1]" << endl;
  event* ev = (event *)args;
  if (!evtimer_pending(ev, &t1)) { //这里为什么还要传一个t1进去呢? 貌似是事件处于pending状态的有效期.
    event_del(ev);
    event_add(ev, &t1);
  }
}

static void timer2(evutil_socket_t sig, short events, void* args){
  cout << "[timer2]" << endl;
}

int main(){
  //1. 创建libevent上下文
  event_base* base  = event_base_new();
  //2. 创建定时器事件
  //evtimer_new是调用的宏，隐藏掉了状态: EV_SIGAL|EV_PERSIST.
  event* ev1 = evtimer_new(base,  timer1, event_self_cbarg()); //不用传socket，所以给-1，不用传参，所以给0.
  if(!ev1){
    cerr << "evtimer_new failed." << endl;
    return -1; 
  }
  //3. 添加timer事件
  if(event_add(ev1, &t1) != 0){
    cerr << "add evtimer_new failed." << endl;
  }

  //为什么这里不用加EV_TIMER而信号中断里需要加EV_SIGNAL
  event* ev2 = event_new(base, -1, EV_PERSIST, timer2, 0); //不用传socket，所以给-1，不用传参，所以给0.  
  timeval t2;
  t2.tv_sec = 0;
  t2.tv_usec = 500000;
  event_add(ev2, &t2);   //注意：就是这里加了t2，所以才实现了定时器功能.

  //4. 进入事件主循环
  event_base_dispatch(base);
  event_free(ev1);
  event_base_free(base);
  return 0;
}

