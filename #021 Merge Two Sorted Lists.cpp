/**
 * Merge two sorted linked lists and return it as a new list. The new list
 * should be made by splicing together the nodes of the first two lists.
 *
 * Tags: Linkedlist
 */

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    //递归做法
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if(l1==NULL)
            return l2;
        if(l2==NULL)
            return l1;
        if(l1->val<l2->val){
            l1->next=mergeTwoLists(l1->next, l2);
            return l1;
        }else{
            l2->next=mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
    
    //非递归做法，使用一个dummy head
    ListNode *mergeTwoLists_II(ListNode *l1, ListNode *l2) {
        ListNode dummy(0);
        ListNode* curNode=&dummy;
        while(l1 && l2){
            if(l1->val<l2->val){
                curNode->next=l1;
                l1=l1->next;
            }else{
                curNode->next=l2;
                l2=l2->next;
            }
            curNode=curNode->next;
        }
        curNode->next=l1?l1:l2;
        return dummy.next;
    }
};
