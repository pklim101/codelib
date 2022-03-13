/*************************************************************************
    > File Name: virtual.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年05月15日 星期五 16时36分18秒
 ************************************************************************/

#include<iostream>
using namespace std;

class parent
{
public:
  parent();
  virtual ~parent();
  void func1(){}
};

class child: public parent
{
public:
  child();
  ~child();
  void func1();	
};


int main()
{
  parent *test = new child();
	return 0;
};

