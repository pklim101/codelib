#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
宏定义两种情况：结尾都没有分号.
1. 直接定义一个常量，注意不是用=号赋值;
2. 定义一个函数式宏，可以用\作宏的延续，解决单行写不完一个宏的问题.注意：在使用该宏的时候，传入的字符串是不需要引号的.
3. 参数化的宏.

预处理器运算符
C 预处理器提供了下列的运算符来帮助您创建宏：
宏延续运算符（\）
字符串常量化运算符（#）
标记粘贴运算符（##）
*/

//常量宏
#define WIDTH 10

#define sayHello(name, where) \
    printf("Jim say Hello to " #name ", and tell him he will go " #where "\n")

#define token(num) printf("the token" #num " = %d\n", token##num)  //相当于把token和num的值连接到一起作为一个变量名token12
//参数化宏
#define MAX(x, y) (x>y ? x : y)


int main(){
    printf("Width is : %d\n", WIDTH);

    sayHello(Amy, Great Wall);
    
    int token12 = 100;
    token(12);

    printf("the result is %d\n", MAX(10,20));

}
