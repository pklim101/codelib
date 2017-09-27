#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
*/

int main(){
    int a = 6;
    int *p;
    int **q;
    p = &a;
    q = &p;
    printf("*p is : %d\n", *p);  //打印指针的值
    printf("*q is : %d\n", **q); //打印指针的指针的值

    //此处验证free() ：只有动态分配(如malloc)的内存才能free()释放.
    int *b = (int *)malloc(sizeof(int));
    *b = 100;
    printf("*b is : %d\n", *b);
    int **c;
    c = &b; 
    free(b); //如果把该指针b的内存释放，则指向指针b的指针c打印结果为0.
    printf("*c is : %d\n", **c);
}

