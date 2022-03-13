/*************************************************************************
    > File Name: binarySearchTarget.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 三  5/27 14:55:48 2020
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int __find(vector<int>& vec, int left, int right, int& target){
  int mid = (left + right)/2;
    
  if (left == right){
      int t1 = abs(vec[left]-target) < abs(vec[left+1]-target) ? left : left+1;
      int t2 = abs(vec[right]-target) < abs(vec[right-1]-target) ? right: right+1;
      cout << "t:" << t1 << "=>" << left << vec[left+1]<< endl;
			int t = t1 < t2 ? t1 : t2;
      return vec[t];
  }
	if ((right-left) == 1) {
      int t = abs(vec[left]-target) < abs(vec[right]-target) ? left : right;
      cout << "t---:" << t << "=>" << mid << endl;
      return vec[t];
	}
  
  if (target > vec[mid])
      return __find(vec, mid+1, right, target);
  else if (target < vec[mid])
      return __find(vec, left, mid-1, target);
  else
      return vec[mid];
}

int BinarySearch(vector<int> vec, int target) {
    return __find(vec, 0, vec.size()-1, target);
}

int main() {
    vector<int> vec;
    vec.reserve(3);
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(6);
    int res = BinarySearch(vec, 4);
    cout << "res:" << res << endl;
}
