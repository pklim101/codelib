/*************************************************************************
    > File Name: firstlibevent.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月19日 星期日 00时05分08秒
 ************************************************************************/

#include<iostream>
#include<event2/event.h>
using namespace std;

int main(){
	//创建libevent上下文，后面所有操作都是基于该上下文做
	event_base *base = event_base_new();
	if (base) {
		cout << "event_base_new success." << endl;
	}
  return 0;
}

