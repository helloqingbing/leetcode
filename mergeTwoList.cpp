#include <list>
#include <iostream>
using namespace std;

struct ListNode {

    int value;
    ListNode* next;
    ListNode(int v):value(v),next(NULL) {}
};


ListNode* mergeList(ListNode* l1, ListNode* l2) {
    if(NULL == l1) return l2;
    if(NULL == l2) return l1;

    ListNode dumy(-1);
    ListNode* p = &dumy;
    while(l1 || l2) {
        int v1 = l1 ? l1->value: INT_MAX;
        int v2 = l2 ? l2->value: INT_MAX;
        if(v1 <= v2) {
            p->next = l1;
            l1 = l1->next;
        } else {
            p->next = l2;
            l2 = l2->next;
        }
        p = p->next;
    }
    return dumy.next;
}
