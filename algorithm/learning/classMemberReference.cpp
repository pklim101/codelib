/*************************************************************************
    > File Name: classMemberReference.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  4/ 2 22:32:39 2020
 ************************************************************************/

#include<iostream>
using namespace std;

/**
可以传一个引用，用来构造一个对象.
必须满足亮点:
1.成员变量要声明为引用; //注意：这里很奇怪，为什么可以没有初始值就可以声明为引用呢? 应该是构造函数在构造的时候先有了一个变量，然后_name成员再引用.
2.构造函数必须显式初始化该引用成员_name，也就是要用初始化列表的方式初始化成员.
*/

class Test {
private:
  string &name_; //warning: class 'Test' does not declare any constructor to initialize its non-modifiable members
public:
  Test(string &name):name_(name) {
    //name_ = name; //error: constructor for 'Test' must explicitly initialize the reference member 'name_'
  }

  void show(){
    printf("class member reference:name_:%p\n",&name_);
    cout << name_ << endl;
  }
};

int main(){
  string name = "Tom";
  Test t(name);
  t.show();
  printf("name:%p\n",&name);
  return 0;
}

