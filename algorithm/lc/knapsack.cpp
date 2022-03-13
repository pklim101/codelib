/*************************************************************************
    > File Name: knapsack.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月10日 星期三 17时01分17秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

/**
0-1背包问题:

给定n个重量为w1,w2,w3,…,wn，价值为v1,v2,v3,…,vn的物品和容量为C的背包，求这个物品中一个最有价值的子集，使得在满足背包的容量的前提下，包内的总价值最大.

0-1背包问题指的是每个物品只能使用一次

暴力遍历解法的时间复杂度: O(n * 2^n).

分析：因为每个物品可以取或者不取，从而可以抽象出这是一个具有：1.重复子问题，2.最优重复子结构 的问题，
      所以可以考虑用递归或者动态规划做，同时因为有重复子问题，所以可以用记忆搜索.

思路：
  1. 抽象出状态函数：
  F(i-1, c): 表示考虑从前i-1个物品中取(不确定取多少个), 且当前背包容量是c；
  2. 抽象出状态转移函数：
  因为：第i个物品可以有两种情况：
  装入：F(i-1, c);
  不装入：v(i) + F(i-1, c-w(i));
  所以：F(n, C) = max(F(i-1, c), v(i) + F(i-1, c-w(i)));  //这里就是相当于求解左右子树哪个子树结果更大.
*/

class Solution {
private:
		//记忆搜索
		vector<vector<int>> memo;
/**
 *  解决背包问题的递归函数
 *  @param w 所有物品的重量 
 *  @param v 所有物品的价值 
 *  @param index 考虑的当前的第几(index)个物品 
 *  @param C 当前背包的总容量(注意：这里不是当前背包的剩余容量，如果理解不了，就像想填表的过程)
 */
  int _maxValue(vector<int>& w, vector<int>& v, int index, int c) {
    //1.终止条件
    if (c <=0 || index <=0) 
      return 0;
    //2.当前层处理
    
    //3.下探到下一层
    //不放第index个物品
		if (memo[index-1][c] != -1) 
			return memo[index][c];
    int res = _maxValue(w, v, index-1, c); 
    //放第index个物品
    if (w[index] <= c)
      res = max(res, v[index]+_maxValue(w, v, index-1, c-w[index] ));
		memo[index-1][c] = res;
    return res;
  }
public:
	//递归+记忆搜索
  int knapsack(vector<int> w, vector<int> v, int C){
		for (int i=0; i < w.size(); i++) {
			memo.push_back(vector<int>(C+1, -1)); //背包容量从0到C依次递增1个单位容量.
		}
    return _maxValue(w, v, w.size(), C); 
  }

	//动态规划实现
	int knapsackDp(vector<int> w, vector<int> v, int C){
		assert(w.size() == w.size() && C >= 0);
		//初始化memo所有值.
		for (int i = 0; i < w.size(); i++) {
			memo.push_back(vector<int>(C+1, 0));
		}
		//动态规划自底向上求解.
		for (int i = 0; i < w.size(); i++) { //依次从第i个物品开始填表
			for (int j = 0) { //将第i个物品依次往容量为j的背包里放入.

			}
		}
	}

};

int main(){
  Solution sl;
	int warr[5] = { 0 , 2 , 3 , 4 , 5 };			//商品的体积2、3、4、5
	int varr[5] = { 0 , 3 , 4 , 5 , 6 };			//商品的价值3、4、5、6
	vector<int> w(warr, warr+5);
	vector<int> v(varr, varr+5);
	int C = 8;	

  int res = sl.knapsack(w, v, C);
	cout << res << endl;
	for (int i : warr) {
		cout << i << endl;
	}
  return 0;
}
