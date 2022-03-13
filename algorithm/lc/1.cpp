/*************************************************************************
    > File Name: 1.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月17日 星期五 14时49分49秒
 ************************************************************************/

#include<iostream>
#include<map>
#include<vector>
using namespace std;


int __partition(vector<int>& vec, int l, int r){
  int v = vec[l]; 
  int j = l;
  for (int i = l+1; i <=r; i++) {
    if (vec[i] < v) {
      j++;
      swap(vec[i], vec[j]);
    }
  }
  swap(vec[l],vec[j]);
  return j;
}

void quickSort(vector<int>& vec, int l, int r) {
  if(l >= r)
    return;
  //1.partition:排序 + 找到左右分割的位置
  int pos = __partition(vec, l, r); 
  //2.递归继续二分
  quickSort(vec,l,pos-1);
  quickSort(vec,pos+1, r);
}



int main(){
  vector<int> vec1 = {3,4,5,6,1,2};
  quickSort(vec1, 0, 5);
  for (int i : vec1) {
    cout << i << endl;
  }


  vector<map<int,int>*> vec;
  
  //vec[0] = new map<int,int>; //段错误  null pointer  //又陷入vector[0]这样的陷阱中了：因为还没有0这个元素，但是却用vector[0]去访问.
  vec.push_back(new map<int,int>);
  int a[2][2] = 
  {{1,2},
    {3,4}};
  char b[1] = {'a'};
  return 0;
}
