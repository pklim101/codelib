/*************************************************************************
    > File Name: reverseList.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 三  4/22 23:46:38 2020
 ************************************************************************/

#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
      ListNode *cur = head;
      ListNode* pre = NULL;
      //ListNode* pre; //不管什么时候都记得指针要初始化，例如这里不初始化，则在下面cur->next = pre这里赋值会出现段错误.
      ListNode* next;
      while(cur != NULL){
        //step1: 保存下一节点到next;
        next = cur->next;
        //step2: 将下一节点指向前驱节点;
        cur->next = pre;
        //step3: 将前驱节点指向当前节点;
        pre = cur;
        //step4: 将当前节点移动到下一节点.
        cur = next; 
      }
      return pre;
    }
};

int main(){
  ListNode* head;
  for (int i = 5 ; i > 0; i--) {
    if(i == 5) {
      head = new ListNode(i);
    } else {
      ListNode* p = new ListNode(i);
      p -> next = head;
      head = p;
    }
  }

  Solution s;
  head = s.reverseList(head);
  while(head){
    cout << head->val << endl;
    head = head->next;
  }
  return 0;
}
