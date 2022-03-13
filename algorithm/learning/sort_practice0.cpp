/*************************************************************************
    > File Name: sort_practice0.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  7/18 14:32:42 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
快排：1. partition； 2. 左右递归继续partition排序.
 */


int _partition(vector<int>& vec, int l, int r){
  int pivot = 0;
  for (int i = l+1; i <= r; i++) {
    if (vec[i] < vec[pivot])  
      swap(vec[i], vec[pivot]);
      pivot++;
  }
  return pivot;
}

void _quick(vector<int>& vec, int l, int r){
  if (l >= r) 
    return;
  int mid = _partition(vec, l, r);
  _quick(vec, l, mid-1);
  _quick(vec, mid+1, r);
}
void quickSort(vector<int>& vec){
  _quick(vec, 0, vec.size());
}

/**
归并排序：1.左右递归拆分，2.比较合并.
*/
//对[l,r]区间的数据进行merge.
void _merge(vector<int>& vec, int l, int mid, int r) {
  int len = r-l+1;
  int aux[len];
  for (int i = l; i <= r; i++) aux[i-l] = vec[i];
  int i = l;
  int j = mid+1;
  for (int k = l; k <= r; k++) {  //这个循环总忘记:要遍历整个[l,r]区间
    if (i > mid) {
      vec[k] = aux[j-l];
      j++;
    } else if (j > r) {
      vec[k] = aux[i-l];
      i++;
    //} else if (aux[i] < aux[j]) {
    } else if (aux[i-l] < aux[j-l]) {
      vec[k] = aux[i-l];
      i++;
    } else {
      vec[k] = aux[j-l];
      j++;
    }
  }
}
void _mergeSort(vector<int>& vec, int l, int r){
  if (l >= r) return;
  int mid = l+(r-l)/2;
  _mergeSort(vec, l, mid);
  _mergeSort(vec, mid+1, r);
  _merge(vec, l, mid ,r);
}
void mergeSort(vector<int>& vec) {
  _mergeSort(vec, 0, vec.size()-1);
}

int main(){
  vector<int> vec = {5,2,8,1,6};
  //quickSort(vec);
  mergeSort(vec);
  for (auto i : vec) printf("%d,", i);
  return 0;
}
