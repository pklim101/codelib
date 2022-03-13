/*************************************************************************
    > File Name: sudoku.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月17日 星期五 15时04分00秒
 ************************************************************************/

#include<iostream>
#include<map>
#include<vector>
using namespace std;

/**
关键点：int box_index = 3 * (i/3) + j/3;  //子数独索引id.
*/
class Solution {
public:
  bool isValidSudoku(vector<vector<char>>& board) {
    /**
    vector<map<int,int>> rows; 
    vector<map<int,int>> columns;
    vector<map<int,int>> boxes; 
    */
    vector<map<int,int>*> rows;   // int* a
    vector<map<int,int>*> columns;
    vector<map<int,int>*> boxes; 
    for (int i = 0; i < 9; i++) {
        rows.push_back(new map<int,int>);
        columns.push_back(new map<int,int>);
        boxes.push_back(new map<int,int>);
    }
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        if(board[i][j] != '.') {
          int num = board[i][j] - '0'; //其实就是减0的asscii码.
          auto iteri = rows[i]->find(num);                                                                                                                                                           
          if(iteri == rows[i]->end()){
            //rows[i][num]++ //rows[i]是个map指针
            rows[i]->insert(pair<int,int>(num,1));
          } else {
					cout << num << endl;
            //rows[i][num] += 1; //rows[i]是一个map指针，这个指针不能用[]操作.
            iteri->second += 1;
          }   
          auto iterj = columns[j]->find(num);
          if(iterj == columns[j]->end()){
            columns[j]->insert(pair<int,int>(num,1)); 
          } else {
            iterj->second += 1;
          }   
          int box_index = 3 * (i/3) + j/3;  //子数独索引id.
          auto iterb = boxes[box_index]->find(num);
          if(iterb == boxes[box_index]->end()){
            boxes[box_index]->insert(pair<int,int>(num,1)); 
          } else {
            iterb->second += 1;
          }   
              
          if (iteri->second > 1 || iterj->second > 1 || iterb->second > 1) {
            return false;
          }   
        }   
      }   
    }   
    return true;
  }
};

int main(){
  char a[9][9] = 
  {{'5','3','.','.','7','.','.','.','.'},
   {'6','.','.','1','9','5','.','.','.'},
   {'.','9','8','.','.','.','.','6','.'},
   {'8','.','.','.','6','.','.','.','3'},
   {'4','.','.','8','.','3','.','.','1'},
   {'7','.','.','.','2','.','.','.','6'},
   {'.','6','.','.','.','.','2','8','.'},
   {'.','.','.','4','1','9','.','.','5'},
   {'.','.','.','.','8','.','.','7','9'}};

  vector<vector<char>> board;
  for (int i = 0; i < 9; i ++) {
    board.push_back(vector<char>(a[i],a[i]+9));
  }
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      //cout << board[i][j] << endl;
    }
  }
	Solution s;
  bool res = s.isValidSudoku(board);
	cout << "res=" << res << endl;
	
	return 0;
}

