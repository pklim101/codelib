/*************************************************************************
    > File Name: move.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  2/20 11:01:52 2022
 ************************************************************************/

#include<iostream>
using namespace std;

class Info {
public:
  Info():age(0){}
  Info(int age):age(age){}
  int age;
};

class Student {
public:
  Student() : info(nullptr) {}
  Student(const Student& stu) {
    cout << "constructor" << endl; 
  }
  Student(Student&& stu) noexcept : info(stu.info) {
    stu.info = nullptr;
    cout << "Move constructor" << endl; 
  }
  ~Student() {}; 
  Info* info;
}; 

int main(){
  Student stu;
  stu.info = new Info(20);
  Student stu1(stu);
  cout << stu.info->age << endl;
  Student stu2(std::move(stu));
  cout << stu2.info->age << endl;
  return 0;
}
