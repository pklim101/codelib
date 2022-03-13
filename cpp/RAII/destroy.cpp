/*************************************************************************
    > File Name: destroy.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月30日 星期四 11时26分08秒
 ************************************************************************/

#include<iostream>
#include<unistd.h>
#include<mutex>
#include<thread>
using namespace std;
/**
RAII: resource aquisition is initialization.
 */

class A {
public:
  A(){
    cout << "construction." << endl;
  }
  ~A(){
    cout << "destroy." << endl;
  }
};

void test(){
  A a;
}


void test1(){
  mutex mutex;
  mutex.lock();
  mutex.unlock();
}

void test2(){
  A* aa = new A;
  mutex mutex;
  lock_guard<std::mutex> lck(mutex);
}


void test3(){

}

mutex mtx;
void print(int i){
  lock_guard<std::mutex> lck(mtx);
  cout << i << endl;
}

int main(){
  std::thread tid[10];
  for (int i = 0; i < 10; i++) 
    tid[i] = thread(print, i);

  for (int i = 0; i < 10; i++) tid[i].join();

  return 0;
}

