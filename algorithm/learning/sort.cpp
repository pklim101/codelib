/*************************************************************************
    > File Name: sort.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  6/ 4 17:17:13 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
各种排序算法：
1. 选择排序;
2. 插入排序;
3. 归并排序;
4. 快速排序;
*/

/**
归并排序：先一拆为二；再两两比较后合并.
核心思想:拆分后，每次合并的时候先比较，再合并. 每层中每两个元素只比较一次.
步骤：
1. 一分为二；
2. 左边搞，右边搞；
3. 两边搞完再合并. 合并的时候排序.
时间复杂度分析：因为有logN层，以及每层有n个元素需要比较，所以是O(nlogn).
*/
void merge(vector<int>& vec, int l, int mid, int r) {
  //1. 申请临时空间aux;
  vector<int> aux;
  aux.reserve(r-l+1);
  //2. 将vec里的[l,r]放到aux里;
  for (int i = l; i <= r; i++) {
   
  }
  //3. 依次比较左右两部分后，将小的放入vec中.
}

void sortMerge(vector<int>& vec, int l, int r) {
  if (l > r)
    return;
  int mid = l + (r-l)/2; 
  sortMerge(vec, l, mid);
  sortMerge(vec, mid, r);
  merge(vec, l, mid, r);
}

int main() {
  return 0;
}

