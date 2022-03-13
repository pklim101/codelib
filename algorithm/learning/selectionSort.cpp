/*************************************************************************
    > File Name: selectionSort.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  3/28 12:11:01 2020
 ************************************************************************/

#include<iostream>
#include "SortTestHelper.h"
using namespace std;

// 选择排序：核心思想：遍历找(选择)最小值后和前面未排序部分第一个元素交换.
template<typename T>
void selectionSort(T arr[], int n) {
  for (int i = 0; i < n; i++) {
    //核心思想：寻找在[0,n)之间的最小值
    int minIndex = i; //假设每次找到的最小值的索引是minIndex.
    for (int j = i+1; j < n; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }
    //找完一遍后，将最小值交换未排序的最前面的位置
    swap(arr[i], arr[minIndex]);
  }
}

// 插入排序
// 核心思想：从后面未排序的元素中找到第i个元素在前面合适的插入位置.
template<typename T>
void insertionSort(T arr[], int n){
  for (int i = 1; i < n; i++) {
    for (int j = i; j > 0; j--) {
      if (arr[j] < arr[j-1]) {
        swap(arr[j],arr[j-1]);
      } else {
        break; //只要比前面排好序的以为大，则不用继续往前比较了.  相比选择排序，少了比较次数.
      } 
    } 
  }
}
// 插入排序-改进版
// 核心思想：找到第i个元素在前面合适的插入位置.
// 改进点: swap()操作需要有三次拷贝，耗费性能，改为一次赋值操作，性能更高.
// 相比选择排序的优点：1. 能提前结束遍历； 2. 将swap()改为一次赋值操作.
template<typename T>
void insertionSortAdvanced(T arr[], int n){
  for (int i = 1; i < n; i++) {
    T e = arr[i]; //拷贝一份当前要排的元素arr[i].
    int j; // j保存元素e应该插入的位置.
    for (j = i; j > 0 && arr[j-1] > e; j--) {
      arr[j] = arr[j-1];
    } 
    arr[j] = e;
  }
}

int main(){
  int n = 10000;
  int* arr = SortTestHelper::generateRandomArray(n,0,n);
  selectionSort(arr, 10);
  SortTestHelper::printArray(arr, 10);

  int* nearArr = SortTestHelper::generateRandomNearlyOrderedArray(n, 10);

  int* arr2 = SortTestHelper::copyIntArray(arr,n);
  int* arr3 = SortTestHelper::copyIntArray(arr,n);
  SortTestHelper::testSort("selectionSort", selectionSort, arr, n);
  SortTestHelper::testSort("insertionSort", insertionSort, arr2, n);
  SortTestHelper::testSort("insertionSortAdvanced", insertionSortAdvanced, arr3, n);
  SortTestHelper::testSort("insertionSortAdvancedNear", insertionSortAdvanced, nearArr, n);

  delete[] arr;
  delete[] arr2;
  delete[] arr3;
  delete[] nearArr;
  //如下代码因为没有break，所以会输出AB.
  int a = 20;
  switch(a/10) {
    case 2:
      cout << "A";
    case 1:
      cout << "B";
  }

  return 0;
}

