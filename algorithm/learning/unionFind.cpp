/*************************************************************************
    > File Name: unionFind.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  4/ 2 09:35:51 2020
 ************************************************************************/

#include<iostream>
#include<cassert>
using namespace std;

/**
并查集：
  概念：有两组数据，每组数据内的元素相连，然后需要实现：
  1.查：查找两组数据中分别两个元素是否相连；
  2.并：将两组数据连接到一起.
  
  解决问题：判断两个元素是否是连接的.

  并查集数据结构：树形结构，但是当前节点的指针指向父节点.
  并查集存储方式：数组存储，key为当前节点，value为父节点. 例子：parent[i]=j,表示当前节点是i，父节点是j，这里并查集数据都存储在parent数组里.

  时间复杂度分析：
  近似为O(1).
  查：从当前节点遍历到根节点即可。
  并：找到两组数据的根，然后将其中一个根指向另外一个根。
  优化：
    将当前节点的层降低。 
    优化方式：1.基于rank优化：将层较短的指向较长的根；
              2.路径压缩优化：在查的时候，更改当前节点指向的父接节点，两种方式：a.一步一遍历改为一步遍历两个节点；b.将所有节点都直接指向根节点(递归);
*/

/**
  优化：Quick Union.
  实现关键点: 
    1. 根节点自己指向自己；
    2. 合并的时候让一个根节点指向另外一个根节点.
 */
class UF2{
private:
  int* parent_;
  int count_;

public:
  //构建一个数组，key为元素，value为元素指向另外一个元素的key，初始状态下每个元素都指向自己.
  UF2(int n){
    count_ = n;
    parent_ = new int[n];
    for (int i=0; i<n; i++) {
      parent_[i] = i;
    }
  }
  ~UF2 () {
    delete[] parent_;
  }

  //检查两个节点是否相连接.
  bool isConnected(int p, int q) {
    return find(p) == find(q);
  }
  //查找一个元素p的根节点的位置(即对应parent数组的value值).
  //注意：是根节点的位置.
  int find(int p){
    assert(p>=0 && p<count_);
    while (p != parent_[p]) {
      parent_[p] = parent_[parent_[p]];  //注意：主要加这一句话，就可以把Quick Union变成路径压缩优化法，提升查找效率[树的层级变短了,查找更快了].
      p = parent_[p];  //关键点：一次向父节点查找是否到达根节点(自己指向自己).
    }
    return p;
  }

  void unionElements(int p, int q){
    int pRoot = parent_[p]; 
    int qRoot = parent_[q];
    if (pRoot == qRoot) {
      return;
    }
    parent_[pRoot] = qRoot;
  }
};

/**
优化方式：基于rank优化.
实现思路：降低层.
  1.用rank[]记录每个根节点的层数；
  2.并的时候，用层数短的根节点指向层数高的根节点.
*/

class UF3{
private:
  int *_parent;
  int *_rank;
  int _count;
public:
  UF3(int n):_count(n) {
    _parent = new int[_count];
    _rank = new int[_count];
    for (int i = 0; i < n; i++) {
      _parent[i] = i;
      _rank[i] = 1;
    }
  }
  ~UF3(){
    delete [] _parent;
    delete [] _rank;
  }

  //查找p节点的根节点.
  int find(int p){
    while (p != _parent[p]) {
      p = _parent[p];
    } 
    return p;
  }

  int isConnected(int p, int q){
    return find(p) == find(q);
  }

  //将组数据并在一起(一个根指向另外一个根)
  void unionElements(int p, int q){
    int pRoot = find(p);
    int qRoot = find(q);
    
    if (pRoot == qRoot)
      return;

    if (_rank[p] < _rank[q]) {
      _parent[pRoot] = qRoot;   //不用对rank加1是因为将短的连接到长的上面，_rank[qRoot]这个新的根所对应的层深度不变.
    } else if (_rank[p] > _rank[q]) {
      _parent[qRoot] = pRoot;
    } else {   //需要单独处理深度相等的情况，因为相等的时候做连接，就要处理_rank深度。此时任何一方连接另外一方都可以.
      _parent[pRoot] = qRoot;
      _rank[qRoot] += 1;
    }
  }
};

/**
优化方式：路径压缩.
思路：基于rank，在查的时候将一个节点一个节点的遍历改为一次遍历两个节点，同时将深度压短.

*/
class UF4{
private:
  int *_parent;
  int *_rank;
  int _count;
public:
  UF4(int n):_count(n) {
    _parent = new int[_count];
    _rank = new int[_count];
    for (int i = 0; i < n; i++) {
      _parent[i] = i;
      _rank[i] = 1;
    }
  }
  ~UF4(){
    delete [] _parent;
    delete [] _rank;
  }

  //查找p节点的根节点.
  int find(int p){
    /**
    while (p != _parent[p]) {
      p = _parent[p];
    } 
    */
    while (p != _parent[p]) {
      _parent[p] = _parent[_parent[p]];//关键点：一次遍历，压缩一层.
      p = _parent[p];
    }
    return p;
  }

  int isConnected(int p, int q){
    return find(p) == find(q);
  }

  //将组数据并在一起(一个根指向另外一个根)
  void unionElements(int p, int q){
    int pRoot = find(p);
    int qRoot = find(q);
    
    if (pRoot == qRoot)
      return;

    if (_rank[p] < _rank[q]) {
      _parent[pRoot] = qRoot;   //不用对rank加1是因为将短的连接到长的上面，_rank[qRoot]这个新的根所对应的层深度不变.
    } else if (_rank[p] > _rank[q]) {
      _parent[qRoot] = pRoot;
    } else {   //需要单独处理深度相等的情况，因为相等的时候做连接，就要处理_rank深度。此时任何一方连接另外一方都可以.
      _parent[pRoot] = qRoot;
      _rank[qRoot] += 1;
    }
  }
};

int main(){
  int n = 10;
  UF2 uf2 = UF2(n);
  return 0;
}

