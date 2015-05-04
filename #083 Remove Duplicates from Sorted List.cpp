/**
 * Given a sorted linked list, delete all duplicates such that each element
 * appear only once.
 *
 * For example,
 * Given 1->1->2, return 1->2.
 * Given 1->1->2->3->3, return 1->2->3.
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
    ListNode *deleteDuplicates(ListNode *head) {
        if(head==NULL) return NULL;
        ListNode* cur=head;
        while(cur->next){
            if(cur->val!=cur->next->val)
                cur=cur->next;
            else
                cur->next=cur->next->next;
        }
        return head;
    }
};