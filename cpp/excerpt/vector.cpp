/*************************************************************************
    > File Name: vector.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年05月25日 星期一 15时21分22秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;


int main(){
  vector<int>* vec = new vector<int>;
  cout << vec->size() << endl;
  vec->push_back(10);
  vec->push_back(20);
  cout << vec->size() << endl;

  vector<int>* tmp;
  cout << tmp << endl;
  return 0;
}
