/*************************************************************************
    > File Name: dp_integerbreak.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  6/ 4 12:29:25 2020
 ************************************************************************/

#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

//*************************************
//最优子结构：通过求解子问题的最优解，可以获得原问题的最优解.
//*************************************

/**
题目：将一个整数分割成n个(n>=2)个数字之和，求这个n个数字之和最大的乘积是多少.
本质思想：动态规划 - 将求解总问题的最优解转换为求解子问题的最优解.
分析方式：该问题在分解为子问题的过程中，发现有很多重叠问题，因此可用递归求解，进而可转换为记忆搜索+动态规划的方式求解.
*/

class Solution {
private:
  int max3(int a, int b, int c) {
    return max(a, max(b, c));
  }
  //方法一：仅仅用递归.
  int _integerBreak(int n) {
    if (n == 1)
      return 1;
    int res = -1;
    for (int i = 1; i <= n-1; i++) 
      //res = max(res, i * _integerBreak(n-i)); //还没想清楚为什么要加个i*(n-i)
      //这里有个陷阱：因为_integerBreak(int n)函数的功能是把n分割为至少两个数字，但是实际在递归的时候，必须得考虑该函数不继续分割了，而只分割成：i * (n-i).  传10 = 3 + 3 + 4可以验证.
      res = max3(res, i*(n-i), i * _integerBreak(n-i)); //求解最优子问题 继而 解得最优总问题的解.
    return res;
  }
  //方法二：动态规划 + 记忆搜索.
  int _integerBreakDp(int n) {
    vector<int> memo(n+1, -1);   //第0个元素 和 第n个元素，所以要开辟n+1个元素的空间.
    //自底向上
    memo[1] = 1;
    //求解memo[i] . 注意，不是求解memo[n]。也就是遍历求解2~n之间的memo[i].
    for (int i = 2; i <= n; i++) {
      //对i进行分割.
      for (int j = 1; j <= i-1; j++) {
        //i可以被分割为:j + (i-j)
        memo[i] = max3(memo[i], j*(i-j), j*memo[i-j]); //对j*(i-j)里的(i-j)进行继续分割的方法是:memo[i-j].
      }
    }
    return memo[n];
  }
public:
  int integerBreakRecursive(int n){
    assert(n > 1); //因为要至少分为两个数字(n >= 2).
    return _integerBreak(n);
  }
  int integerBreakDp(int n){
    assert(n > 1); //因为要至少分为两个数字(n >= 2).
    return _integerBreakDp(n);
  }
};

int main(){
  Solution s;
  //方法一：
  int res1 = s.integerBreakRecursive(10);
  cout << res1 << endl;
  //方法二：
  int res2 = s.integerBreakDp(2);
  cout << res2 << endl;
  return 0;
}

