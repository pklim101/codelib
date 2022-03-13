/*************************************************************************
    > File Name: b.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月08日 星期三 11时51分33秒
 ************************************************************************/

#include<iostream>
#include<random> //mt19937和random_device()用
#include<sys/time.h>
#include<vector>
using namespace std;

class A{
public:
  static void getid();
};

void A::getid(){
  //srand(666); //种子值固定，则每次调用生成的随机数都是一样的.
  //srand(time(NULL)); //只有种子值变化，每次调用生成的随机数才不一样。但是这里是秒级别，如果一秒内调用多次，也会生成一样的随机数.
  //cout<<rand()<< endl;
  thread_local static std::mt19937 gen((std::random_device())());
  uint32_t a = gen();
  cout << a << endl;
}

void xx(){
  struct timeval tv;
  gettimeofday(&tv, 0);
  cout << tv.tv_usec << endl;
  srand(time(NULL));
}

void ff(int* a){
  cout << *a << endl;
  //free(a);
  //delete a;
  cout << *a << endl;
}

typedef void (*CALLBACK)(int a);

void cb(int a){
  cout << "callback" << a << endl;
}

//利用pair做函数回调
void vec(){
  vector<pair<CALLBACK,int>> ve; 
  auto pp = pair<CALLBACK,int>(cb,20);
  ve.push_back(pp);
  for(auto iter = ve.begin(); iter != ve.end(); ++iter){
    iter->first(iter->second);
  }
}

/**
const char* func()
{
   const char* p = "D.T.Software\n";
     
   return p;
}

	const char * pp = func();
  cout <<pp << endl;
  cout << CLOCKS_PER_SEC << endl;
*/

struct AA{
  int age;
};

void foo(void* data){
  //(void)data;
}

int main(){
  AA aa;
  aa.age = 18;
  foo(&aa);


 // int b = 20;
 // int *a = &b; //这个是在栈上，只有用new创建的才在堆上.
  int *a = new int(10);
  (void)a;
  int b = 20;
  ff(&b);
  return 0;
}

