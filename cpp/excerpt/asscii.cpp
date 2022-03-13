/*************************************************************************
    > File Name: asscii.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年07月07日 星期二 16时21分44秒
 ************************************************************************/


//编译方法：g++ -I/usr/include -lssl asscii.cpp
//因为使用到了openssl里的md5.h，所以需要链接对应的库：-lssl。

#include<iostream>
#include</usr/include/openssl/md5.h>
#include<stdio.h>
using namespace std;

string GetMD5(const string& input)
{
  unsigned char digest[MD5_DIGEST_LENGTH];
  MD5((const unsigned char*)input.c_str(), input.length(), (unsigned char*)&digest);
  char res[33];
  for(int i = 0; i < 16; i++)
  {
    sprintf(&res[i*2], "%02X", (unsigned int)digest[i]);
  }
  res[32] = '\0';
  //return res;
	string* ss = new string("world");
	return string(res);
}


int main(){
  //%02X表示：款速为2个，不足则用0填充，X表示用十六进制方式格式化.
  printf("十六进制格式为：%02X\n", 10); //结果为0A

	//c++中没有byte,替代的方法是：unsigned char.
	//byte aa = 10; //范围0~255，占一个字节，8个bit位.

	string str = "hello";
	string res = GetMD5(str);
	cout << res << endl;
  return 0;
}
