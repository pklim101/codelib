/*
注意：点号和->的使用.

struct 和 union的区别：
1.最大区别：union是使用的共用存储空间;
2.truct的大小是所有成员占用空间之和，而union是共用内存空间，所以取占最大内存空间的成员变量的最小4的倍数为union大小.
3.struct成员赋值互不影响，而union的后一成员赋值会覆盖前一成员的值.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    char name[50];
    char title[70];
    int page_count;
};

union Magazine {
    char name[50];
    char title[70];
    int page_count;

};


int main(){
    struct Book book1;
    struct Book *book2;

    book2 = &book1;
    /* 该方法赋值总报错：error: incompatible types when assigning to type ‘char *[50]’ from type ‘char *’
    book1.name = "prid and prejudice";
    book1.title = "a very good night";
    book1.page_count = 300;
    */

    strcpy(book1.name, "Pride and prejudice");
    strcpy(book1.title, "a very good night");
    //strcpy(book1.page_count, 300); //这里不能将整型用strcpy的方式赋值.warning: passing argument 1 of ‘strcpy’ makes pointer from integer without a cast
    book1.page_count = 300;

    printf("book1's name is : %s\n", book1.name);
    printf("book1's title is : %s\n", book1.title);
    printf("book1's page_count is : %d\n\n", book1.page_count);

    strcpy(book2->name, "HAHA");
    strcpy(book2->title, "This is happy book");
    book2->page_count = 200;

    printf("book2's name is : %s\n", book2->name);
    printf("book2's title is : %s\n", book2->title);
    printf("book2's page_count is : %d\n\n", book2->page_count);


    union Magazine magazine1;
    strcpy(magazine1.name, "The king magazine");
    strcpy(magazine1.title, "The global things");
    magazine1.page_count = 50;
    
    printf("magazine1's name is : %s\n", magazine1.name);
    printf("magazine1's title is : %s\n", magazine1.title);
    printf("magazine1's page_count is : %d\n\n", magazine1.page_count);

    printf("struct book1 size is : %d\n", sizeof(book1));
    printf("struct book2 size is : %d\n", sizeof(book2));
    printf("union magazine1 size is : %d\n", sizeof(magazine1));


}
