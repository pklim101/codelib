#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
*/


int main(){
    int a[] = {1,2,3,4,5,0};
    int length,i;
    length  = sizeof(a)/sizeof(a[0]); //获取数组元素个数 = 数组占用总空间/单个元素占用空间
    printf("array length is: %d\n", length);

    //打印数组
    for(i=0; i<length; i++){
        printf("a[%d] is: %d\n", i, a[i]);

    }
}
