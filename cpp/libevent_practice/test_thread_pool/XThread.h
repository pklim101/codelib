/*************************************************************************
    > File Name: XThread.h
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月25日 星期六 13时27分57秒
 ************************************************************************/
#pragma once
#include<iostream>
using namespace std;

class XThread{
public:
  //启动线程
  void Start();

  //线程入口函数
  void Main();
  XThread();
  ~XThread();

  //线程编号
  int id = 0;

};
