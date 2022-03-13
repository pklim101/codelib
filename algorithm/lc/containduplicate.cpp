/*************************************************************************
    > File Name: containduplicate.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  4/12 18:38:28 2020
 ************************************************************************/

#include<iostream>
#include<vector>
#include<map>
//#include<algorithm>
using namespace std;

class Solution{
private:
  struct Node{
    int key;
    Node* left;
    Node* right;
    Node(int key):key(key),left(NULL),right(NULL){}
  };
  Node* root_;
  int count_ = 0;
public:
  Solution():count_(0),root_(NULL){}
  ~Solution(){
  }
  bool containsDuplicate(vector<int>& nums) {
    if (nums.size() < 2) return false;
    bool flag = false;
    for(int i=0; i < nums.size(); i++){
      root_ = insert_(root_, nums[i], flag);  
      cout << "insert i:" << i << endl;
      if (flag) return flag;
    }
    return flag;
  }

  Node* insert_(Node* node, int key, bool& flag){
    if(node == NULL) {
      return new Node(key);
    } 
    if(key == node->key){
      flag = true;
      return node;
    }
    if(key < node->key)
      node->left = insert_(node->left, key, flag);
    else if(key > node->key)
      node->right = insert_(node->right, key, flag);
    return node;
  }

};

bool mapMethod(vector<int>& nums){
  map<int, int> tmpmap;
  for(int i = 0; i < nums.size(); i++){
    auto iter = tmpmap.find(nums[i]); //哎，注意find用法. 
    if(iter != tmpmap.end()) {
      return true;
    }else{
      tmpmap.insert(pair<int,int>(nums[i],i));
    }
  }
  return false;
}

int main(){
  int arr[] = {1,2,2,3,5};
  vector<int> nums(arr, arr+5);
  /*
  Solution sol;
  bool cd = sol.containsDuplicate(nums);
  */
  bool cd = mapMethod(nums);
  cout << "result:" << cd << endl;
  return 0;
}

