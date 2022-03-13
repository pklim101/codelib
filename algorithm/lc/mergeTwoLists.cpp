/*************************************************************************
    > File Name: mergeTwoLists.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 四  4/23 22:30:05 2020
 ************************************************************************/

#include<iostream>
using namespace std;

/**
思路：经过分析，发现两个链表的节点依次两两比较是个重复的过程，那么可以把这个重复过程抽象成一个子过程，则可考虑用递归解题.
1.递归每层返回值：返回的都是要将下一层的链表接到当前层的最后节点;
2.递归终止条件：某个链表遍历完成后，将另一个链表接到其后面；
3.递归子过程：将下一层的新参数l1',l2'传入.
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
      //1.递归终结
      if (l1 == NULL)
        return l2;
      if (l2 == NULL)
        return l1;
      //2.内部处理

      //3.下探到下一层,继续递归
      if (l1->val <= l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
      } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
      }
      //4.清理当前层的工作
    }
};


int main(){
  ListNode* head = NULL;
  for (int i = 5; i > 0; i--) {
    if(i == 5){
      head = new ListNode(i);
    } else {
      ListNode* p = new ListNode(i);
      p->next = head;
      head = p;
    }
  }

  ListNode* head2 = NULL;
  for (int i = 5; i > 2; i--) {
    if(i == 5){
      head2 = new ListNode(i);
    } else {
      ListNode* p = new ListNode(i);
      p->next = head2;
      head2 = p;
    }
  }

  Solution s;
  head = s.mergeTwoLists(head, head2);
  while(head){
    cout << head->val << endl;
    head = head->next;
  }
  return 0;
}
