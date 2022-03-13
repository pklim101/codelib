/*************************************************************************
    > File Name: iofstream.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年07月07日 星期二 11时45分47秒
 ************************************************************************/

#include<iostream>
#include<fstream>  //记住头文件是fstream， 没有ifstream。
#include<unordered_map>
using namespace std;

int main(){
  const char* filename = "a.log";
  ifstream ifs(filename, std::ifstream::in);
  char c = ifs.get(); //从stream中获取一个字符.
  while(ifs.good()){ //stream的error state flags(eofbit,failbit,badbit)被设置为none则返回true.也就是文件流可继续正常读.
    cout << c ;
    c = ifs.get(); 
  }
  ifs.close();
  /**
    aaa 111 
    bbb 222
    可用ifsream做如上格式的配置文件.
  */

  unordered_map<string, int> conf_map;
  string key("");
  int val = 0;
  string confname = "b.log";
  ifstream conf(confname);
  while(!conf.eof()) {
    conf >> key >> val;
    conf_map.insert(pair<string, int>(key, val));
  }
  for (auto iter = conf_map.begin(); iter != conf_map.end(); ++iter) {
    printf("conf-> key:%s, val:%d\n", iter->first.c_str(), iter->second);
  }
  return 0;
}

