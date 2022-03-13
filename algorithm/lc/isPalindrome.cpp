/*************************************************************************
    > File Name: isPalindrome.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月26日 星期日 12时22分08秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

/**
  思路：快慢指针：慢指针移动一个节点，快指针移动两个节点，移动完成后慢指针正好在中间.
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    bool isPalindrome(ListNode* head) {
      if (!head || !head->next)
        return true;
      ListNode *fast = head, *slow = head;
      ListNode* cur = head;
      ListNode* pre = NULL;
      while (fast && fast->next) {
        cur = slow;
        slow = slow->next;        //快指针移动一个节点
        fast = fast->next->next;  //慢指针移动两个节点
        //反转节点
        cur->next = pre;
        pre = cur;
      }
      //如果fast为真说明是有基数个节点，应该跳过该节点.
      if (fast) {
        slow = slow->next;
      }
      //比较，判断是否会回文链表
      while (cur) {
        if (cur->val != slow->val) {
          return false;
        }
        cur = cur->next;
        slow = slow->next;
      }
			return true;
    }
};

int main(){
	vector<int>	 v = {1,2,3,2,1};
  bool ishead = true;
  ListNode* head = NULL;
  ListNode* p = NULL;
	for(vector<int>::reverse_iterator riter = v.rbegin(); riter != v.rend(); ++riter){
	  if (ishead) {
      head = new ListNode(*riter);
      ishead = false;
    } else {
      p = new ListNode(*riter);
      p->next = head;
      head = p;
    }
	}
  /**
  while (head) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;
  */
  Solution s;
  bool res = s.isPalindrome(head);
  cout << "res=" << res << endl;
	return 0;
}
