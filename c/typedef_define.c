/*
typedef与define的区别：
1.typedef是定义类型，而define是定义常量；
2.typedef在编译阶段处理，而define在预处理阶段处理.
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



