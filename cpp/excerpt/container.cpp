/*************************************************************************
    > File Name: container.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年05月28日 星期四 14时45分56秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<stack> //LIFO， 基于vector，list，deque实现，默认为deque.
using namespace std;

void vectorTest() {
  vector<int> vec;
  vec.reserve(3);
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  auto iter = vec.begin();
  vec.push_back(4);
  ++iter;
  cout << *iter << endl; //迭代器失效，输出0
  iter = vec.begin();
  ++iter;
  cout << *iter << endl; //重新获取迭代器,输出正确值.
  cout << vec.capacity() << endl;
}

void stackTest(){
  stack<int>* st = new stack<int>;
  //cout << stack<int>::value_type << endl; 
  for (int i = 0; i < 5; i++) {
    st->push(i);
  }
  while (!st->empty()) {
    cout << st->top() << endl;
    st->pop(); //返回值为none
  }
}
int main(){
 stackTest();
  return 0;
}

