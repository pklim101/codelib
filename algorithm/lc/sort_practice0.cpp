/*************************************************************************
    > File Name: sort_practice0.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年07月14日 星期二 18时28分51秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
冒泡排序：O(N^2)，每次遍历两两交换，大的放后面.
*/
void bubble(vector<int>& vec) {
  int num = vec.size(); 
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num-1; j++) {
      if (vec[j] > vec[j+1]) {
        swap(vec[j], vec[j+1]);
      }
    }
  }
}

//选择排序：每次遍历，都记录最小值的索引位置，遍历完成后，将最小值与外层循环被比较的值
void selection(vector<int>& vec){
  int len = vec.size();
  for (int i = 0; i < len; i++) {
    int minIndex = i;
    for (int j = i+1; j < len; j++) {
      if (vec[minIndex] > vec[j]) {
        minIndex = j;
      }
    }
    swap(vec[minIndex], vec[i]); //别掉了这行.
  }
}

//插入排序：查到插入后就排好序的位置.
void insertion(vector<int>& vec) {
  int len = vec.size();
  for (int i = 1; i < len; i++) {
    for (int j = i; j > 0; j--) {
      if (vec[j] < vec[j-1]) {
        swap(vec[j], vec[j-1]);
      } else 
        break;
    }
  }
}

void _partition(vector<int>& vec, int l, int r){

}
void _quick(vector<int>& vec, int l, int r){
  
}
//快速排序：partition + 左右拆分递归.
void quick(vector<int>& vec){
  _quick(vec, 0, vec.size()); 
}

int main(){
  vector<int> vec = {2,9,1,5,7};
  //bubble(vec);
  //selection(vec);
  //insertion(vec);

  for (auto i : vec) {
    printf("%d,", i);
  }
  return 0;
}
