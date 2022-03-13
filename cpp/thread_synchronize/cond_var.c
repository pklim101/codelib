/*************************************************************************
    > File Name: cond_var.c
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  3/15 15:17:55 2020
 ************************************************************************/

/**
brief:利用条件变量实现生产者消费者模型.

核心思想：消费者阻塞，生产者通知消费者.

要点：
1. 条件变量结合互斥锁实现生产和消费者模型；
2. pthread_cond_wait(*cond, *mutex): 
  a.需要条件初始化条件变量cond,mutex，
  b.需要提前加锁mutex，
  c.调用该函数的时候解锁和阻塞是原子操作,
  d.当该线程被唤醒时，首先抢锁mutex，如果抢到，则变成非阻塞，继续执行消费，否则继续阻塞着.
3. pthread_cond_signal(*cond): 唤醒至少一个阻塞的线程;
4. pthread_cond_broadcast(*cond): 唤醒所有阻塞的线程;
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

struct msg {
  struct msg* next;
  int num;
};

struct msg* head = NULL;
struct msg* node = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* producter() {
  while(1) {
    node = malloc(sizeof(struct msg));
    node->num = rand() % 1000;

    pthread_mutex_lock(&mutex);
    node->next = head; //1. 先挂上去：把要添加的节点的next指向head,
    head = node;       //2. 再把head指针指向node.
    pthread_mutex_unlock(&mutex);

    printf("product-------%d\n", node->num);
    pthread_cond_signal(&cond);
    sleep(rand() % 3);
  }
}

void* consumer() {
  while(1){
    pthread_mutex_lock(&mutex);
    while(head == NULL){
      pthread_cond_wait(&cond, &mutex);
    }
    /** 又写错了，这里总写错.
    node = head->next;
    head = node;
    */
    node = head;       //1. 先把head节点拿出来给node；
    head = node->next; //2. 再把head指针指向下一个节点.
    pthread_mutex_unlock(&mutex);

    printf("consumer-------%d\n", node->num);
    free(node);  //注意：消费了后应该释放掉该节点.
    sleep(rand() % 3);
  }
}

int main(void) {
  srand(time(NULL));

  pthread_t pid,cid;  //注意：只要声明该变量即可.

  pthread_create(&pid, NULL, producter, NULL);
  pthread_create(&cid, NULL, consumer, NULL);

  pthread_join(pid, NULL); //注意：这里参数一不是传指针.
  pthread_join(cid, NULL);
  return 0;
}
