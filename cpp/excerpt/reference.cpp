/*************************************************************************
    > File Name: reference.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  4/25 23:29:46 2020
 ************************************************************************/

#include<iostream>
using namespace std;

int a = 10;
int& foo(){
  return a; }

int main(){
  //foo()的返回值可以作为一个左值:因为其返回了一个引用
  foo() = 20;
  int& p = foo();
  cout << p << endl;
  return 0;
}
