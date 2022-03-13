/*************************************************************************
    > File Name: XThreadPool.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月25日 星期六 13时59分23秒
 ************************************************************************/

#include <iostream>
#include "XThread.h"
#include "XThreadPool.h"
#include <thread>
using namespace std;

//初始化所有线程并启动线程
void XThreadPool::Init (int threadCount) {
  this->threadCount = threadCount;
  for (int i = 0; i < threadCount; i++) {
    XThread* t = new XThread();
    t->id = i + 1;
    cout << "Create thread " << i << endl;
    //启动线程
    t->Start();
    threads.push_back(t);
    this_thread::sleep_for(std::chrono::seconds(1));
  }
}



