/*************************************************************************
    > File Name: 1.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年05月09日 星期六 15时22分08秒
 ************************************************************************/

#include<iostream>
#include<pthread.h>
#include "event2/event.h"
#include "event2/thread.h"

using namespace std;


int main(){
  int a = -1;
  if (a = evthread_use_pthreads() != 0){ 
    cout << "error." << endl;                                                                                                                                                                                    
  }
  cout << a << endl;
  return 0;
}
