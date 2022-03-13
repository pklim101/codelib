/*************************************************************************
    > File Name: twoSum.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月17日 星期五 13时04分32秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
  map<int,int> tmp;
  for(int i = 0; i < nums.size(); i++){
    int e = target - nums[i];
    auto iter = tmp.find(e);
    if (iter != tmp.end()){
      return {i,iter->second};
    } else {
      tmp.insert(pair<int,int>(nums[i],i));
    }
  }
  return {NULL,NULL};
}

int main(){
  return 0;
}

