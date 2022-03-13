/*************************************************************************
    > File Name: virtualherit.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年05月26日 星期二 18时29分53秒
 ************************************************************************/

#include<iostream>
using namespace std;

// 在多重继承中，如果发生了如：类A继承类COM，类B继承类COM，类C同时继承了类A和类B。最终在类C中就有了两份类COM的成员，这在程序中是不能容忍的。当然解决这个问题的方法就是利用虚继承。

// 注意：C++编译系统在实例化C类时，只会将虚基类的构造函数调用一次，忽略虚基类的其他派生类（class A，class B）对虚继承的构造函数的调用，从而保证了虚基类的数据成员不会被多次初始化。

class COM {
public:
  COM() {
    cout << "class COM constuct." << endl;
  }
  ~COM() {
    cout << "class COM desctory." << endl;
  }
};

class A : virtual public COM{  //如果不是虚继承，则COM的构造函数会调用两次，析构函数也会调用两次.
public:
  A() {
    cout << "class A constuct." << endl;
  }
  ~A() {
    cout << "class A desctory." << endl;
  }
};

class B : virtual public COM{
public:
  B ()  {
    cout << "class B construct." << endl;
  }
  ~B () {
    cout << "class B destroy." << endl;
  }
};

class C : public A, public B {
public:
  C ()  {
    cout << "class C construct." << endl;
  }
  ~C () {
    cout << "class C destroy." << endl;
  }

};

int main(){
  C c;
  return 0;
}

