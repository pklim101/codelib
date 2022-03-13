/*************************************************************************
    > File Name: threadpool.c
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年03月14日 星期六 11时34分10秒
 ************************************************************************/

#include<threadpool.h>

#define CHECK_TIME 60
#define ADJUST_STEP 10;

threadpool_t* threadpool_init(int min_thr_num, int max_thr_num, int queue_capacity) {
  do {
    //1. 给线程池开辟空间
    threadpool_t* threadpool = (threadpool_t*)malloc(sizeof(threadpool_t));

    threadpool->min_thr_num = min_thr_num;
    threadpool->max_thr_num = max_thr_num;
    threadpool->queue_capacity = queue_capacity;

    //2. 给工作线程开辟空间
    threadpool->worker_tids = (pthread_t*)malloc(sizeof(pthread_t) * threadpool->min_thr_num);

    //3. 给任务队列开辟空间
    threadpool->task_queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t) * threadpool->queue_capacity);

    //4. 初始化互斥锁和条件变量
    threadpool->lock = PTHREAD_MUTEX_INITIALIZER; 
    threadpool->busy_thr_lock = PTHREAD_MUTEX_INITIALIZER; 
    threadpool->queue_not_full = PTHREAD_COND_INITIALIZER; 
    threadpool->queue_not_empty = PTHREAD_COND_INITIALIZER; 

    //5. 启动min_thr_num个工作线程
    for (int i = 0; i < threadpool->min_thr_num; i++) {
      pthread_create(&threadpool->worker_tids[i], NULL, threadpool_worker, NULL);
    }
    threadpool->live_thr_num = threadpool->min_thr_num;

    //6. 启动管理者线程
    pthread_t tid;
    pthread_create(&tid, NULL, threadpool_manager, NULL);

    //7. 返回初始化成功的线程池
    return threadpool;

    //8. 如果初始化失败，free掉线程池相关资源 
    threadpool_destroy(threadpool);
  } while(0);
}

/** 主线程调用->添加任务:
1. 向任务队列中添加一个任务;
2. 唤醒阻塞在条件变量"不为空"的工作线程;
 */
int threadpool_task_add(threadpool_t* threadpool, void* (*call_back)(void* args), void* args) {

  //1. 锁住threadpool_t;
  pthread_mutex_lock(&threadpool->lock);

  //2. 主线程在此趴活:判断任务队列是否已满，如果满了则阻塞条件变量:不为满;
  while(threadpool->queue_size == threadpool->queue_capacity){
    pthread_cond_wait(&threadpool->queue_not_full, &threadpool->lock);
  }

  //3. 将任务添加到任务队列中;
  threadpool->queue_size++ ;
  threadpool->queue_rear= threadpool->queue_size;
  threadpool->task_queue[threadpool->queue_rear].args = (int*)args;
  threadpool->task_queue[threadpool->queue_rear].call_back = call_back ;

  //4. 唤醒阻塞在条件变量"不为空"的工作线程;
  pthread_cond_signal(&threadpool->queue_not_empty);

  //5. 添加任务后解锁threadpool_t;
  pthread_mutext_unlock(&threadpool->lock);

}

void* threadpool_work(void* threadpool){
  threadpool_t* threadpool = (threadpool_t*)threadpool;
  
  while(1) {
    //1. 锁住threadpool_t；
    pthread_mutext_lock(&threadpool->lock);

    //2. 工作线程在此趴活:判断任务队列是否不为空，如果为空则阻塞条件变量:不为空;
    while(threadpool->queue_size > 0){
      pthread_cond_wait(&threadpool->queue_not_empty, &threadpool->lock);
    }

    //3. 从任务队列取出任务;
    threadpool_task_t* task = (threadpool_task_t*)malloc(sizeof(threadpool_task_t));
    memeset(task, 0, sizeof(*task));
    task.args = threadpool->task_queue[0].args;
    task.call_back = threadpool->task_queue[0].call_back;
    threadpool->front = (threadpool->queue_front+1) % threadpool->queue_capacity;

    //4. 唤醒主线程将新的任务添加到任务队列中;  
    pthread_cond_broadcast(threadpool->queue_not_full);

    //5. 解锁threadpool_t；
    pthread_mutex_unlock(&threadpool->lock);

    //6. 加锁锁住忙线程数锁:busy_thr_lock --> busy_thr_num++ -->解锁;
    pthread_mutex_lock(&threadpool->busy_thr_lock)
    threadpool->busy_thr_num++;
    pthread_mutex_unlock(&threadpool->busy_thr_lock);

    //7. 执行任务:回调函数;
    call_back(args);

    //8. 解锁忙线程数锁:busy_thr_lock --> busy_thr_num-- -->解锁;
    pthread_mutext_lock(&threadpool->busy_thr_lock);
    threadpool->busy_thr_num--;
    pthread_mutex_unlock(&threadpool->busy_thr_lock)

  }
}

void* threadpool_manager(void* threadpool) {
  threadpool_t* threadpool = (threadpool_t*)threadpool;

  //1. 定时:sleep()，防止频繁检测耗费资源;
  sleep(CHECK_TIME);

  //2. 取出队列现有任务数和存活线程数;
  pthread_mutex_lock(&threadpool->lock);
  int queue_size = threadpool->queue_size;
  int live_thr_num = threadpool->live_thr_num;
  pthread_mutex_unlock(&threadpool->lock);

  //3. 取出忙线程数;
  pthread_mutex_lock(&threadpool->busy_thr_lock);
  int busy_thr_num = threadpool->busy_thr_num;
  pthread_mutex_unlock(&threadpool->busy_thr_lock);

  //4. 创建新线程; pthread_create();
  if (busy_thr_num < threadpool->max_thr_num && busy_thr_num/live_thr_num > 0.8) {
    for (int i = 0; i < ADJUST_STEP; i++) {
      pthread_create(&threadpool->worker_tids[i], NULL, threadpool_worker, NULL);
    }
    threadpool->live_thr_num += 10;
  }

  //5. 销毁多余的空闲线程: 巧妙销毁->唤醒任务线程,然后利用判断wait_exit_thr_num>0则退出线程pthread_exit();
  if (busy_thr_num > threadpool->min_thr_num && busy_thr_num/live_thr_num > 0.3) {
    threadpool->wait_exit_thr_num += ADJUST_STEP;
    for (int i = 0; i < ADJUST_STEP; i==) {
      pthread_cond_broadcast(&threadpool->queue_not_empty);
    }
  }

}

void* threadpool_destropy(void* threadpool){
  //1. shutdown = 1;

  //2. pthread_join(管理线程); 

  //3. phtread_joing(工作线程) + 唤醒所有工作线程;

  //4. free线程池:threadpool_free(void* threadpool);
}

void* threadpool_free(void* threadpool){
  //1. 释放任务队列;

  //2. 释放工作线程数组;

  //3. 释两个放锁 + 两个条件变量;

  //4. 释放线程池.
}

//任务中的回调函数
void* call_back(void* args) {
  printf("worker thread ===========> threadid:%d, task:%d\n", pthread_self(), *(int *)args);
  sleep(2);
  return NULL;
} 

int main(void) {
  //1. 初始化线程池
  threadpool_t* threadpool = threadpool_init(3, 50, 100);

  //2. 模拟添加任务到任务队列中
  int num[10];
  for (int i = 0; i < 10; i++) {
    threadpool_task_add(threadpool, call_back, (void*)&num[i]);  //注意参数&num[i]要强转为(void*)
  }

  //3. 销毁线程池
  threadpool_destroy(threadpool);
}





