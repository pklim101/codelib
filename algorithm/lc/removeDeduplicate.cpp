/*************************************************************************
    > File Name: removededuplicate.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  4/12 10:55:22 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

//这里要传入数组的引用，在函数内修改数组元素的值，在c++里不能写成int (&arr)[]，
//因为数组名本身就是指向数组第一个元素的地址，直接传入int arr[]就可以在函数内修改数组元素的值.
int removeDeduplicate(int arr[], int n){
  if (n<2){
    return n;
  }
  int j = 0;
  for (int i=1; i<n; i++){
    if(arr[j]!=arr[i]) arr[++j] = arr[i];  //如果相邻的两个不相等，则自己给自己赋值了.
  }
  return ++j;
}
int removeDuplicates(vector<int>& nums) {
	if (nums.size() < 2) return nums.size();
	int j = 0;
	for (int i = 1; i < nums.size(); i++)
		if (nums[j] != nums[i]) nums[++j] = nums[i];
	return ++j;
}

int main(){
  int n = 7;
  int arr[] = {0,1,2,2,2,3,3};
  int count = removeDeduplicate(arr,n);
  cout << "new arrlen=" << count << endl;
  for(int i : arr){
    cout << arr[i] << endl;
  }
  /*
  vector<int> nums(arr, arr+n);
  for (int i : nums){
    cout << i << endl;
  }
  int v = removeDuplicates(nums);
  cout << "vec=" << v << endl;
  for (int i : nums){
    cout << i << endl;
  }
  */
  return 0;
}

