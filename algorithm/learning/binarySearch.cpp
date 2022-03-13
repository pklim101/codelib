/*************************************************************************
    > File Name: selectionSort.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  3/28 12:11:01 2020
 ************************************************************************/

#include<iostream>
#include "SortTestHelper.h"
using namespace std;

/** 二分查找法
前提: 是一个有序的数组.
实现步骤:
  1. 定义好查找的区间:前闭后闭arr[l...r];
  2. 取中间值:mid = (r+l)/2;
  3. while循环判断是否找完了:while(l<=r);
  4. 每次循环判断的时候，看:
    a. 是否已经找到; 
    b. 否则小于中间值则从左边找; 
    c. 否则大于中间值就从右边找.
二分查找法容易出现的BUG:
  求中间值的时候容易出现溢出:mid=(l+r)/2,如果l和r是非常大的值，则相加后会溢出.
  解决办法: 利用差值进行偏移. mid=l+(r-l)/2.
*/

//在有序数组arr[l...r]中查找数字target,如果查找到返回其索引,如果没查找到返回-1.
template<typename T>
int binarySearch(T arr[], int n, T target) {
  //定义清楚查找的区间:前闭后闭[l,r]
  int l = 0, r = n-1;
  while (l <= r) {
    //int mid = (l+r)/2;
    int mid = l+(r-l)/2;
    if (arr[mid] == target) {
      return mid;
    }
    if (target < arr[mid]) {
      r = mid-1;  //因为上面索引为mid的位置没有查找到，所以这里应该为r = mid-1而不是为r = mid
    } else {
      l = mid+1; //+1原因同上.
    }
  }
  //循环完成，说明没有找到.
  return -1;
}

/**递归实现二分查找法
递归优点: 实现起来，思维更容易，因为只需考虑子过程和递归结束条件.
递归缺点: 性能略差，但是是常数级的.
*/

//递归函数:即考虑该子过程即可.
template<typename T>
int binarySearchRecursion_(T arr[], int l, int r, int target) {
  if (l>r) {
    return -1;
  }
  int mid = l+(r-l)/2;
  if (target == arr[mid]) {
    return mid;
  }
  if (target < arr[mid]) {
    r = mid-1;
    binarySearchRecursion_(arr, l, r, target);
  } else {
    l = mid+1;
    binarySearchRecursion_(arr, l, r, target);
  }
  return -1;
}
template<typename T>
int binarySearchRecursion(T arr[], int n, int target) {
  int l = 0, r = n-1;
  return binarySearchRecursion_(arr, l, r, target);
}

int main(){
  int n = 10;
  int* arr = SortTestHelper::generateRandomArray(n,0,n);
  //SortTestHelper::printArray(arr, 10);
  int arr2[] = {1,3,5,7,9};
  int target = binarySearch(arr2, 5, 3);
  cout << "none-recursion:" << target << endl;
  int target2 = binarySearch(arr2, 5, 3);
  cout << "recursion:" << target2 << endl;


  delete[] arr;
  return 0;
}

