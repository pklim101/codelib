/*************************************************************************
    > File Name: dp_integerbreak2.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  6/ 4 16:42:13 2020
 ************************************************************************/

#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

/**
题目：将一个正整数n分割成至少两个数，求乘积最大是多少.
思考方式：开始一看题目，无从下手，因为分割的方式非常多。静下来捋一捋，其实就是一个树形问题。
          再仔细捋一捋，可以将该问题的最优解转为求子问题的最优解：因为1.有重复子过程；2.子问题存在最优解.
解题方法：
一、递归；关键点：分割一个数 + 遍历递归分割这个数的最优解.
二：动态规划 + 记忆搜索. 关键点：自底向上，求出memo[1~n]，求导最后memo[n]就是结果.
*/

class Solution {
private:
  int max3(int a, int b, int c) {
    return max(a, max(b, c));
  }
  int _integerBreakRecursive(int n) {
    //1.终结
    if (n == 1)
      return 1;
    int res = -1;
    //遍历要分割的数
    for (int i = 2; i < n-1; i++) 
      //求 i + (n-i)
      res = max3(res, i * (n-i), i * integerBreakRecursive(n-i)); //将总问题的最优解转换为求子问题的最优解.
    return res;
  }

public:
  int integerBreakRecursive(int n){
    return _integerBreakRecursive(n); 
  }
  int integerBreakDp(int n) {
    assert(n > 1);
    //1. 开辟n+1个空间,因为第0个元素和第n个元素都需要空间,所以是n+1.
    vector<int> memo(n+1, -1);
    //2.求出最底层的子问题最优解.
    memo[1] = 1;
    //3.遍历2~n，求出每个子问题的最优解memo[2~n].
    for (int i = 2; i <= n; i ++) {
      //4. 求memo[i]子问题:对每个i进行分割：j + (i-j).
      for (int j = 1; j <= i-1; j ++) {
        //5.从子问题从找到最优解.
        memo[i] = max3(memo[i], j * (i-j), j * memo[i-j]);  //突然想到：等号后的memo[i]怎么来的? => 就是默认值-1。
      }
    }
    return memo[n];
  }

};


int main(){
  Solution s;
  int res1 = s.integerBreakRecursive(10);
  cout << res1 << endl;
  int res2 = s.integerBreakDp(2);
  cout << res2 << endl;
  return 0;
}
