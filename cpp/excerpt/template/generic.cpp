/*************************************************************************
    > File Name: generic.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月22日 星期一 10时40分44秒
 ************************************************************************/

#include<iostream>
using namespace std;

//为什么说不能推导出函数返回值呢？  这里验证了模版函数和模版类的函数，都可以的啊.

template<typename T> 
T foo(T a){
  //cout << a << endl;
  return a;
}

template<typename T>
class Stu{
public:
  T say(T w){
    //cout << w << endl;
    return w;
  }
};

int main(){
  auto pp = foo("hello");
  cout << pp << endl;

  Stu<string> stu;
  auto w = stu.say("world");
  cout << w << endl;
  return 0;
}
