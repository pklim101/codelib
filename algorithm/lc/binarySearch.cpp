/*************************************************************************
    > File Name: binarySearch.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月03日 星期三 15时51分40秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
二分搜索
找到返回index，找不到则返回-1.
*/

//递归方式查找.
int _binarySearch (vector<int>& vec, int val, int l, int r) {
  //1.终止条件
  if (l > r) {
    return -1;
  }
  //2.当层处理
  int mid = (l + r)/2;
  if (val == vec[mid])
    return mid;
  else if (val < vec[mid])
    //3.下探到下一层.
    _binarySearch(vec, val, l, mid-1);
  else
    _binarySearch(vec, val, mid+1, r);
}

//while方式
int _binarySearch2 (vector<int>& vec, int val, int l, int r) {
  while (l <= r) {
    int mid = l + (r-l)/2;
    
    if (vec[mid] == val)
      return mid;
    else if (val < vec[mid])
      r = mid-1;
    else 
      l = mid+1;
  }
  return -1;
}

int main(){
  vector<int> vec = {1,2,5,7,10,12,20};
  int res = _binarySearch2(vec, 10, 0, vec.size()-1);
  cout << res << endl;
  return 0;
}
