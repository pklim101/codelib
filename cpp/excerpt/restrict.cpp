/*************************************************************************
    > File Name: 3.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年03月06日 星期五 16时41分09秒
 ************************************************************************/

#include<iostream>
#include<vector>

using namespace std;
int main() {
  int* __restrict ppp = (int*) malloc(3 * sizeof(int));

  for (int i = 0; i<3; i++) {
    ppp[i] += 12;
    ppp[i] += 13;
  }

  int* ccc = &(ppp[0]);
  ccc[0] = 10;
  cout << ppp[0] << endl;

  printf("%d\n",*ppp);
  printf("%d\n",*ccc);
}

