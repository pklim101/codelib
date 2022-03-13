/*************************************************************************
    > File Name: isSubsequence.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  6/ 6 00:00:29 2020
 ************************************************************************/

#include<iostream>
using namespace std;

/**
题目：求s是否是t的子序列.
方法：贪心算法.
*/
class Solution {
public:
    bool isSubsequence(string s, string t) {
      if (s.empty() && s.empty())
        return true;
			int si = 0;
			int ti = 0;
			while (si <= s.size() && ti <= t.size()) {
				if (s[si] == t[ti])	{
					si++;
					ti++;
				} else {
					ti++;
				}
				if (si == s.size())
					return true;
			}
			return false;
    }
};

int main() {
	string s = "bef";
	string t = "abcfg";
	Solution sl;
	bool res = sl.isSubsequence(s, t);
	cout << res << endl;
	return 0;
}
