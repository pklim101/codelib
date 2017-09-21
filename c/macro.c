#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
宏定义两种情况：结尾都没有分号.
1. 直接定义一个常量，注意不是用=号赋值;
2. 定义一个函数式宏，可以用\作宏的延续，解决单行写不完一个宏的问题.注意：在使用该宏的时候，传入的字符串是不需要引号的.
*/

#define WIDTH 10

#define sayHello(name, where) \
    printf("Jim say Hello to " #name ", and tell him he will go " #where "\n")


int main(){
    printf("Width is : %d\n", WIDTH);
    sayHello(Amy, Great Wall);
}
