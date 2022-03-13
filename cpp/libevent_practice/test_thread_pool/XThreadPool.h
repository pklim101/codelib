/*************************************************************************
    > File Name: XThreadPool.h
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月25日 星期六 13时22分04秒
 ************************************************************************/

#include<iostream>
#include<vector>
//#include "XThread.h"
using namespace std;

class XThread; //在.h文件中尽量少引用文件
class XThreadPool {
public:
  //单例
  static XThreadPool* Get(){
    static XThreadPool p;
    return &p;
  }
  //初始化所有线程并启动线程
  void Init(int threadCount);


private:
  //线程池中线程数量
  int threadCount = 0;
  //线程池线程：存储线程
  std::vector<XThread*> threads; //在头文件中尽量不用命名空间 using namespace xxx
  //将构造函数作为私有的，从代码层面保证了单个对象
  XThreadPool(){};

};
