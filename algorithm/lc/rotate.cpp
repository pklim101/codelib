/*************************************************************************
    > File Name: rotate.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  4/12 16:46:55 2020
 ************************************************************************/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void rotate(vector<int>& nums, int k){
  if(nums.size()<2)  return;
  queue<int> q;
  for(int i=nums.size()-1; i >=0 ; i--){
    q.push(nums[i]); 
  }
  for(int i=0; i < k; i++){
    q.push(q.front());
    q.pop();
  }
  int i = nums.size();

  while(!q.empty()){
    cout << q.front() << endl;
    nums[i-1] = q.front();
    q.pop();
    i--;
  }
}

int main(){
  int arr[] {1,2};
  vector<int> nums(arr,arr+2);
  int k = 1;
  rotate(nums, k);
  for(int i : nums){
    cout << "result:" << i << endl;
  }

  return 0;
}
