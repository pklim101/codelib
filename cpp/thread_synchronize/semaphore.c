/*************************************************************************
    > File Name: semaphore.c
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  3/15 17:43:15 2020
 ************************************************************************/

/**
brief: 信号量实现的生产者消费者模型.

核心要点：
1. sem_init()初始化信号量值，该值决定了同时可以有几个线程来访问共享数据;
2. sem_wait()：相当于pthread_mutex_lock()，实现-1；如果为0，则阻塞；
3. sem_pos()：相当于pthread_mutex_unlock()，实现+1，唤醒阻塞在sem_wait()上的线程；

与mutex的区别：
1. 是mutex的进化版，mutex只支持0-1，而信号量则支持0-N;
2. mutex只能一个线程同时访问共享数据，信号量可以N个线程同时访问信号量。

实现方法：
产品数(sem_product)：
空格数(sem_blank)：  
生产者每生产一个产品，则做的事是：空格-1，产品+1；如果空格数满了则sem_wait()阻塞;
消费者每消费一个产品，则做的事是：空格+1，产品-1；如果产品消费完了则sem_wait()阻塞;
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<time.h>

#define NUM 5  //定义信号量值为5，表示同时可以有5个线程访问共享数据.
int queue[NUM];
sem_t sem_product, sem_blank;  //需要提到最前面，如果放在main函数中，则producter()函数里使用的时候提示未定义.

void* producter() {
  int i = 0;
  while(1){
    sem_wait(&sem_blank); 
    queue[i] = rand() % 1000 + 1;
    printf("producter-----------%d\n",queue[i]);
    sem_post(&sem_product);
    i = (i+1) % NUM;  //逻辑环形队列.
    sleep(rand() % 3);
  }
}

void* consumer(){
  int i = 0;
  while(1) {
    sem_wait(&sem_product);
    printf("consumer-----------%d\n",queue[i]);
    sem_post(&sem_blank);
    i = (i+1) % NUM;
    sleep(rand() % 3);
  }
}

int main(void) {
  srand(time(NULL));
  
  sem_init(&sem_product, 0, NUM);  //sem_init已经废弃，用sem_open()
  sem_init(&sem_blank, 0, NUM);

  pthread_t pid, cid;
  pthread_create(&pid, NULL, producter, NULL);
  pthread_create(&cid, NULL, consumer, NULL);

  pthread_join(pid, NULL);
  pthread_join(cid, NULL);

  sem_destroy(&sem_product);
  sem_destroy(&sem_blank);
  return 0;
}
