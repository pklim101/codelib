/*************************************************************************
    > File Name: constructor_param_list.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 三  3/11 17:02:02 2020
 ************************************************************************/

#include<iostream>
using namespace std;

class Stu {
public:
  Stu(int &age, std::string &name, int* sex): age_(age), name_(name), sex_(sex) {
    //这明显不对：name_本身就是成员变量，但是又把它声明为引用.
    string& name_ = name;  //这样做其实就相当于在构造函数内重新声明了一个同名的局部变量name_，因为既然要声明一个引用，则说明被引用的变量是已经初始化的。
    printf("&name:%p,_name:%p\n", &name, &name_);
    //&age_ = &age;
    printf("&age:%p, _age:%p\n",&age,&age_);  //对象成员age_的地址和传引用进来的age地址不一样:说明构造函数参数初始化列表赋值是拷贝数据而非传引用.
    //sex_ = sex;
    //printf("&sex:%p, _sex:%p\n",sex,sex_);  //
  }
  int getAge() {
    return age_;
  }
  void updateAge(int age) {
    age_ = age;
  }
  int getSex() {
    return *sex_;
  }
  void updateSex(int sex) {
    *sex_ = sex;
  }
  string getName(){
    return name_;
  }
  void updateName(string name) {
    printf("obj member name:%p\n",&name_);
    name_ = name;
  }
private:
  int age_;
  std::string name_;
  int* sex_;
};

int main() {
  int age = 20;
  printf("age out of:%p\n",&age);
  std::string name = "Tom";
  int sex = 1;
  Stu stu(age, name, &sex); //【重点】：通过构造函数初始化列表传引用后，在对象内修改了该成员值后，外部传的age并不会被改变.但是指针却可以，如传的值&sex.
  stu.updateAge(30);
  cout << "age=" << stu.getAge()<< endl;
  cout << "age out of=" << age << endl;

  int sex_a = 100;
  stu.updateSex(sex_a);
  cout << "sex_a=" << stu.getSex() << endl;
  cout << "sex=" << sex << endl;

  int aa = 10;
  int& bb = aa;
  printf("a:%p,b:%p\n",&aa, &bb); //地址一样

  stu.updateName("Amy");
  cout << "name=" << stu.getName() << endl;
  cout << "name out of=" << name << endl;



  return 0;
}

