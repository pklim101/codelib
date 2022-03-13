/*************************************************************************
    > File Name: validateBST.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月03日 星期三 15时42分04秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;


struct TreeNode {
  TreeNode* left;
  TreeNode* right;
  int key;
  int val;
  TreeNode(int key, int val):key(key), val(val), left(nullptr), right(nullptr){};
};

//递归函数
//在以node为根的二叉搜索树中插入节点；
//每次递归返回插入节点后的子数的根节点.
TreeNode* insertNode(TreeNode* node, int k, int v){
  //1.终止
  if (node == nullptr) {
    return new TreeNode(k, v);
  }
  
  if (k == node->key)
    node->val = v;
  else if (k < node->key)
    node->left = insertNode(node->left, k, v);
  else 
    node->right = insertNode(node->right, k, v);
  return node;
}

//给定一个数组，用其创建一颗二叉搜索树，采用广度遍历.
TreeNode* createBST(vector<int>& vec){
  TreeNode* root = nullptr;
  for (auto i : vec) {
    root = insertNode(root, i, i); 
  }
  return root;
}


//遍历二叉树
void inOrder(TreeNode* node){
  //递归千万不要忘记终止条件了， 这里忘记了，所以段错误了.
  if (node == nullptr)
    return;
  inOrder(node->left);
  cout << node->val << endl;
  inOrder(node->right);
}

//使用中序遍历验证二叉树
//这道题对返回值纠结了半天.
long long last = LONG_MIN; //要用到LONG，应该是lc里
bool inOrderForValid(TreeNode* node){
  if (node == nullptr)
    return true;
  if (!inOrderForValid(node->left))
    return false;
  if (node->val < last)
    return false;
  last = node->val;
  if (!inOrderForValid(node->right))
    return false;
  return true;
}

bool validateBST(){
  vector<int> vec = {2,1,3};
  TreeNode* root = createBST(vec);
  bool res = inOrderForValid(root);
  cout << res << endl;
  return false;
}

int main(){
  validateBST();

  return 0;
}

