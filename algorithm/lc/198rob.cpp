/*************************************************************************
    > File Name: 198rob.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  6/ 6 14:16:22 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
题目：打家劫舍. 每个房子有不同价值的物品，打劫相邻的两个房子会触发报警.求如何才能打劫到最多的财务.
分析：是树形问题. 1. 有重复子结构:可以考虑递归; 2. 有最优子问题:可以考虑动态规划; 3. 因为有重复最优子问题，所以可以考虑记忆化搜索.
*/

class Solution {
private:
  vector<int> memo;
  //递归自顶向下求解：O(2^n)
	//考虑打劫[index~nums.size)个房子获得最优解.
	int _rob(vector<int>& nums, int index) {
		if (index >= nums.size())
			return 0;
    if (memo[index] != -1)
      return memo[index];
		int res = 0; //每打劫一个房子后获得的最优解.
		for (int i = index; i < nums.size(); i++) {
			//res = max(res, i + _rob(nums, i));	 //错了，注意，很容易混淆.
			res = max(res, nums[i] + _rob(nums, i+2));	//为什么是+2呢？因为得隔一个房子.
		}
    memo[index] = res;
		return res;
	}	
  //动态规划自底向上求解: O(n^2)
  int _rob2(vector<int>& nums, int index){
    int n = nums.size();
    //memo[i]表示考虑抢劫[index,n-1]区间的房子所能获得的最大收益.
    memo[n-1] = nums[n-1]; //抢劫第n-1个房子.也就是只有一个房子可抢劫.
    for (int i = n-2; i >=0; i--) {
      //求memo[i]：即考虑从i到n-1个房子的最大收益.
      for (int j = i; j <= n-1; j++) {
        memo[i] = max(memo[i], nums[j]+ (j+2<n ? memo[j+2] : 0)); //状态转移方程.
      }
    }
    return memo[0];
  }
public:
	int rob(vector<int>& nums) {
  memo = vector<int>(nums.size(), -1);
		if (nums.size() == 0)
			return 0;
		return _rob2(nums, 0);
	}
};

int main(){
	vector<int> vec = {1,2,3,1};
	Solution sl;
	int res = sl.rob(vec);
	cout << res << endl;
  return 0;
}
