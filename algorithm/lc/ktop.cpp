/*************************************************************************
    > File Name: ktop.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  6/ 4 22:03:03 2020
 ************************************************************************/

#include<iostream>
using namespace std;

/**
题目:有两个降序排列的int型数组，要求从这两个数组中找出第K大的数.
说明:数组中可以有重复的数,如: 5,4,4  则第2大的数是4，第3大的数是4.
*/

#include<vector>
int foo(vector<int>& vec1, vector<int>& vec2, int k){
		int size1 = vec1.size();
    int size2 = vec2.size();
    int i = 0;
    int j = 0;
		int count = 0;
/**
    while (i != size1 && j != size2) {
			count ++;	
			cout << i << "-" << j << "-" << count << endl;
    	if (vec1[i] <= vec2[j]) {
				if (k == count)
						return vec2[i];
    		j++;
    	} else if (vec1[i] > vec2[j]) {
				if (k == count)
						return vec1[i];
        i++;
      }
    }
*/
	int total = size1 + size2;
	for (int z = 0; z < total; z++) {
		if (i == size1)
			j++;
		else if (j == size2)
			i++;
		else if (vec1[i] <= vec2[j])	
			j++;
		else 
			i++;
		if (k-1 == z ) {
			if (z < size1)
				return vec1[z];
			else 
				return vec2[z-size1];
		}
	}
		return -1;
}

int main(){
	vector<int> vec1{9,8};	
	vector<int> vec2{2,1,1,0};	
	int res = foo(vec1, vec2, 1);
	cout << res << endl;
	return 0;
}

