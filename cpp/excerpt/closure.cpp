/*************************************************************************
    > File Name: closure.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月08日 星期一 14时45分24秒
 ************************************************************************/

#include<iostream>
using namespace std;


//闭包

typedef void(*fun)();

fun foo(int a){
  int b = a;
  fun inner(){
    cout << a << endl;
  }
  return inner();
}

int main(){
  return 0;
}
