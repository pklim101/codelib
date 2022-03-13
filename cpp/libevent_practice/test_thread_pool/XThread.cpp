/*************************************************************************
    > File Name: XThread.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月25日 星期六 14时09分32秒
 ************************************************************************/

#include<iostream>
#include "XThread.h"
#include <thread>
using namespace std;

void XThread::Start(){
  thread th(&XThread::Main, this);
  //清理线程: 断开与主线程联系
  th.detach();
}

void XThread::Main(){
  cout << id << "XThread::Main() begin." << endl;
  cout << id << "XThread::Main() end." << endl;
}

XThread::XThread(){

}

XThread::~XThread(){

}

