/*************************************************************************
    > File Name: gflags.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月02日 星期二 15时20分08秒
 ************************************************************************/

#include<iostream>
using namespace std;

//编译：g++ -std=c++11 -I./com/public/gflags/output/include/ -L./com/public/gflags/output/lib/  1.cpp -lgflags
//注意：编译的时候，1.cpp 和 -lgflags顺序不能颠倒.

//在另外一个文件做如下定义.该文件不用包含，只需要编译的时候和使用FLAGS的文件一起编译即可。它们在连接处使用.
//DEFINE_int32(defer_close_second, 10, "seconds");

DECLARE_int32(defer_close_second);

int main (){
  cout << FLAGS_defer_close_second << endl; 
  return 0;
}
