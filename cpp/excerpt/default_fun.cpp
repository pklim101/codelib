/*************************************************************************
    > File Name: default_fun.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年03月07日 星期六 16时27分37秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Stu {

};

class Teacher {
public:
  int age;
  Teacher &operator=(const Teacher &tc) {
    age = tc.age;
    cout << "copy assignment." << endl;
    return *this;
  }
  //只显式写拷贝构造函数，竟然报错，还必须显式写默认构造函数
  Teacher(const Teacher &tc) {
    age = tc.age;
    cout << "copy constructor." << endl;
  }
  Teacher() {
    sex = 100;
  }
  int& getSex() { //返回私有成员的引用，会造成私有成员访问权限泄漏，好奇怪.=>解释：如果指向让sex通过getSex()方法访问，不让返回的引用去修改该私有成员，则可将该方法定义为:const int& getSex() const;
    printf("in class sex:%p\n",sex);
    return sex;
  }
private:
  int sex;
};

int main () {
  Teacher t1;
  int& sex = t1.getSex();
  printf("sex:%p\n",sex);
  sex = 200;
  cout << t1.getSex() << endl;
  t1.age = 20;
  /* 拷贝赋值构造
  Teacher t2;
  t2 = t1;
  */
  Teacher t2 = t1; //拷贝构造函数.前面有类型声明就调用拷贝构造函数
  t1.age = 30;
  cout << "t2.age:" << t2.age << endl;
  cout << "t1.age:" << t1.age << endl;

  //为什么&operator返回的是引用，但是地址却不一样呢?
  printf("t1:%p,t2:%p\n",&t1,&t2);
  return 0;
}
