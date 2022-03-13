/*************************************************************************
    > File Name: union.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月22日 星期一 11时58分45秒
 ************************************************************************/

#include<iostream>
using namespace std;

//占用空间为成员最大的一个；
//同时只有一个成员有效，后面的会覆盖前面的.
union Stu{
  int level;
  char a;
};

typedef union {
  unsigned int Ax;
  //结构体在内存位置表示：0-15位:AL, 16-31位:AH.
  struct AX {
    unsigned int AL:16;
    unsigned int AH:16; //AH在AX结构体的而部分，所以可以表示高16位置
  } sAX;
} example;

int main(){
  Stu stu;
  stu.a = 'A';
  stu.level = 10;
  cout << stu.a << endl;
  cout << stu.level << endl;
  cout << stu.a << endl;
  cout << sizeof(stu) << endl;
  return 0;
  
  example a;
  a.Ax = 0xAFAFBEBE;

  int i = a.sAX.AH;
  printf("AX = 0x%X, AH = 0x%X, AL = 0x%X\n", a.Ax, a.sAX.AH, a.sAX.AL);
}
