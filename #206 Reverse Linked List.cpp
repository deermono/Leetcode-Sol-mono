/**
 * Reverse a singly linked list.
 *
 * Hint:
 * A linked list can be reversed either iteratively or recursively.
 * Could you implement both?
 *
 * Tags: Linked List
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
    /**
     * 1->2->3->4->NULL
     * 1->NULL, 2->3->4->NULL
     * 2->1->NULL, 3->4->NULL
     * 3->2->1->NULL, 4->NULL
     * 4->3->2->1->NULL
     */
    ListNode* reverseList(ListNode* head) {
        ListNode *prev=NULL;
        ListNode *cur=head;
        ListNode *next;
        while(cur){
            next=cur->next;
            cur->next=prev;
            prev=cur;
            cur=next;
        }
        return prev;
    }
    
    /**
     * 1->2->3->4->NULL
     * 2->1->3->4->NULL
     * 3->2->1->4->NULL
     * 4->3->2->1->NULL
     */
    ListNode* reverseList_I(ListNode* head) {
        if(head==NULL) return head;
        ListNode *cur=head;
        while(cur->next){
            ListNode *tmp=cur->next;
            cur->next=tmp->next;
            tmp->next=head;
            head=tmp;
        }
        return head;
    }
    
    /**
     * 递归
     * 1->2->3->4->NULL
     * 1->NULL, reverse(2->3->4->NULL) --> 4->3->2->NULL, 2->next=1
     * 2->NULL, reverse(3->4->NULL) --> 4->3->NULL, 3->next=2
     * 3->NULL, reverse(4->NULL) --> 4->NULL, 4->next=3
     */
    ListNode* reverseList_II(ListNode* head) {
        if(head==NULL || head->next==NULL) return head;
        ListNode *tail=head;
        ListNode *cur=head->next;
        tail->next=NULL;
        head=reverseList(cur);
        cur->next=tail;
        return head;
    }
    
    /**
     * 递归
     * 1->2->3->4->NULL
     * 1->NULL, reverse(2->3->4->NULL, 1->NULL)
     * 2->1->NULL, reverse(3->4->NULL, 2->1->NULL,)
     * 3->2->1->NULL, reverse(4->NULL, 3->2->1->NULL) 
     * 4->3->2->1->NULL, reverse(NULL, 4->3->2->1->NULL)
     * return 4->3->2->1->NULL
     */
    ListNode* reverseList_III(ListNode* head) {
        return reverse(head, NULL);
    }
    
    ListNode* reverse(ListNode* head, ListNode* tail){
        if(head==NULL) return tail;
        ListNode* cur=head->next;
        head->next=tail;
        return reverse(cur, head);
    }
};