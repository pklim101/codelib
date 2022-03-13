/*************************************************************************
    > File Name: maxArea.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月03日 星期三 14时57分50秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
题目：给出一个数组，求出水位最大面积.
方法：想向双指针.谁小谁就往前移动一个，直到遍历完后取maxArea的最大值.
*/

int maxAreaWater (vector<int>& vec) {
  int i = 0;
  int j = vec.size() - 1;
  int minValue = 0;
  int maxArea = 0;

  while (i != j) {
    minValue = std::min(vec[i], vec[j]); 
    //maxArea = std::max(maxArea, minValue * (j-i+1));  //不应该+1，因为是求数之间的空格数.
    maxArea = std::max(maxArea, minValue * (j-i));
    if (minValue == vec[i]) {
      i++;
    } else {
      j--;
    }
  }
  return maxArea; 
}


int main(){
  vector<int> vec = {1,8,6,2,5,4,8,3,7};
  int maxArea = maxAreaWater(vec);
  cout << maxArea << endl;
  return 0;
}
