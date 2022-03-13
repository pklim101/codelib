/*************************************************************************
    > File Name: dp_break_integer1.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  7/25 13:57:47 2020
 ************************************************************************/

#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

/**
将一个数分割成至少2个数之和，求这些数的最大积。
关键：遍历所有组合=>一种是继续拆分，另外一个是不继续拆分，以此保证能把所有组合遍历到.
方法：
1. 递归；
2. 动态规划 + 记忆化搜索.
*/

class Solution {
public:
  int recursive(int n){
    assert(n > 1); 
    return _recursive(n);
  }
  int dp(int n){
    assert(n > 1);
    return _dp(10);
  }
private:
  int max3(int a, int b, int c){
    return max(a, max(b, c));
  }
  //int res = 0;
  int _recursive(int n) {
    int res = -1; //每次递归都初始化为-1.
    for (int i = 1; i < n-1; i++) {
      res = max3(res, i*(n-i), i*_recursive(n-i));
    }
    return res;
  }
  int _dp(int n){
    vector<int> memo(n+1, -1);
    //1. 求解memo[i];
    for (int i = 2; i <=n ; i++) {
      //2. 对i分割.
      for (int j = 1; j <= i-1; j++) {
        memo[i] = max3(memo[i], j*(i-j), j*memo[i-j]);  //非递归，不要总想着递归.
      }
    }
    return memo[n];
  }
};

int main(){
  Solution s;
  int res = s.recursive(10);
  cout << res << endl;
  res = s.dp(10);
  cout << res << endl;
  return 0;
}
