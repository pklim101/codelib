/*************************************************************************
    > File Name: 1.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 三  4/ 1 23:24:36 2020
 ************************************************************************/

#include<iostream>
#include<random> //mt19937和random_device()用
#include<sys/time.h>
#include<vector>
using namespace std;

class A{
public:
  static void getid();
};

void A::getid(){
  //srand(666); //种子值固定，则每次调用生成的随机数都是一样的.
  //srand(time(NULL)); //只有种子值变化，每次调用生成的随机数才不一样。但是这里是秒级别，如果一秒内调用多次，也会生成一样的随机数.
  //cout<<rand()<< endl;
  static std::mt19937 gen((std::random_device())());
  int a = gen();
  cout << a << endl;
}

void xx(){
  struct timeval tv;
  gettimeofday(&tv, 0);
  cout << tv.tv_usec << endl;
  srand(time(NULL));
}

int factory(int n){
  int m;
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    m = 1;
  } else {
    m = n * factory(n-1);
  } 
  return m;
}

int fib(int n){
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return fib(n-1) + fib(n-2);
  }
}

//递归对左右两部分进行归并
void __merge(int vec[], int l, int m, int r){
  //辅助变量
  int aux[r-l+1];
  for (int i = l; i <=r; i++) {
    aux[i-l] = vec[i];
  }
  //左右两部分同时比较的时候分别向右走动
  int i = l, j = m+1;
  for (int k = l; k <=r; k++) {
    //防止i和j越界了
    if (i>m) {
      vec[k] = aux[j-l];
      j++;
    } else if (j > r) {
      vec[k] = aux[i-l];
      i++;
    } else if (aux[i-l] < aux[j-l]) {
      vec[k] = aux[i-l];
      i++;
    } else {
      vec[k] = aux[j-l];
      j++;
    }
  }
}

//递归用归并排序
void mergeSort(int vec[], int l, int r){
  //拆分结束条件
  if (l >= r) 
    return;
  //int m = (r-l)/2;
  int m = (l+r)/2;
  //1. 拆分
  mergeSort(vec, l, m);
  mergeSort(vec, m+1, r);
  //2. merge
  __merge(vec, l, m, r);
}

//再练习一遍
int factory2(int n){
  int m = 0;
  if (n == 0) {
    return m;
  } else if (n == 1) {
    m = 1;
    return m;
  } else {
    m = n * factory2(n-1);
  }
  return m;
}

int fib2(int n){
  int m = 0;
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    m = fib2(n-2) + fib2(n-1); 
  }
  return m;
}

void __merge2(vector<int> vec, int l, int m, int r){
  //记住归并要用辅助变量
  vector<int> tmp(r-l+1);
  for (int i : vec) {
    tmp.push_back(i);  
  }
  int i = l, j = m+1;
  for (int k=l; k <= r; k++) {
    if (i > m) {
      vec[k] = tmp[j];
      j++;
    } else if (j > r) {
      vec[k] = tmp[i];
      i++;
    } else if (tmp[k-i] < tmp[k-j]) {
      vec[k] = tmp[k-i];
      i++;
    } else {
      vec[k] = tmp[k-j];
      j++;
    }
  }
}

void mergeSort2(vector<int> vec, int l, int r){
  if (l >= r) 
    return;
  int mid = (r - l)/2; 
  mergeSort2(vec, l, mid);
  mergeSort2(vec, mid+1, r);
  __merge2(vec, l, mid, r);
}

//选择排序：依次选择最小的数放在最前面。  类似冒泡排序。
void selectionSort(int vec[], int n){
  for (int i = 0; i < n; i++) {
    int min_index = i;
    for (int j = i+1; j < n; j++) {
      if (vec[min_index] > vec[j])
        min_index = j;
    }
    swap(vec[min_index], vec[i]);
  }
}

//插入排序：找到当前元素在前面适当的插入位置。类似每次起扑克牌后应该放到前面的哪个位置.
void insertionSort(int arr[], int n){
  for (int i = 0; i<n; i++) {
    for(int j = i; j>0; j--) {
      if (arr[j] < arr[j-1]) {
        swap (arr[j], arr[j-1]);
      } else {
        break;
      }
    }
  }
}

//ListNode node{   //我竟然都忘记结构体怎么定义了.
struct ListNode{
	ListNode* next;
  int val;
	ListNode(int val):val(val),next(NULL){}
}; //struct和class一样，最后都要写";".

//翻转链表：遍历的时候，1.先保存下一个节点；2.处理当前节点和上一个节点.
ListNode* reverseList(ListNode* head){
  ListNode* cur = head;
  ListNode* pre = nullptr;
  ListNode* next = nullptr;
  while(cur != nullptr){
    //**********容易绕晕的地方：开始遍历的时候，cur就是第一个节点.
    //1.保存下一个节点
    next = cur->next;
    //2. 把当前节点的next置为上一个节点pre
    cur->next = pre;
    //*********容易绕混的地方：此刻往后挪一个节点，然后赋值给下一次遍历使用
    //3. 赋值pre节点
    pre = cur;
    //4. 赋值cur节点
    cur = next; //***当前节点挪到下一位用于下次遍历.
  }
  return pre; //因此返利完成后，cur指向的是最后一个节点NULL，所以应该是pre.
}

class AA{
  char a;
  short b;
  virtual void f();
  int c;
};

int main(){
	
	int a = sizeof(AA); //16  字节对齐.
	cout << a << endl;
  int vec[5] = {1,5,2,7,9};
  //selectionSort(vec, 5);
  insertionSort(vec, 5);
  for (int i : vec) {
    cout << i << endl;
  }
  /**
  mergeSort(vec, 0, 4);
  int a = factory2(5);
  cout << a << endl;
  int b = fib2(5);
  cout << b << endl;
  */
  return 0;
}

