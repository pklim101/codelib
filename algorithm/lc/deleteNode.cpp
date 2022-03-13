/*************************************************************************
    > File Name: deleteNode.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 二  4/21 00:22:39 2020
 ************************************************************************/

#include<iostream>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    void deleteNode(ListNode* node) {
      node->val = node->next->val;
      node->next = node->next->next;
    }
};

int main(){
  struct ListNode *head;
  for (int i = 0; i < 10; i++){
    if (i == 0)
      head = new ListNode(i,NULL);
    else
      head = new ListNode(i,head); //头插法
  }
  while(head != nullptr){
    cout << head->val << endl;
    head = head->next;
  }
  return 0;
}

