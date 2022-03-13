/*************************************************************************
    > File Name: sort_exercise1.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  7/19 16:14:54 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
  冒泡排序：N*N的双层遍历，O(N^2).
  核心思想：内层遍历的时候，每遍历一次就找出一个最大值放到最右边.
*/
void bubleSort(vector<int>& vec){
  for (int i = 0; i < vec.size(); i ++) {
    for (int j = 0; j < vec.size()-i-1; j++) {
      if (vec[j] > vec[j+1]) swap(vec[j], vec[j+1]);
    }
  }
}

/**
  选择排序:每次遍历都选择最小值的索引与未排序部分的第一个元素交换..
  注意：冒泡和选择排序，都是每次遍历选择最小值/最大值，但是冒泡是判断了大小就交换，而选择排序是记录最小值索引，遍历完再交换.
*/
void selectionSort(vector<int>& vec){
  for (int i = 0; i < vec.size(); i++) {
    //int minIndex = 0;
    int minIndex = i;
    for (int j = i+1; j < vec.size(); j++) {
      if (vec[minIndex] > vec[j])
        minIndex = j;
    }
    swap(vec[minIndex], vec[i]);
  }
}

/**
  插入排序：每次遍历，都将选择的元素插入到前面排序好的合适的位置.
*/
void insertionSort(vector<int>& vec) {
  for (int i = 1; i < vec.size(); i ++) {
    for (int j = i; j > 0; j--) {
      if (vec[j] < vec[j-1]) {
        swap(vec[j], vec[j-1]);
      } else {
        break;
      }
    }
  }
}

/**
快速排序： 1. partition  2. 递归左右拆分.
核心思想：用递归的方式，左右分别partition排序，以分治的思想排序. nlog(n).
因为分治，所以快速.
*/
//对[l,r]区间的数做partion排序.
int _partition(vector<int>& vec, int l, int r){
  //int p = 0;
  int p = l;  //注意：都是从当前区间[l,r]的第一个元素作为pivot.
  for (int i = l+1; i <=r; i++) {
    if (vec[p] > vec[i]) {
      swap(vec[p], vec[i]);
      p++; //交换后，p这个游标也跟着指向pivot了，所以p总是指向pivot这个游标.
    }
  }
  return p;
}
void _quick(vector<int>& vec, int l, int r){
  if (l >= r)
    return;
  int p = _partition(vec, l, r);
  _quick(vec, l, p-1); //注意：p已经排好序了，所以得是p-1，不能是p.
  _quick(vec, p+1, r);
}
void quickSort(vector<int>& vec) {
  _quick(vec, 0, vec.size()-1);
}

/**
归并：1. 左右递归拆，2.左右比较merge.
核心思想：分治，先左右往下拆完，最后一次往上合并排序；
*/
void _merge(vector<int>& vec, int l, int mid, int r){
  int aux[r-l+1];
  for (int i = l; i <= r; i++) aux[i-l] = vec[i];
  int i = l;
  int j = mid+1;
  for (int k = l; k <= r; k++) { //:重要：遍历[l,r]
    if (i > mid) {
      vec[k] = aux[j-l];
      j++;
    } else if (j > r) {
      vec[k] = aux[i-l];
      i++;
    } else if (aux[i] < aux[j]) {
      vec[k] = aux[i-l];
      i++;
    } else {
      vec[k] = aux[j-l];
      j++;
    }
  }
}
void _mergeSort(vector<int>& vec, int l, int r){
  if (l>=r) return;
  int mid = l+(r-l)/2;
  _mergeSort(vec, l, mid);
  _mergeSort(vec, mid+1, r);
  _merge(vec, l, mid, r);
}
void mergeSort(vector<int>& vec){
  _mergeSort(vec, 0, vec.size()-1); 
}

int main(){
  vector<int> vec = {5,2,8,1,6};
  //vector<int> vec = {5,1,3,2,6};
  //quickSort(vec);
  //mergeSort(vec);
  //bubleSort(vec);
  //selectionSort(vec);
  insertionSort(vec);
  for (int i : vec) printf("%d,", i);
  return 0;
}
