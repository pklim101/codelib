/*************************************************************************
    > File Name: maxSubseqSum.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  7/23 21:49:51 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;
/**
求一个无序数组的子序列的最大和.
贪心算法：假定第一个元素为最大值，然后依次遍历元素的同时依次累加，
*/


//贪心算法
int foo(vector<int>& vec){
  int max = vec[0];
  int curSum = vec[0];
  for (int i = 1; i < vec.size(); i++) {
    curSum = curSum + vec[i] > vec[i] ? curSum + vec[i] : vec[i];
    max = std::max(max, curSum);
  }
  return max;
}
int main(){
  vector<int> vec = {-2,1,-3,4,-1,2,1,-5,4}; //结果： [4,-1,2,1]， 和为6.
  int res = foo(vec);
  cout << res << endl;
  return 0;
}
