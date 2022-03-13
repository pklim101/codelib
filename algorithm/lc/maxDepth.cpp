/*************************************************************************
    > File Name: maxDepth.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月27日 星期一 10时45分16秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/**
二叉搜索树特性：当前节点大于左子数，小于右子树.
求树最大深度方法：递归，比较每个节点的左右子树长度，取最大的长度.
*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
      if (root == nullptr) {
        return 0;
      } else {
        int left_hight = maxDepth(root->left);
        int right_hight = maxDepth(root->right);
        return max(left_hight, right_hight) + 1; //每层递归，都是加一层，所以+1.
      }
    }
};

TreeNode* insert(TreeNode* root, int key){
  //如果该节点root为空，说明已经到叶子节点了，需要创建一个叶子节点挂上去.
  if (root == nullptr) {
    return new TreeNode(key);
  }

  if (key < root->val) {
    root->left = insert(root->left, key);
  }
  if (key > root->val)
    root->right = insert(root->right, key);
  return root;
}

void preOrder(TreeNode* tree){
  if (tree == nullptr)
    return;
  cout << tree->val << endl;
  preOrder(tree->left);
  preOrder(tree->right);
}
void inOrder(TreeNode* tree){
  if (tree == nullptr)
    return;
  inOrder(tree->left);
  cout << tree->val << endl;
  inOrder(tree->right);
}
void posOrder(TreeNode* tree){
  if (tree == nullptr)
    return;
  posOrder(tree->left);
  posOrder(tree->right);
  cout << tree->val << endl;
}

//求树的最大深度
class Solution2 {
public:
    int maxDepth(TreeNode* root) {
      if (root == nullptr)
        return 0;
      int leftDepth = maxDepth(root->left);
      int rightDepth = maxDepth(root->right);
      return max(leftDepth, rightDepth) + 1;
    }
};


int main(){
  TreeNode* tree = nullptr;
  vector<int> vec = {1,7,5,8,0};
  for (int i : vec) {
    tree = insert(tree, i); 
  }

  Solution2 s;
  int res = s.maxDepth(tree);
  cout << res << endl;

  return 0;
}

