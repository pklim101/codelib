/*************************************************************************
    > File Name: 1.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月08日 星期一 18时13分17秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<map>
#include "unistd.h"
using namespace std;


int aaa;

class AA{
public:
  AA () {
    cout << "construction" << endl;
  }
  ~ AA () {
    cout << "destruction" << endl;
  }
};



int main(){
  map<int, string> mm;
  mm.insert(make_pair(10, "hello"));
  mm.insert(make_pair(10, "hello2"));
  for (auto i : mm) {
    cout << i.second << endl;
  }
  AA* aa = new AA();
  aa = NULL;

  cout << sizeof(aaa) << endl;
  int a = -10;
  if (a) {
    cout << "true" <<endl;
  } else {
    cout << "false" <<endl;
  }
  //gcc是2倍方式扩容.
  vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);
  cout << vec.size() << endl;
  cout << vec.capacity() << endl;
  cout << vec.max_size() << endl;
  return 0;
}
