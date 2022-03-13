/*************************************************************************
    > File Name: template_specialize.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2019年10月21日 星期一 14时40分51秒
 ************************************************************************/

 /**
  模版特化：也叫模版具体化. 是在某种特定类型下的具体实现.
reference : https://blog.csdn.net/k346k346/article/details/82179205
特化：对模版类的某类数据类型进行特殊化处理。
方式：
  step 1. 正常声明模版类；
  step 2. 特化：声明同模版类，但是template<>括号里为空，类名后加<特殊化处理的数据类型>,类内的方法也用特殊化的类型而非T；
  step 3. 实现方法定义：正常模版类实现方法(必须) + 特化模版类方法.
偏特化：
  分三种：1.部分参数特化；2.参数部分特性特化，如指针； 3. 将模版参数特为另外一个模版
 */

#include<iostream>
#include<math.h>
using namespace std;

template<class T>
class Tclass{
public:
  bool isequal(const T& a, const T& b);
};

//=======>特化:即特殊处理化
//已经不具有template的意思了，已经明确为float了
template<>
class Tclass<float>{
public:
  //bool equal(T& a, T& b); //错误：‘T’未声明  
  bool isequal(const float& a, const float& b); 
};

template<class T>
//如果不加如下定义，则报错：该原型不匹配模版声明中的任何一个函数.
bool Tclass<T>::isequal(const T& a, const T& b){
  return a==b;
}
//如果不加特化的<float>，则报错：undefined reference to `Tclass<float>::isequal(float const&, float const&)'
bool Tclass<float>::isequal(const float& a, const float& b){
  return (fabsf((a-b))<10e-3); //错误：调用重载的‘abs(float)’有歧义 =>abs(int)的参数是int不是float
}

int main(){
  //Tclass t; 错误：missing template arguments before ‘t’
  Tclass<float> t;
  bool ret = t.isequal(10.1, 10.1);
  cout << ret << endl;
  return 0;
}

