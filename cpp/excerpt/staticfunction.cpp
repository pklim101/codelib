/*************************************************************************
    > File Name: staticfunction.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年07月08日 星期三 09时51分25秒
 ************************************************************************/

#include<iostream>
using namespace std;
//静态方法不会造成内存泄漏.

class Stu {
public:
  static string foo(string& str){
    string tmp(""); 
    tmp = str;
    return str;
  }
};

int main(){
  string str = "hello";
  string res = Stu::foo(str);
  cout << res << endl;
  string str2 = "world";
  string res2 = Stu::foo(str2);
  cout << res2 << endl;
  return 0;
}

