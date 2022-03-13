/*************************************************************************
    > File Name: letterCombination.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  5/31 22:16:07 2020
 ************************************************************************/

#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

/**
树形问题：递归通常会形成递归树，处理递归树这样的问题成为树形问题.

题目：手机键盘0~9，根据数字字符串获得对应字母的所有组合.
解法思路：依次每个数字取对应字母作为一个子过程，进行递归.
*/

class solution {
private:
  const string letterArr[10] = {
    " ",     //0
    "",      //1
    "abc",   //2
    "def",   //3
    "ghi",   //4
    "jkl",   //5
    "mno",   //6
    "pqrs",  //7
    "tuv",   //8
    "wxyz",  //9
  };
  vector<string> _res;
  //s需要加const，否则s+letters[i]报错：non-const lvalue reference to type 'basic_string<[3 * ...]>'
  void _findLetterCombination(string& digits, int index, const string& s) {
    //1.终止条件
    if (index == digits.size()) {
      _res.push_back(s);
      return;
    }
    //2.当层处理
    //3.下探到下一层
    char ch = digits[index];
    assert(ch >= '0' && ch <= '9' && ch != '1');
    string letters = letterArr[ch-'0']; //ascii
    for (int i = 0; i < letters.size(); i++) {
      _findLetterCombination(digits, index+1, s + letters[i]);  //递归：树形结构. 当前字母对应子树有三个字母.
    }
    //4.清理当前层
  }

public:
  vector<string> letterCombinations(string digits){
    _res.clear();
    _findLetterCombination(digits, 0, "");
    return _res;
  }  
};

int main(){
  solution s;
  vector<string> res = s.letterCombinations("23");
  for (string i : res) {
    cout << i << endl;
  }
  return 0;
}
