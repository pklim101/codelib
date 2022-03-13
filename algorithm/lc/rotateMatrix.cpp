/*************************************************************************
    > File Name: rotateMatrix.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 一  4/20 23:09:50 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
      //对矩阵求转置：对折
      for(int i = 0; i < matrix.size(); i++){
        //因为对折，所以这里从j=i开始，也就是只求对角线的一半.
        for(int j = i; j < matrix[i].size(); j++){
          swap(matrix[i][j],matrix[j][i]);
        }
      }
      //对每行数组求倒序
      for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size()/2; j++){
          swap(matrix[i][j],matrix[i][matrix[i].size()-j-1]);
        }
      }
      for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
          cout << matrix[i][j] << endl;
        }
      }
    }
};

int main(){
  int a[][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,9},
  }; 
  vector<vector<int>> matrix;
  for(int i = 0; i < 3; i++){
    matrix.push_back(vector<int>(a[i],a[i]+3));
  }
  Solution s;
  s.rotate(matrix);
  return 0;
}
