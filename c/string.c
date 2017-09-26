#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
字符串的两种赋值形式：
1.char a[] : 将字符放入一个字符数组中，变量a指向字符数组的第一个地址.
2.char *b  : 将指针b指向字符串的第一个字符地址.
*/


int main(){
    char a[] = "hello world!";
    char *b = "hahaha!";
    printf("a is %s\n", a);
    printf("b is %s\n", b);
}
