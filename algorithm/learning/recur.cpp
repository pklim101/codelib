/*************************************************************************
    > File Name: recur.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  5/16 14:45:33 2020
 ************************************************************************/

#include<iostream>
using namespace std;

/**
递归三要素：
1. 明确这个递归函数想干什么;
2. 必须由结束条件， if() return；
3. 递归代码调用顺序：被调用的递归函数前的代码与调用顺序一致，之后的与调用顺序相反.
 */

/**
  从上面的步骤我们可以清晰的看到递归算法的第一步是分治，把复杂的大的问题，给拆分成一个一个小问题，直到不能再拆解，通过退出条件retrun，然后再从最小的问题开始解决，只到所有的子问题解决完毕，那么最终的大问题就迎刃而解。
  */

int factorial(int n) {
  int m;
  if (n < 0) {
    return 0;
  } else if (n == 1) {
    m = 1;
  } else {
    m = n * factorial(n-1);
  }
  return m;
}

int fib(int n){
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else
    return fib(n-2) + fib(n-1);
}

int main(){
  printf("%d\n", factorial(3));
  printf("%d\n", fib(5));
}
