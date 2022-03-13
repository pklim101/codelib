/*************************************************************************
    > File Name: test.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月01日 星期一 11时20分22秒
 ************************************************************************/

#include<iostream>
//把a.h放在b.h下面就好了.
//这样貌似就是重新定义常量define TAG了
#include "a.h"
#include "b.h"


using namespace std;

/**
a.h:12:13: 错误：expected identifier before numeric constant
 #define TAG 1 

enum XX {
  1 = 1, //因为#define TAG 1做宏替换.
};

*/

int main() {
  cout << TAG << endl; //输出为2，并不是enum里的1. 貌似就是重新定义常量define TAG了.
  return 0;
}
