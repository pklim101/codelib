/*
typedef与define的区别：
1.typedef是定义类型，而define是定义常量；
2.typedef在编译阶段处理，而define在预处理阶段处理.

定义常量的两种方式：
1. #define预处理器定义常量;
    #define identifier value
    #define LENGHT 10
2. const声明指定类型的常量.
    const type variable = value
    const int LENGTH = 10
#define与const区别：
1.const有类型，且const可有不同的作用域;
2.编译器可以对const进行类型安全检查，而对#define只是进行字符替换，没有类型安全检查;
3.调试工具可对const常量进行调试，但不能对宏常量进行调试.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAG "《Typedef Introduction》"

typedef struct Book {
    char name[30];
    char title[70];
    int page_count;
} book;

int main(){

    book book1; //如果不用typedef起别名book，则这里需要写成struct Book book1.

    strcpy(book1.name, TAG);
    strcpy(book1.title, "How to use the declaration typedef?");
    book1.page_count = 10;

    printf("book1's name is :%s\n", book1.name);
    printf("book1's title is :%s\n", book1.title);
    printf("book1's page_count is :%d\n", book1.page_count);

}



