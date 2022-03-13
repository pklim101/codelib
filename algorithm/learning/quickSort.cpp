/*************************************************************************
    > File Name: quickSort.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  3/28 12:11:01 2020
 ************************************************************************/

#include<iostream>
#include "SortTestHelper.h"
using namespace std;

// 快速排序：核心思想：子过程采用partition排序. 对左右两部分进行依次递归.
/** partition思路：
  元素: l:arr最左侧元素,r:arr最右侧元素, j:元素v应该在的索引位置.
  step 1. 选择一个partition分区比较的元素，一般选第一个元素，设为v;
  step 2. 当前元素a[i] > v 时，i++;
          当前元素a[i] < v 时, swap(arr[i], arr[j+1]), j++;
  step 3. 遍历排完左右两边后，swap(arr[l],arr[j]);
  step 4. 返回v元素在一次partition后应该在的索引位置,用于下一次递归中partition的v.
*/

template<typename T>
int partition_(T arr[], int l, int r) {
  T v = arr[l];

  int j = l;
  //遍历[l+1,r]，将所有遍历的元素比v小的放左边，比v大的放右边.
  for (int i=l+1; i <= r; i++) {
    if (arr[i] < v) {  //注意：这里是小于的时候才替换，大于的时候就不用替换了.
      swap(arr[i], arr[j+1]);
      j++;
    }
  }
  swap(arr[l], arr[j]); //注意：是把左边第一个元素和第j个元素交换.
  return j;
}

template<typename T>
void partitionSort_(T arr[], int l, int r) {
  if (l >= r) {
    return;   //递归结束
  } 

  //每次递归找到patition中区分左右两边的元素位置p，也就是函数partition_返回的j.
  int p = partition_(arr, l, r);
  partitionSort_(arr, l, p-1); //左边部分递归
  partitionSort_(arr, p+1, r); //右边部分递归
}

template<typename T>
void partitionSort(T arr[], int n) {
  partitionSort_(arr, 0, n-1);
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
  ///SortTestHelper::printArray(arr, n);

  int* nearArr = SortTestHelper::generateRandomNearlyOrderedArray(n, 10);

  int* arr2 = SortTestHelper::copyIntArray(arr,n);
  int* arr3 = SortTestHelper::copyIntArray(arr,n);
  SortTestHelper::testSort("insertionSort", insertionSort, arr2, n);
  SortTestHelper::testSort("insertionSortAdvanced", insertionSortAdvanced, arr3, n);
  SortTestHelper::testSort("insertionSortAdvancedNear", insertionSortAdvanced, nearArr, n);
  SortTestHelper::testSort("partitionSort", partitionSort, arr, n);

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

