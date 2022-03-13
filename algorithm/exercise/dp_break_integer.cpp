/*************************************************************************
    > File Name: dp_break_integer.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 二  7/21 15:48:18 2020
 ************************************************************************/

#include<iostream>
using namespace std;

/**
将n分割成至少两个数之和，求分割的这些数的最大乘积.
方法一：递归+缓存.  利用最优子结构的思想，自顶向下求解.
方法二：动态规划. 自底向上求解.
*/

class Solution {
public:
  int recursive(int n){
    assert(n>=2);
    vector<int> memo(n+1, -1);
    _recursive(n);
  }
  int dp(int n){
    assert(n>=2);
    vector<int> memo(n+1, -1);
    _dp(n);
  }
private:
  int _recursive(int n){
    int res = -1;
    for (int i = 1; i <= n-1; i++) {
      return max3(res, i*(n-i), i*_recursive(n-1));
    }  
  }
};
int main(){
  return 0;
}
