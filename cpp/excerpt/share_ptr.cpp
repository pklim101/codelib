/*************************************************************************
    > File Name: share_ptr.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年07月08日 星期三 18时13分39秒
 ************************************************************************/

#include<iostream>
#include <memory>
using namespace std;

class A {
public:
  A () {
    cout << "construct A" << endl;
  }
  ~ A () {
    cout << "desconstruct A" << endl;
  }
  void foo () {
    cout << "A foo()========================." << endl;
  }
};

class B {
public:
  B () {
    cout << "construct B" << endl;
  }
  ~B () {
    cout << "desconstruct B" << endl;
  }
  shared_ptr<A> ptr;
};

//指针指针指向栈对象竟然会析构两次A，而且还不出错.
void test(){
  A a;
  B b;
  b.ptr = make_shared<A>(a); 
  b.ptr->foo();
}

void test2(){
  B b;
  //b.ptr = make_shared<A*>(a); 
  b.ptr->foo();  //好神奇，竟然该智能指针不指向A，也能成功调用foo()。
}

int main(){
  test2();
  return 0;
}

