/*************************************************************************
    > File Name: string.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年05月20日 星期三 18时22分02秒
 ************************************************************************/

#include<iostream>
using namespace std;

void strfind(){
  string str = "hello://world." ;
  string::size_type pos = str.find("://");
  cout << str << ":" << pos << endl;
  cout << str.substr(0, pos) << endl; //截取是前闭后开
  cout << str.substr(pos+2) << endl;//也是前闭后开
}

void testAtoi(){
  string str = "807";
  const char* pp = str.c_str();
  cout << atoi(pp) << endl;
}

int main(){
  strfind();
 testAtoi();
  return 0;
}
