/*************************************************************************
    > File Name: cast.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年05月21日 星期四 11时16分19秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Base {
public:
  virtual void foo(){
    cout << "base foo..." << endl;
  }
};

class Derive : public Base{
public:
  void foo(){
    cout << "derive foo..." << endl;
  }

  void foo2(){
    cout << "derive special foo2..." << endl;
  }
};

int main(){
  int b = 100;
  const int* a = &b;
  int* c = const_cast<int*>(a);
  *c = 200;
  cout << *c << endl;

  Base* d = new Derive;
  //d->foo2(); //错误：‘class Base’没有名为‘foo2’的成员

  Derive *d_re = reinterpret_cast<Derive*>(d);
  d_re->foo();
  d_re->foo2();

  Derive *d_st = static_cast<Derive*>(d);
  d_st->foo();
  d_st->foo2();

  Derive *d_dy = dynamic_cast<Derive*>(d);
  d_dy->foo();
  d_dy->foo2();

  double n = 10.1;
  int s = static_cast<int>(n);
  cout << s << endl;

  Derive *sub = new Derive;
  Base *pr = dynamic_cast<Base*>(sub);
  pr->foo(); //子类转为父类后，调用的还是子类的方法.

  Base* par = new Base;
  Derive* der = dynamic_cast<Derive*>(par);
  cout<< "............."<<endl;
  der->foo2();//竟然可以调用子类特有方法. 
  //der->foo2(); //如雷转为子类，会段错误.

  //指针之间的bit重解释
  int *ta;
  char* tb = "a";
  ta = reinterpret_cast<int*>(tb);
  cout << *ta<< endl;

  //基本类型之间的类型转换
  char tc = 'b';
  int td = static_cast<int>(tc);
  cout << td << endl;

  return 0;
}


