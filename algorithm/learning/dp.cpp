/*************************************************************************
    > File Name: dp.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  6/ 4 00:01:28 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
题目：爬梯子，每次只能爬一个台阶或两个台阶，总共有多少种爬法。
其实本质上是斐波拉契数列.
解决方法：
1. 递归；
2. 递归 + 缓存;
3. 动态规划：从分解的最小子问题，自底向上求解，最后求解出总问题.
*/


int recursive(int n) {
  if (n == 0)
    return 1;  //一个台阶都没有，只有一种走法：也就是说：没得走就是一种走法.
  if (n == 1)  
    return 1;  //只有一个台阶：那肯定只有一种走法.
  return recursive(n-1) + recursive(n-2);
}

// 递归 + 缓存memo
// 记忆化搜索.
int recursive_cache(int n,vector<int>& memo){
  if (n == 1)
    return 1;
  if (n == 2)
    return 2;
  if (memo[n] == -1)
    memo[n] = recursive_cache(n-1, memo) + recursive_cache(n-2, memo);
  return memo[n]; 
}

//动态规划
vector<int> memo(5+1, -1);
int dp(int n){
  memo[0] = 1;
  memo[1] = 1;
  for (int i = 2; i <= n; i++) {
    memo[i] = memo[i-1] + memo[i-2];
  }
  return memo[n];
}
int main(){
  int res1 = recursive(5);
  cout << res1 << endl;

  vector<int> memo(5+1, -1);
  int res2 = recursive_cache(5, memo);
  cout << res2 << endl;
  
  int res3 = dp(5);
  cout << res3 << endl;
  return 0;
}
