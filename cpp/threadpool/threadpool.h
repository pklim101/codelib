/*************************************************************************
    > File Name: threadpool.h
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年03月13日 星期五 23时59分40秒
 ************************************************************************/

/**
brief: 用条件变量实现一个线程池.
核心思想：
1. 三个角色：客户端，任务队列，，线程池;
2. 生产者消费者关系：客户端---生产--->任务队列(消费)---生产--->线程池(消费);
3. 两个条件变量：1)队列不为满:若满足条件，则客户端请求可以放入任务队列；2)队列不为空:若满足条件，则唤醒一个线程来消费任务;
4. 线程池管理者：根据任务队列闲忙状态调整线程池线程数.

线程池实现步骤：
1. threadpool_init() :初始化一个线程池，主要对线程池对象初始化值，创建任务线程和管理线程;
2. threadpool_task_add() :唤醒客户端，将任务接受过来放入任务队列；
3. threadpool_worker() :唤醒一个工作线程来消费处理任务；
4. threadpool_manager() :根据任务队列闲忙状态调整线程池中工作线程数量；
5. threadpool_destroy() :pthread_join()和pthread_exit() 销毁线程;
6. threadpool_free() :释放线程池相关的锁、条件变量、malloc分配的线程池结构体对象和任务结构对象.

 */

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__ 

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>
#include<string.h>
#include<assert.h>
using namespace std;

struct threadpool_task_t {
  void* args;
  void* (*call_back)(void* args);
};

//描述线程池相关信息
struct threadpool_t {
  pthread_mutext_t lock;           //锁该结构体
  pthread_mutext_t busy_thr_lock;  //锁忙线程数量更变:busy_thr_num 

  pthread_cond_t queue_not_full;   //队列满了，添加任务的线程(此例子中是主线程)阻塞等待该条件变量后向队列添加任务;
  pthread_cond_t queue_not_empty;  //列队为空了，线程池中的工作线程阻塞等待该条件变量满足后从队列取出任务执行;

  pthread_t* worker_tids;         //存放线程池中线程tid，数组;
  pthread_t manager_tid;          //管理者线程tid;

  threadpool_task_t* task_queue;  //任务队列; 
  int queue_size;                 //队列中实际任务数;
  int queue_capacity;             //队列容量;
  int queue_front;                //队首下标;
  int queue_rear;                 //队尾下标;

  int min_thr_num;                //线程池中最少线程数;
  int max_thr_num;                //线程池中可创建最多线程数;
  int live_thr_num;               //线程池中现有多少线程数;
  int busy_thr_num;               //线程池中处理工作状态的线程数;
  int wait_exit_thr_num;          //要销毁的线程数(销毁多余的空闲线程数);  

  int shutdown;                   //是否关闭线程池.
}

//初始化一个线程池，主要对线程池对象初始化值，创建任务线程和管理线程;
threadpool_t* threadpool_init(int min_thr_num, int max_thr_num, int queue_capacity); 

//唤醒客户端，将任务接受过来放入任务队列；
int threadpool_task_add(threadpool_t* pool, (void*)(*call_back)(void* args), void* args);

//唤醒一个任务线程来消费处理任务；
void* threadpool_worker(void* threadpool); 

//根据任务队列闲忙状态调整线程池中工作线程数量；
void* threadpool_manager(void* threadpool);

//pthread_join()和pthread_exit() 销毁线程;另外:pthread_cancel()、pthread_detach()也可以销毁线程.
void threadpool_destroy(void* pthreadpool); 

//释放线程池相关的锁、条件变量、malloc分配的线程池结构体对象和任务结构对象.
void threadpool_free();



#endif
