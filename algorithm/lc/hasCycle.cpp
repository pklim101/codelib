/*************************************************************************
    > File Name: hasCycle.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月26日 星期日 13时12分31秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include<stack>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution1 {
public:
    bool hasCycle(ListNode *head) {
        unordered_map <ListNode *,int> m;
        while(head)
        {
            m[head]++;
            if(m[head] > 1)      return true;
            head = head->next;
        }
        return false;
    }
};


 
class Solution {
public:
    bool hasCycle(ListNode *head) {
      map<ListNode*,int> tmp; //注意：是要找节点，而不是找head->val， 因为head->val也可能重复.
      map<ListNode*,int>::iterator iter;
      if (!head || !head->next) {
        return false;
      }
			while(head){
				iter = tmp.find(head);
				if(iter != tmp.end()){
					return true;  
				} else {
					false;
				}
        tmp.insert(pair<ListNode*,int>(head, 0));
        head = head->next;
			}
			return false;        
    }
};

int main(){
	vector<int> v = {1,2,3};
	ListNode* head = nullptr, *p = nullptr, *pos = nullptr, *tail = nullptr;
	bool ishead = true;
	for (vector<int>::reverse_iterator riter = v.rbegin(); riter != v.rend(); ++riter) {
		if (ishead) {
			head = new ListNode(*riter);
			ishead = false;
			tail = head;
		}	else {
			p = new ListNode(*riter);
			p->next = head;
			head = p;
		}
	}
	tail->next = head;

	/**
	while(head){
		cout << head->val << endl;
		head = head->next;
	}
	*/
  Solution s ;
  bool res = s.hasCycle(head);
  cout << res << endl;


	return 0;
}
