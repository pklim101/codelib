/*************************************************************************
    > File Name: firstlibevent.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月19日 星期日 00时05分08秒
 ************************************************************************/

#include<iostream>
#include<event2/event.h>
#include<event2/listener.h>
#include<string.h> //memset()
using namespace std;

/**
配置libevent.
思路：
1. 创建配置上下文: event_config_new;
1. 创建libevent配置上线文：event_base_new_with_config；
2. 创建监听(socket创建、端口绑定、backlog、回调函数)：evconnlistener_new_bind；
3. 时间分发处理：event_base_dispatch();
4. evconnlistener清理;
5. event_base清理;
*/

#define SERV_PORT 8001

void listener_cb(struct evconnlistener * l, evutil_socket_t s, struct sockaddr * a, int socklen, void *arg) {
	cout << "listener_cb."<< endl;
}

int main(){
	//创建配置上下文
	event_config *conf = event_config_new();

	//显示支持的网络模式
	const char **methods = event_get_supported_methods();
	cout << "event_get_supported_methods:" << endl;
	for (int i = 0; methods[i] != NULL; i++){
		cout << methods[i] << endl;
	}
	//设置特征
	//event_config_require_features(conf, EV_FEATURE_EARLY_CLOSE); //[warn] event_base_new_with_config: no event mechanism available
	//event_config_require_features(conf, EV_FEATURE_ET); //只有设置为EV_FEATURE_FDS才可以使用select,ET则报错.

	//设置网络模型为select.
	event_config_avoid_method(conf, "epoll");
	event_config_avoid_method(conf, "poll");

	//创建libevent上下文，后面所有操作都是基于该上下文做
	event_base *base = event_base_new_with_config(conf);
	if (conf){
		event_config_free(conf);
	}
	if (base) {
		cout << "event_base_new_with_config success." << endl;
	} else {
		cout << "event_base_new_with_config faild." << endl;
		base = event_base_new(); //如果用配置创建上下文失败则使用默认配置创建.
		if (!base) {
			cout << "event_base_new failed." << endl;
		} else {
			cout << "event_base_new success." << endl;
		}
	}

	//获取当前网络模型
	cout << "current method is :" << event_base_get_method(base) << endl;

	int f = event_base_get_features(base);
	if (f & EV_FEATURE_ET) {
		cout << "EV_FEATURE_ET event is supported." << endl;
	}
	if (f & EV_FEATURE_O1) {
		cout << "EV_FEATURE_01 event is supported." << endl;
	}
	if (f & EV_FEATURE_FDS) {
		cout << "EV_FEATURE_FDS event is supported." << endl;
	}
	if (f & EV_FEATURE_EARLY_CLOSE) {
		cout << "EV_FEATURE_EARLY_CLOSE event is supported." << endl;
	}


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

	event_base_dispatch(base);

	if(ev)
		evconnlistener_free(ev);
	if(base)
		event_base_free(base);
  return 0;
}

