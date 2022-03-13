/*************************************************************************
    > File Name: class.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年05月28日 星期四 17时57分22秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

class Base{
public:
  static void foo1(){
    cout << "static function foo1." << endl;
  }
  void foo2(){
    cout << "non static function foo2." << endl;
  }
};

class Derive: public Base{ //如果不public继承，则在派生类中无法访问基类的foo2()。
public:
  static void foo1(){
    cout << "static function foo1 is override." << endl;
  }
};

//适配器模式：关键点：创建一个适配器，继承A和B，在适配器里的目标方法内调用需要适配的方法.
class A {
public:
  void foo1(){
    cout << "adapter function foo1." << endl;
  }
};
class B {
public:
  void foo2(){
    cout << "adapter function foo2." << endl;
  }
};

class Adapter: public A, public B{
public:
  void foo1(){
    cout << "come into adapter." << endl;
    foo2();
  }
};


//验证直接调用Student()构造一个对象放入vector.
class Student{
public:
  //在调用Student()的时候会调用构造函数，如果不加{}则表示未定义.
  //Student(); //undefined reference to `Student::Student()' 
  //~Student();

  Student(){
  };
  ~Student(){

  };
};

//验证父类有非默认的构造函数的时候，子类是否需要在初始化列表中调用父类的非默认构造函数
class Parent {
public:
  const int a; //如果成员变量被声明为const的时候，需要在构造函数的初始化列表里初始化该成员变量.
  int b;
public:
  //无参构造函数被子类默认调用.
  /**
  Parent() {
    cout << "parent no params." << endl;
  }
  */
  //带参构造函数在子类必须显示调用.
  Parent(int a, int b): a(a), b(b){
  //带默认值后子类竟然可以不显示调用.
  //Parent(int a = 10, int b = 12){
    cout << "parent a and b." << a << endl;
  }
  void run(){
    cout << "parent run......" << endl;
  }
private:
  void play(){
    cout << "parent play......" << endl;
  }
};
class Child : public Parent {
public:
  Child():Parent(a, b){
  //Child(){
    cout << "child." << endl;
  }
  void run(){
    cout << "child run......" << endl;
  }
};

//验证如果声明了一个带参构造函数，那么其它默认构造函数还会被自动默认生成吗？
//如果只声明了带参的构造函数，则无参的构造函数不会被调用. 如： Monkey m 则不成.
class Monkey {
public:
  Monkey(int a, int b){
    cout << "Monkey......." << endl;
  }
};

//new 对象数组
class PPP {
public:
  //如果是二维指针，则不需要赋默认值.
  PPP(int a = 10):a(a) {

  }
  int a = 0;
};
/**
  PPP* ppp = new PPP[3];
  (ppp+1)->a = 12;
  int pv = (ppp+1)->a;
  cout << pv << endl;
  return 0;

  */


int main(){
  /**
  Parent* p = new Parent(1,2);
  Child* c = new Child();
  c = (Child*)p;
  c->run();
  */

  Parent* p = new Parent(1,2);

  //Monkey m; 声明了带参构造函数后 无参默认构造函数不会被生成.

  vector<Student> stus;
  stus.push_back(Student());
  Student a = Student();



  Adapter ad;
  ad.foo1();


  Derive d;
  //静态成员方法可以被继承
  Derive::foo1();
  d.foo1();
  d.foo2();
  int aa = 5;
  switch (aa) {
    case 1 :
      cout << 1 << endl;
      break;
    case 2 :
      cout << 2 << endl;
      break;
    default :
      cout << 3 << endl;
  }
  return 0;
}

