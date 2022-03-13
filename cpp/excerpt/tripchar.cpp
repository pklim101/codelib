/*************************************************************************
	> File Name: 2.cpp
	> Author: tony
	> Mail: tony@z.com 
	> Created Time: 2019年07月24日 星期三 22时56分52秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include<iostream> 
#include<string.h> 
using namespace std; 
int main(){ 
	string s="-daas-j--kdj-al-"; 
	string::iterator it; 
	for(it=s.begin();it!=s.end();it++) 
		if(*it=='-') { 
			s.erase(it); it--; 
		} 
		cout<<s<<endl; 
	return 0; 
}
