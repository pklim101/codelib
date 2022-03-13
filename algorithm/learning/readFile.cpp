/*************************************************************************
    > File Name: readFile.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  4/ 2 21:55:27 2020
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<sstream>
#include<cassert>
using namespace std;

class ReadFile {
public:
  ReadFile (string filename) {
    ifstream file(filename);
    string line;
    assert(file.is_open());
    int a, b;
    while(getline(file,line)){
      stringstream ss(line);
      cout << ss.str() << endl;
      ss>>a>>b;  //这样竟然能自动将一行数据里的每个\t分割的字符串放入a和b中.
      cout << "a=" << a << ",b=" << b << endl;
    }
  }
};

int main() {
  string filename = "./file.txt";
  ReadFile rf(filename);
  return 0;
}

