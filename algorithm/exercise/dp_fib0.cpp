/*************************************************************************
    > File Name: dp_fib.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 二  7/21 11:17:15 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;
/**
动态规划：把大问题分解成一个个小问题，小问题解决了，大问题也就解决了。
求解斐波拉契数列的三种方法：
1. 递归；
2. 递归 + 缓存；
3. 动态规划（其实里面也包含缓存）；
*/

//方法一：递归：从最大递归到最小，然后返回来的时候就求解出来了。
int fib_recursive(int n){
  if (n == 0) 
    return 1;
  if (n == 1) 
    return 1;
  /** warning: control may reach end of non-void function [-Wreturn-type]
  if (n > 1) 
    return fib_recursive(n-1) + fib_recursive(n-2);
  */
  return fib_recursive(n-1) + fib_recursive(n-2);
}

//方法二：递归 + 缓存
//缓存：先将数组每个值初始化为-1.  然后存值。
//vector<int> memo(5, -1);
vector<int> memo(5+1, -1);
int fib_recursive_cache(int n) {
  if (n == 0)
    return 1;
  if (n == 1)
    return 1;
  if (memo[n] == -1)
    memo[n] = fib_recursive_cache(n-1) + fib_recursive_cache(n-2);
  return memo[n];
}

//动态规划
//自底向上求解.
vector<int> memo2(5+1, -1);
int fib_dp(int n) {
  memo2[0] = 1;
  memo2[1] = 1;
  for (int i = 2; i <=n; i++) {
    if (memo2[i] == -1) memo2[i] = memo2[i-1] + memo2[i-2];
  }
  return memo2[n];
}

int main(){
  int res = fib_recursive(5);
  cout << res << endl;

  res = fib_recursive_cache(5);
  cout << res << endl;

  res = fib_dp(5);
  cout << res << endl;
  return 0;
}


