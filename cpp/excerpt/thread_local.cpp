/*************************************************************************
    > File Name: thread_local.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年07月08日 星期三 16时52分27秒
 ************************************************************************/

#include<iostream>
#include<pthread.h>
using namespace std;

//thread_local周期是：线程.只会在线程创建的时候构造，在线程销毁的时候析构.
class Stu {
public:
  Stu(){
    cout << "construction" << endl;
  }
  void test(){
    cout << "test" << endl;
  }
  ~Stu(){
    cout << "deconstruction" << endl;
  }
};

thread_local Stu* stu = new Stu;

void* foo(void* arg){
  stu->test();
  int* pp = (int*)arg;
  printf("foo:%d\n", *pp);
}

int main(){
  int a = 100;
  pthread_t tid;
  int res = pthread_create(&tid, NULL, foo, &a);
  pthread_join(tid, NULL);
  cout << res << endl;
  return 0;
}
