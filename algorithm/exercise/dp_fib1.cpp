/*************************************************************************
    > File Name: db_fib1.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  7/25 13:11:30 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
求斐波拉契数列--爬楼梯。
三种方法：
1. 递归；
2. 递归 + 记忆化搜索；
3. 动态规划 + 记忆化搜索。
*/

//递归求解：自顶向下递归求解。

int _recursive(int n) {
  if (n == 0) return 1;
  if (n == 1) return 1;
  return _recursive(n-1) + _recursive(n-2);
}
int recursive(int n){
   return _recursive(n); 
}

//递归 + 记忆化搜索
vector<int> memo(5+1, -1);
int _recursive_catch(int n) {
  if (n == 0) return 1;
  if (n == 1) return 1;
  if (memo[n] == -1) memo[n] = _recursive_catch(n-1) + _recursive_catch(n-2); 
  return memo[n];
}
int recursive_catch(int n) {
  return _recursive_catch(n);
}

//动态规划 + 记忆化搜索
//动态规划：将大问题分解成小问题，自底向上求解，小问题都求解完成后大问题就解决出来了。
vector<int> memo2(5+1, -1);
int _dp(int n){
  memo2[0] = 1;
  memo2[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (memo2[i] == -1) memo2[i] = memo2[i-1] + memo2[i-2];
  }
  return memo2[n];
}
int dp(int n){
  return _dp(n);
}

int main(){
  int res = recursive(5);
  cout << res << endl;
  res = recursive_catch(5);
  cout << res << endl;
  res = dp(5);
  cout << res << endl;
  return 0;
}
