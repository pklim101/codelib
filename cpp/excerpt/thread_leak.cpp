/*************************************************************************
    > File Name: thread_leak.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年07月08日 星期三 11时56分24秒
 ************************************************************************/

#include<iostream>
#include <pthread.h>
using namespace std;

/**
  使用重复的线程id会造成内存泄漏.
  valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --run-libc-freeres=yes --log-file=./valgrind_report.log ./a.out 
 */

void* foo(void* arg){
  int* a = (int*)arg;
  cout << *a << endl;
}

int main(){
  pthread_t tid;

  for (int i = 0; i < 3; i++) {
    int ret = pthread_create(&tid, NULL, foo, &i);
    if (ret == 0) {
      cout << "OK" << endl;
    } else {
      cout << "Fail" << endl;
    }
  }


  return 0;
}
