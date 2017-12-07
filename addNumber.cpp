#include <iostream>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}

    ListNode* push_back(int val) {
        ListNode* head = this; 
        ListNode* node = new ListNode(val);
        while(head->next) {
            head = head->next;
        }
        head->next = node;
        return this;
    }

    void showList() {
        ListNode* head = this;
        cout << "List Data: " << endl;
        while(head) {
            cout << head->val << " -> ";
            head = head->next;
        }
        cout <<endl;
    }
};
 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(NULL == l1) { return l2; }
        if(NULL == l2) { return l1; }
        
        int value = 0, pre = 0, mod = 0;
        ListNode *tempNode = new ListNode(0);
        ListNode *first = l1, *curl1;
        while(l1 && l2) {
            value = l1->val + l2->val;
            pre = value / 10;
            mod = value % 10;
            l1->val = mod + tempNode->val;
            curl1 = l1;
            l1 = l1->next;
            l2 = l2->next;
            tempNode->val = pre;
        }
        if(l1 == NULL && l2 == NULL && pre == 1) {
            tempNode->val = pre;
            curl1->next = tempNode;
        }
        
        if(l1) {
            l1->val = l1->val + pre;
        }
        
        if(l2) {
            l2->val = l2->val + pre;
            curl1->next = l2;
        }
        return first;
    }
};

int main() {
    ListNode *l1 = new ListNode(5);
    l1->push_back(4)->push_back(8);
    ListNode *l2 = new ListNode(5);
    l2->push_back(7)->push_back(4)->push_back(6)->push_back(3);

    l1->showList();
    l2->showList();

    Solution *s = new Solution();
    s->addTwoNumbers(l1, l2);
    l1->showList();

    
    
    return 0;
}
