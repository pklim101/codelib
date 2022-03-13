/*************************************************************************
    > File Name: removeNthFromEnd.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月22日 星期三 14时26分27秒
 ************************************************************************/

#include<iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    struct ListNode *p, *q;
    p = q = head;
    for(int i = 0; i < n; i++){
       q = q->next; 
    }

    if (q == NULL) { //移动完成后如果q为NULL，说明是从第一个元素移动到最后一个的下一位了.
      ListNode *tmp = head->next;
      delete head;
      return tmp;
    }

    while(q->next != NULL){ //用q->next而不用q!=NULL是因为只需要移动q到最后一个元素即可
      q = q->next;
      p = p->next;
    }
    ListNode* delNode = p->next;
    p->next = p->next->next;
    delete delNode; //删除该节点.
    return head; 
  }
};


int main(){
	struct ListNode *head, *p;
  for (int i = 5; i >0; i--) {
    if (i == 5) {
      head = new ListNode(i);
    } else {
      p = new ListNode(i);
      p->next = head;
      head = p;
    }
  }

  Solution s;
  head = s.removeNthFromEnd(head, 2);

  while(head != NULL){
    cout << head->val << endl;
    head = head->next;
  }
	

	return 0;
}
