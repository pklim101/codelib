/*************************************************************************
    > File Name: value_type.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年05月20日 星期三 14时47分04秒
 ************************************************************************/

#include<iostream>
using namespace std;

template<typename T>
class MyIterator{
public:
  typedef T value_type;
  value_type age;
  value_type num;
};

template<typename T>
//MyIterator<T>::value_type foo(MyIterator<T> i){ //value_type.cpp:17:1: 错误：‘MyIterator<T>::value_type’之前需要‘typename’，因为‘MyIterator<T>’是一个有依赖的作用域
typename MyIterator<T>::value_type foo(MyIterator<T> i){
  
}

int main(){
  MyIterator<int> myIterator;
  myIterator.age = 20;
  myIterator.num = 101;
  MyIterator<int>::value_type tt = foo(myIterator);
  cout << tt << endl;
  return 0;
}
