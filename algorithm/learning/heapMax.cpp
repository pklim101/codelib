/*************************************************************************
    > File Name: HeapMax.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 三  4/ 1 18:42:21 2020
 ************************************************************************/

#include<iostream>
#include<cassert>
using namespace std;

/**
二叉堆定义：最大堆：每一个节点都不大于其父节点的值；最小堆：每一个节点都不小于其父节点的值.
二叉堆的满足条件:1. 每一个节点都不大于/小于其父节点的值；2. 必须是一颗完全二叉树.

完全二叉树：每一层都达到节点最大个数，只有最底层能从右到左连续的无叶子节点.
 */
template<typename Item>
class HeapMax {
private:
  Item* data_;
  int count_; //节点个数. 也用来作为节点索引id，根节点索引id为1.
  int capacity_;

  //关键点：1.当前节点和父节点比较大小； 2.swap()
  void shiftUp(int k) {
    while (k > 1 && data_[k/2] < data_[k]) {  //k>1是因为根节点不用比较.
      swap(data_[k/2], data_[k]);
      k /= 2;  //注意：这里别丢了，这是因为要依次向根节点判断.
    }
  }
  
  void shiftDown(int k){
    while (2*k <= count_) { //判断当前节点是否有左孩子.
      int j = 2*k; //在此轮循环中data_[j]和data_[k]交换位置.
      if (j+1 <= count_ && data_[j] < data_[j+1]) {  //j+1 <= count_：判断是否存在右子树.   左右子树比较取较大者与父节点交换.
        j += 1;
      }
      if (data_[k] >= data_[j]) {  //父节点与子节点判断大小后决定是否交换.
        break;
      }
      swap(data_[k], data_[j]);
      k = j;
    }    
  }

public:
  HeapMax(int capacity):capacity_(capacity) {
    data_ = new Item[capacity];
  }
  ~HeapMax() {
    delete[] data_;
  }

  int size(){
    return count_;
  }

  bool isEmpty(){
    return count_ == 0;
  }

  void insert(Item item) {
    assert(count_+1 <= capacity_);
    data_[count_+1] = item;
    count_++;
    shiftUp(count_);
  }

  Item popMax(){
    assert(count_>0);
    Item ret = data_[1];
    swap(data_[1], data_[count_]);
    shiftDown(1);
    return ret;
  }

};

int main() {
  HeapMax<int> heap_map = HeapMax<int>(10);
  heap_map.insert(10);
  heap_map.insert(20);
  cout << heap_map.size() << endl;
  int max = heap_map.popMax();
  cout<< max << endl;
  return 0;
}

