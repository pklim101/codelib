/*************************************************************************
    > File Name: reverseString.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 一  4/20 23:28:05 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
      for(int i = 0; i < s.size()/2; i++){
        swap(s[i],s[s.size()-i-1]); 
      }
    }
};

int main(){
  vector<char> s = {'h','e','l','l','o'};
  Solution sol;
  sol.reverseString(s);
  for(char i : s){
    cout << i << endl;
  }
  return 0;
}

