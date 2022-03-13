/*************************************************************************
    > File Name: pointer.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年05月25日 星期一 16时16分11秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

class A{
public: 
  A(string* name):_name(name){
  //A(){

  }
  string* _name = nullptr;
  ~A(){
    //delete _name;
    //_name = nullptr;
  }
};


int main(){
  //delete一个野指针，看看发生什么？
  int* aa;
  //delete aa; //发生了错粗：invalid pointer
  cout << "ye zhi zhen:"<< *aa << endl; //脏治


  // delete只是释放了指针指向的堆空间，但是指针变量本身还是存在的，而且指向了脏数据.
  vector<int>* vec = new vector<int>;
  vec->push_back(100);
  vec->push_back(200);
  for (auto &i : *vec) {
    cout << &i << endl;
  }
  cout << vec << ":" << vec->front() << endl;
  delete vec;
  vec = nullptr; //如果不置为nullptr,则读到的是脏数据.
  //cout << vec << ":" << vec->front() << endl; //段错误：vec被置为nullptr了，所以该指针是一个空指针，不能访问.

  string name = "Tom";
  //A a; //外部传入的栈指针销毁后
  A a(&name); //double free ==> _name和name都指向了同一个地址，所以会重复释放.
  //cout << a._name << endl;


  return 0;
}
