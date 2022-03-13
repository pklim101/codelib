/*************************************************************************
    > File Name: SortTestHelper.h
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  3/29 12:04:23 2020
 ************************************************************************/
#ifndef SortTestHelper_H
#define SortTestHelper_H

#include<iostream>
#include<ctime>  //time(NULL),clock()
#include<cassert>

using namespace std;

namespace SortTestHelper{
  //生成有n个元素的随数组，每个元素的取值范围为[rangeL,rangeR]
  int* generateRandomArray(int n, int rangeL, int rangeR) {
    assert(rangeL <= rangeR);
    int* arr = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
      arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;//加上rangeL个偏移.
    }
    return arr;
  }

  int* generateRandomNearlyOrderedArray(int n, int randomTimes) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
      arr[i] = i;
    }
    srand(time(NULL));
    for (int j = 0; j < randomTimes; j++) {
      int randx = rand() % n;
      int randy = rand() % n;
      arr[randx] = arr[randy];
    }
    return arr;
  }
  
  template<typename T>
  void printArray(T arr[], int n){
    for (int i = 0; i < 10; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }

  //验证是否已经排序已经排序是否正确.
  template<typename T>
  bool isSorted(T arr[], int n) {
    for (int i = 0; i < n-1; i++) {
      if (arr[i] > arr[i+1]) {
        return false;
      }
    }
    return true;
  }

  /**
  void(*sort)(T[], int): 是函数指针；
  typedef long clock_t;
  clock(): 时钟周期，表示从程序启动到运行到调用clock()处用了多少个时钟周期；
  时钟周期 = 1/震荡频率, 是计算机CPU运行的最小时间单元;
  CLOCKS_PER_SEC: 每秒有多少个时钟周期.
  */
  template<typename T>
  void testSort(string sortName, void(*sort)(T[], int), T arr[], int n){
    clock_t startTime = clock();
    sort(arr, n);
    clock_t endTime = clock();

    assert( isSorted(arr, n) );
    cout << sortName << ":" << double(endTime - startTime) / CLOCKS_PER_SEC << endl;
  }

  //拷贝一个整形数组
  int* copyIntArray(int arr[], int n){
    int* a = new int[n];
    copy(arr, arr+n, a);
    return a;
  }
}

#endif

