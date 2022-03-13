/*************************************************************************
    > File Name: xor.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  2/20 19:06:08 2022
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
      if (nums.size() == 0) {
        return -1; 
      }
      int num = 0;
      for (int i : nums) {
        num ^= i; 
      }
      return num;
    }
};

int main() {
  vector<int> nums = {1,2,1,6,6,9,8,8,9};
  Solution s;
  int num = s.singleNumber(nums);
  cout << num << endl;
  return 0;
}

