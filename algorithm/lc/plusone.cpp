/*************************************************************************
    > File Name: plusone.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月17日 星期五 11时11分06秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;
//模拟十进制加法器：遇10进1.
vector<int> plusOne(vector<int>& digits) {
	for(int i=digits.size()-1;i>=0;i--)
	{
			++digits[i];             //进一操作

			if(digits[i]!=10)        //如果该位没有继续产生进位,则直接return 结果
					return digits;       
			else
					digits[i]=0;        //进位
	} //如果最高位遇到10则不会return，所以会继续向下走，继而在最高位前面进一(intert(begin(),1))
	cout << "xx" << endl;
	digits.insert(digits.begin(), 1);       //如果首位也产生进位,才会执行到这条语句，否则循环中已经return了
	return digits;
}

int main(){
	int a[] = {1,9,9};
  vector<int> vec(a,a+3);
	auto v = plusOne(vec);
  for(int i : v){
    cout << i << endl;
  }
	return 0;
}
