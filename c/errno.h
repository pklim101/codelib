#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// gcc test.c -o a.o
/*
*/

extern int errno;

int main(){
    FILE *fp;
    fp = fopen("file.txt", "r");
    if(fp == NULL){
        fprintf(stderr, "Value of errno:%d\n", errno);
        fprintf(stderr, "Error opening file:%s\n", strerror(errno));
    }else{
        fclose(fp);
    }
    return 0; 
}
