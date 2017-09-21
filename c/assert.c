#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// the first sample
// gcc test.c -o a.o

int main(){
    int a ;
    printf("please input a number:");
    scanf("%d", &a);
    //断言用法：如果里面的表达式或者变量为真，则不输出，如果为假，则输出.
    assert(a>10);
    printf("the input number is : %d", a);
    return(0);
    
}
