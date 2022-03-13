/*************************************************************************
    > File Name: binarySearchTree.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 六  4/ 4 11:40:38 2020
 ************************************************************************/

#include<iostream>
#include<queue>
#include<cassert>
using namespace std;

/** 二分搜索树
必须满足条件:
  1. 任意节点>左孩子且<右孩子; =>因为此特性，所以具有天然的递归特性.
  2. 必须是一颗二叉树，但不必是一颗完全二叉树(二叉堆必须是完全二叉树);

二分搜索树优点：
  1. 可以做查找表(即dict);
  2. 可以回答很多和顺序相关的问题：minmum,maxmum,rank,select.

二分搜索树的局限性:
  1. 插入节点的顺序不同，相同的数据可能会构建不同的二叉搜索树，极端情况下会退化成链表，
     时间复杂度从O(logN)退化成O(N); 因为二叉搜索树查找的时间复杂度和树的高度有关(logN).
  2. 对于第一点的局限性，提出了平衡二叉树的概念，其有许多实现，比如红黑树,2-3tree,AVL树,Splay树(伸展树).
     平衡二叉树的定义:二叉搜索树 + 左右子树高度差不超过1.

二分搜索树增删改查操作的基本思想:
  1. 递归；
  2. 每次递归，都是处理一个子二叉搜索树，且传入一个要处理的子二叉树的根节点，然后返回一个处理完成后的新的子二叉树的根节点.
*/

template<typename Key, typename Value>
class BST{
private:
  struct Node {
    Key key;
    Value value;
    Node* left;
    Node* right;
    int nodeNum; //当前节点(包含当前节点)的子树公有多少个节点，用于rank,select函数;
    int nodeRepeatNum; //当前节点重复的个数.

    //为此节点生成一个构造函数
    Node(Key key, Value value):key(key),value(value),left(NULL),right(NULL){
    }
    Node(Node* node):key(node->key),value(node->value),left(node->left),right(node->right){
    }
  };
  Node* root_;
  int count_;
public:
  BST(){
    root_ = NULL;
    count_ = 0;
  }
  ~BST(){
    //TODO ~BST()
    destroy_(root_);
  }
  Node* getRoot(){
    return root_;
  }
  int siez(){
    return count_;
  }
  bool isEmpty(){
    return count_ == 0; //或者 return root_ == NULL;
  }

  //插入一个节点到一颗搜索二叉树中.
  void insert(Key key, Value value){
    //插入节点的时候，首先从整棵树的根节点开始插入.
    root_ = insert_(root_, key, value);
  }

  //查找是否存在key节点.
  bool contain(Key key) {
    return contain_(root_, key);
  }

  Value* search(Key key){
    return search_(root_, key);
  }
  //前序遍历
  void preOrder(Node* node){
    preOrder_(node);
  }
  //中序遍历
  void inOrder(){
    inOrder_(root_);
  }
  //后序遍历
  void posOrder(Node* node){
    posOrder_(node);
  }

  //层序遍历：广度优先
  void levelOrder(){
    queue<Node*> q;
    q.push(root_);
    while(!q.empty()){
      Node* node = q.front();
      q.pop();
      cout << node->key << endl;
      if(node->left)
        q.push(node->left);
      if(node->right)
        q.push(node->right);
    }
  }

  //获取二叉树最小值. 
  Key minmum(){
    assert(count_ != 0);
    Node* min = minmum_(root_);
    return min->key;
  }
  //获取二叉树最大值.
  Key maxmum(){
    assert(count_ != 0);
    Node* max = maxmum_(root_);
    return max->key;
  }

  //删除二叉树最小值
  void removeMinmum(){
    if (root_ != NULL)
      root_ = removeMinmum_(root_);
  }
  //删除二叉树最大值
  void removeMaxmum(){
    if (root_ != NULL)
      root_ = removeMaxmum_(root_);
  }
  //删除二叉搜索树中任意键为key的节点
  void removeNode(Key key){
    root_ = removeNode_(root_, key);
  }

private:
  //向以node为根的二叉树中插入一个节点(key, value)
  //返回插入新节点后的二叉搜索树的根.
  Node* insert_ (Node* node, Key key, Value value) {
    if (node == NULL) {
      count_ ++;
      return new Node(key, value);
    }

    if (key == node->key) 
      node->value = value; //如果插入的key等于该节点的key，则更新value值.
    else if (key < node->key)
      //node->left = node->insert_(node, key, value); //注意：因为要递归，所以这里不应该是node，而应该是node->left.
      node->left = insert_(node->left, key, value); //注意：小于的时候，在做子树中插入.
    else // key > node->key
      node->right = insert_(node->right, key, value);

    return node; //返回的是每次递归用的子二叉搜索树的根节点. => 注意：这里不太好理解.
  }

  //查找以node为根的二叉树中是否存在节点key.
  bool contain_(Node* node, Key key){
    if (node == NULL) 
      return false;
    if(key == node->key)
      return true;
    else if (key < node->key)
      return contain_(node->left, key);
    else 
      return contain_(node->right, key);
  }

  //找到以node为根的二叉树中为key的节点的值.
  Value* search_(Node* node, Key key){
    if(node == NULL)
      return NULL;
    if(key == node->key)   //怎么竟然把这行都忘记了呢.
      return &(node->value);
    if(key < node->key)
      return search_(node->left, key); //找不到就在左子树找.
    else //key > node->key
      return search_(node->right, key);
  }

  //对以node为根节点的二叉树进行前序遍历
  void preOrder_(Node* node){
    if (node != NULL) {
      cout << node->key << endl;  //注意：该输出在哪一行就表示是哪种序遍历.
      preOrder_(node->left);
      preOrder_(node->right);
    }
  }
  //对以node为根节点的二叉树进行中序遍历
  void inOrder_(Node* node){
    if (node != NULL) {
      inOrder_(node->left);
      cout << node->key << endl;
      inOrder_(node->right);
    }
  }
  //对以node为根节点的二叉树进行后序遍历
  void posOrder_(Node* node){
    if (node != NULL) {
      posOrder_(node->left);
      posOrder_(node->right);
      cout << node->key << endl;
    }
  }

  //利用后续遍历对整颗二叉树进行析构
  //因为后续遍历是在一个节点的最后访问的时候才做是操作.
  void destroy_(Node* node) {
    if (node != NULL) {
      destroy_(node->left); 
      destroy_(node->right); 

      delete node;
      count_--;
    }
  }

  //返回以node为根节点的二叉树的最小key值.
  Node* minmum_(Node* node){
    if (node->left == NULL) {
      return node;
    }
    return minmum_(node->left);
  }
  //返回以node为根节点的二叉树的最大key值.
  Node* maxmum_(Node* node){
    if(node->right == NULL)
      return node;
    return maxmum_(node->right);
  }

  //返回删除最小值后的子二叉树的根节点.
  Node* removeMinmum_(Node* node){
    if(node->left == NULL){
      Node* rightNode = node->right;  //右节点为空也可以. 
      delete node;
      count_--;
      //node = rightNode; //如果没有左子节点，则删除当前节点后把右子节点放入当前子树的根节点，所以应该是return右子节点.
      return rightNode;
    }
    node->left = removeMinmum_(node->left); //如果有左子节点，则需要继续递归找更小的左子节点进行删除.
    //return removeMinmum_(node->left);
    return node;
  }
  //返回删除最大值后的子二叉树的根节点.
  Node* removeMaxmum_(Node* node){
    if(node->right == NULL){
      Node* leftNode = node->left;  //左节点为空也可以. 
      delete node;
      count_--;
      return leftNode;
    }
    node->right = removeMaxmum_(node->right);
    return node;
  }
  /** 以下两点对于删除节点的理解非常重要:
  1.删除以node为根的子二叉搜索树中键为key的节点,
  2.返回删除该节点后新的子二叉搜索树的根节点.
  */
  Node* removeNode_(Node* node, Key key){
    //1. 判断当前子树的根节点是否存在;
    if (node == NULL)
      return NULL;
    //2. 如果key小于当前子树根节点的key，则从左子树递归找;
    if (key < node->key) {
      node->left = removeNode_(node->left, key); // 注意：这点理解很重要：当前节点的左节点为当前节点的左子树的根节点(因为removeNode_()后返回的是子树的根节点.)
      return node; //返回当前子树的根节点.
    }
    //3. 如果key大于当前子树根节点的key，则从右子树队规找;
    else if (key > node->key) {
      node->right = removeNode_(node->right, key);
      return node;
    }
    //4. 如果找到key等于当前子树根节点的key，则执行删除key节点操作;
    else {
      //4.1 要删除的节点的左孩子为空,则把右孩子作为当前子树的根节点返回.
      if (node->left == NULL) {
        Node* rightNode = node->right;
        delete node;
        count_--;
        return rightNode;
      }
      //4.2 要删除的节点的右孩子为空,则把左孩子作为当前子树的根节点返回.
      else if (node->right == NULL) {
        Node* leftNode = node->left;
        delete node;
        count_--;
        return leftNode;
      }
      //4.3 要删除的节点的左右孩子都不为空,则把后继节点作为当前子树的根节点返回:重点.
      else {
        //4.3.1 找到右子树的最小节点，并且拷贝一份；
        //Node* successor = new Node(minmum_(node));
        Node* successor = new Node(minmum_(node->right));
        count_++;
        //4.3.2 删除右子树的最小节点，返回了右子树的根节点,作为后继节点的右节点；
        successor->right = removeMinmum_(node->right);
        //4.3.3 给后继节点左节点赋值
        successor->left = node->left;
        //4.3.4 删除当前节点.
        delete node;
        count_--;
        //4.3.5 将后继节点返回作为删除node节点后新的二叉搜索树的根节点.
        return successor; 
      }
    }
  }
};

int main(){
  BST<int, int> bst;
  bst.insert(50,500);
  bst.insert(10,100);
  bst.insert(20,200);
  bst.insert(30,300);
  bst.insert(60,600);
  /** 不能对NULL解引用.
  int* v = bst.search(70);
  cout << *v << endl; //如果搜索不到的时候会返回NULL，而*v(也就是对NULL解引用)则会出现段错误.
  */
  if(int* v = bst.search(70)){
    cout << *v << endl;
  }else{
    cout << "Not Found!" << endl;
  }
  //bst.posOrder(bst.getRoot()); //为什么打印结果是30 20 10 60 50? 应该是先20再30啊.
  bst.levelOrder(); //打印出来是50 10 60 20 30. 应该是：50 20 60 10 30
  /**
  以上两个打印结果不是和期望结果一致的原因是：自己理解错了插入的树的结构.
  错入理解是：
       50
      /  \
    10   60
   / \
  20 30
  正确的树结构应该是:
       50
      /  \
    10   60
     \
      20
        \
         30
  注意：正确理解插入元素后树的结构的方式:
        1.从根节点开始比较；
        2.像开车一样，如果比当前节点小，则向左插入，如果比当前节点大，则向右插入，如果相等，则替换当前节点.
  */

  int min = bst.minmum();
  int max = bst.maxmum();
  cout << "min:" << min << endl;
  cout << "max:" << max << endl;

  bst.removeMinmum();
  bst.removeMaxmum();
  bst.inOrder();

  cout << "removeNode()" << endl;
  bst.removeNode(30);
  bst.inOrder();
  
  return 0;
}

