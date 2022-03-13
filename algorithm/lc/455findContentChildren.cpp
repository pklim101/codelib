/*************************************************************************
    > File Name: 455findContentChildren.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  6/ 6 00:14:53 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
题目：孩子与饼干的问题.
方法：贪心算法:总是先用最大的饼干去判断是否满足最贪心的孩子，如果不满足，则判断是否满足第二贪心的孩子.
greedy:贪心;
size:饼干大小.
*/
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
			//记得先倒序排序.
			sort(g.begin(), g.end(), greater<int>());
			sort(s.begin(), s.end(), greater<int>());
			int gi = 0;
			int si = 0;	
			int res = 0;
			while (gi < g.size() && si < s.size()) {
				//cout << gi << ":" << si << endl;
				if (s[si] >= g[gi]) {
					si++;
          gi++;
					res++;
				} else {
					gi++; //这里弄串了，弄成si了.
				}
			}
			return res;
    }
};

int main(){
	Solution sl;
	vector<int> g = {1,2,3};
	vector<int> s = {1,1};
	int res = sl.findContentChildren(g, s);
	cout << res << endl;
  return 0;
}

