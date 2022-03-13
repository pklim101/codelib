/*************************************************************************
    > File Name: quickSort.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月18日 星期四 10时05分30秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<unistd.h>
using namespace std;


/**
冒泡排序：内层循环两两比较.
  遍历N次，每次遍历后最大值在最右边.
  时间复杂度O(N^2)
  关键点：每扫一遍的过程中，两两交换，如果前者大于后者，则交换.
*/

void bubbleSort(vector<int>& vec) {
  int len = vec.size();
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len-1-i; j++) {  //注意这里1.不要越界，2.不要做多余重复运算;
      if (vec[j] > vec[j+1])
        swap(vec[j], vec[j+1]);
    }
  }
}


/**
选择排序: 选择最小值的索引
  遍历N次，每次选出最小/最大值.
  时间复杂度O(N^2)
  关键点：每扫一遍的时候记住最小值的索引位置，扫完后将最小值和前面的位置调换.
*/

void selectionSort(vector<int>& vec) {
  int len = vec.size();
  for (int i = 0; i < len; i++) {
    //寻找[i,n)区间里的最小值.
    int minIndex = i;
    for (int j = i+1; j < len; j++) {
      if (vec[maxIndex] > vec[j]) 
        minIndex = j;
    }
    swap(vec[minIndex], vec[i]);
  } 
}

/**
插入排序：找到合适插入点.
  遍历N次已排好序的序列，找到合适的插入点.
  时间复杂度O(N^2)
  关键点：取未排序的元素到前面已经排序好的序列里找到合适的插入点.
*/
void insertionSort(vector<int>& vec){
  int len = vec.size();
  for (int i = 1; i < len; i++) {
    for (int j = i; j > 0; j--) {
      if (vec[j] < vec[j-1])
        swap(vec[j], vec[j-1]);
      else
        break; // 避免多余的比较运算.
    }
  }
}

/**
快速排序
  分治思想，partition排序.
  时间复杂度:O(NlogN)
  关键点：用j跟踪比pivot小的个数，用比pivot小的元素swap比pivot大的元素.
*/
int _partition(vector<int>& vec, int l, int r){
  int v = vec[l]; 
  int j = l; 
  for (int i = l+1; i <= r; i++) {
    if (vec[i] < v) {
      j++;
      swap(vec[i], vec[j]); //巧妙处：用j跟踪比pivot小的元素个数，用小的元素swap大的元素.
    }
  }
  swap(vec[l], vec[j]);
  return j;
}

//对[l,r]部分进行排序
void _quickSort(vector<int>& vec, int l, int r){
  //1. 终止条件
  sleep(1);
  //注意：1.当有三个有序元素的时候(如1,2,3)，p则为0，也就是j没移动,这时候算得l=0,r=p-1=-1，所以要用大于.
  //      2.当有两个有序元素(如4,5)，则p为0，也就是J没移动,这时候算得l=4,r=p-1=3,所以要用大于
  //     总之:分区有序，则p为0，则左边分区里l>r.
  if (l >= r) 
    return ;
  //2. 下探到下一层.
  int p = _partition(vec, l, r);
  _quickSort(vec, l, p-1);
  _quickSort(vec, p+1, r);
}

void quickSort(vector<int>& vec) {
  _quickSort(vec, 0, vec.size()-1);
}

/**
归并排序
  分治思想，先拆分，最后merge.
  时间复杂度：O(NlogN)
  关键点：如何拆--递归调用就是拆，如何merge--左右分区比较后放入原数组.
*/
//对[l,r]部分进行归并
void _merge(vector<int>& vec, int l, int mid, int r) {
  vector<int> aux(r-l+1);
  for (int i = l; i <= r; i++) {
    //aux.push_back(vec[i]);
    aux[i-l] = vec[i];
  }
  
  //i指向左半部分的索引起始位置l，j指向右半部分的索引起始位置mid+1.
  int i = l;
  int j = mid+1;
  for (int k = l; k <= r; k++) { //注意：遍历k[l,rl.
    if (i > mid) {
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

//对[l, r]部分排序
void _mergeSort(vector<int>& vec, int l, int r) {
  if (l >= r)
    return;
  int mid = l + (r-l)/2;
  _mergeSort(vec, l, mid);
  _mergeSort(vec, mid+1, r);
    //cout << l << "====== "<< mid << "========" << r << endl;
  _merge(vec, l, mid, r);
}
void mergeSort(vector<int>& vec){
  _mergeSort(vec, 0, vec.size()-1);
}

int main(){
  vector<int> vec = {5,2,7,3,6,2};
  //bubbleSort(vec);
  //selectionSort(vec);
  //insertionSort(vec);
  //quickSort(vec);
  mergeSort(vec);
  for (int i : vec) {
    cout << i << endl;
  }
}
