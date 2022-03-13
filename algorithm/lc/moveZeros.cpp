/*************************************************************************
    > File Name: moveZeros.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月17日 星期五 11时39分21秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

//双指针
//遍历，将非0的往前移，覆盖到j的位置，每覆盖一次，j就+1；
//最后将j后面的位置置0.
void moveZeroes(vector<int>& nums) {
	int j = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != 0) {
			nums[j] = nums[i];
			j++;
		}
  }
	for (int i = j; i < nums.size(); i++) {
			nums[i] = 0;
	}

}

void moveZeroes2(vector<int>& nums) {
		int zeroIndex = 0;
		for (int i = 0; i < nums.size(); i++) {
				if (nums[i] != 0) {
						if (i != zeroIndex)
								swap(nums[i], nums[zeroIndex]);
						zeroIndex++;
				}     
		}
}
int main(){
  int a[] = {0,1,0,3,12};
  vector<int> vec(a, a+5);
  moveZeroes(vec);
  for (int i : vec){
    cout << i << endl;
  }
  return 0;
}

