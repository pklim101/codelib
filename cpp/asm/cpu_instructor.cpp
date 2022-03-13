/*************************************************************************
    > File Name: cpu_instructor.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月17日 星期三 12时01分02秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
using namespace std;
/**
生成汇编文件：gcc -S example.c 

简化汇编文件如下：
_add_a_and_b:
   push   %ebx           //将EBX寄存器里的值写入_add_a_and_b帧，同时ESP下移4个字节
   mov    %eax, [%esp+8] //mov表示将esp上移8个字节并取出里面的值后写入eax寄存器.
   mov    %ebx, [%esp+12]//取出3
   add    %eax, %ebx     //将EAX和EBX寄存器里的值相加后的结果写入第一个运算子EAX.
   pop    %ebx           //弹出栈中最近一个写入的值(即最低地址的值),然后写回EBX. 此时ESP中的地址回回首4个字节,也就是加4个字节.
   ret                   //用于终止当前函数的执行，将运行权交给上层函数. 

_main:                    //新建一个栈帧，将该地址保存到寄存器ESP里；
   push   3               //入栈3，将ESP里的地址减4个字节(也就是下移4个字节),存放3
   push   2               //入栈2
   call   _add_a_and_b    //调用函数，去找_add_a_and_b标签，并为该函数建栈帧.
   add    %esp, 8         //将ESP里的地址加上8个字节，也就是再回收8个字节,等于全部回收.
   ret                    //退出程序执行.
*/

int add_a_and_b(int a, int b) {
   return a + b;
}
int another_foo() {}

const char* namea = "hello";
const char* nameb = "bbbbb";
int age;
int level = 100;
int main() {
   printf("%d",10000);
   return add_a_and_b(2, 3);
}
