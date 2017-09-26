#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
1.冒泡排序法;
*/
int pop_sort();

int main(){
    pop_sort();
}

/*
思路：从第一个元素开始，拿第一个元素比完后面所有元素；尽管中途作了交换，
也要继续拿交换后新的第一个元素与接下来的元素对比，最终目的是第一轮比下来后，保证第一个元素是最小的；后续一次循环.
注意：在进入第二个循环的最开始作if(i>=j) continue;操作，可减少时间复杂度.
*/
int pop_sort(){
    int data[] = {11, 8, 10, 0, 12, 39, 9};
    int length, i, j, k, tmp; 
    length = sizeof(data)/sizeof(data[0]);
    printf("the data total number is : %d\n", length);
    if(length<=0){
        printf("the data is empty!\n");
    }
    
    printf("初始数组为：");
    for(k=0; k<length; k++){
        printf("%d, ", data[k]);
    }
    printf("\n");
    
    printf("比较详细步骤：\n");
    for(i=0; i<length; i++){
        for(j=length-1; j>=0; j--){
            if(i>=j) continue;
            printf("%d - %d: %d-%d\n", i, j, data[i], data[j]);
            if(data[i]>data[j]){
                tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            } 
        }
    }

    printf("排序后的数组为：");
    for(k=0; k<length; k++){
        printf("%d, ", data[k]);
    }
}
