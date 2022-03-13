/*************************************************************************
    > File Name: rand.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年03月31日 星期二 15时46分51秒
 ************************************************************************/

#include<iostream>
using namespace std;

int main(){
  srandom(time(NULL));
  long int aa = random();
  cout << aa << endl;
  cout << time(NULL) << endl;
  return 0;
}
