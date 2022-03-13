/*************************************************************************
    > File Name: thread.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2019年08月20日 星期二 17时12分46秒
 ************************************************************************/

#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<sstream>
#include<thread>
using namespace std;

class Stu;

struct Data {
  int id;
  Stu* stu;
};

class Stu {
public:
  Stu(Data& data):data_(data) {}
  void foo (); 
  int process_num_ = 0;
private:
  int age_;
  Data data_;
};

typedef void* (*thread_pp)(void*); //1.thread_pp前面的*不能少；2.返回值不能用括号包起来，如(void*)，这就相当于定义函数的返回值不能被括号包起来一样.
void* thread_local_test(void* args){
  Data* data = (Data*)args;
  cout << __FUNCTION__ << endl;
  cout << "thread_id_sub:"<< std::this_thread::get_id() <<endl;
  cout << "args-process_num:" << data->stu->process_num_ << endl;
  data->stu->process_num_++;
  /*
  while(true) {
    stringstream ss;
    ss.str("");
    ss << "xx";
    int a;
    printf("=======%p,%s\n",&a,ss.str().c_str());
    sleep(1);
  }
  */
}

void Stu::foo () {
  data_.stu = this;
  thread_pp tpp = thread_local_test;
  cout << "thread_id_main:"<< std::this_thread::get_id() <<endl;
  pthread_t pid;
  pthread_create(&pid, NULL, thread_local_test, &data_);
  pthread_join(pid,NULL);
  cout << "args-process_num in Stu:" << process_num_ << endl;
}


void* foo(void* tno){  //定义为指针函数
  while(1){
    cout << *((int*)tno) << endl;
    sleep(1);
  }
}




int main(){
  Data data;
  Stu stu(data);
  stu.foo();

  /**
  pthread_t tids[3];
  int indexs[3];   //这里需要用数组存放线程的编号，因为foo函数传的参数是指针
  for(int i = 0; i<sizeof(tids)/sizeof(pthread_t); i++){
    indexs[i] = i;
    int err = pthread_create(&tids[i], NULL, foo, (void *)&indexs[i]); //最后一个参数需要强转为(void *)
    if(err!=0) {
      cout << "create thread " << i << " err:"<<err << endl;
    }
  }

  for(int i=0; i< sizeof(tids)/sizeof(tids[0]); i++){
    pthread_join(tids[i],NULL);  //会等待线程结束，然后回收线程资源，防止僵尸线程.
  }
  */

  return 0;
}
