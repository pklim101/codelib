/*************************************************************************
    > File Name: inheritanceDesign.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年07月02日 星期四 12时02分20秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;


/**
  编译总出错： inheritanceDesign.cpp:(.text._ZN7Utility11getInstanceEv[_ZN7Utility11getInstanceEv]+0x2d): undefined reference to `Utility::_instance''
  因为_instance是静态成员，所以需要定义：Utility* Utility::_instance;
 */

class Base;

class Utility{
public:
  static Utility* getInstance () {
    if (!_instance) {
      _instance = new Utility;
    }
    return _instance;
  }
  void addObj(Base* obj){
    _vec.push_back(obj);
  }
  void run_all();

private:
  vector<Base*> _vec;
  //Utility* _instance;  错误：在静态成员函数中使用成员‘Utility::_instance’无效
  static Utility* _instance;
};

Utility* Utility::_instance;

class Base {
  friend class Utility;
public:
  Base () {
    Utility::getInstance()->addObj(this);
  }
  virtual void run(){
    cout << "run..." << endl;
  }
};

class A : public Base {
public:
  //终于搞明白且写出了一个多态.
  //终于搞明白一路都是调用父类的方法，却可以实现执行的是子类方法:因为多态.
  void run(){
    cout << "run...A" << endl;
  }

};
class B : public Base {
  void run(){
    cout << "run...B" << endl;
  }
};
class C : public Base {

};

void Utility::run_all(){
    for (auto i : _vec) {
      i->run();
    }
}


int main(){
  Base** base = new Base*[3];
  base[0] =  new A;
  base[1] =  new B;
  base[2] =  new C;
  Utility::getInstance()->run_all(); 
  return 0;
}
