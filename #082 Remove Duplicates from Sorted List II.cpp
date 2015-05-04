/**
 * Given a sorted linked list
 * delete all nodes that have duplicate numbers
 * leaving only distinct numbers from the original list.
 *
 * Given 1->2->3->3->4->4->5, return 1->2->5.
 * Given 1->1->1->2->3, return 2->3.
 *
 * Tag: Linkedlist
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
    //递归
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==NULL || head->next==NULL) return head;
        if(head->val!=head->next->val){
            head->next=deleteDuplicates(head->next);
            return head;
        }else{
            while(head->next && head->val==head->next->val)
                head=head->next;
            head=head->next;
            return(deleteDuplicates(head));
        }
    }
    
    //使用double pointer
    ListNode* deleteDuplicates_I(ListNode* head) {
        ListNode **p=&head;
        while(*p){
            if((*p)->next && (*p)->val==(*p)->next->val){
                ListNode *t=(*p)->next->next;
                while(t && (*p)->val==t->val)
                    t=t->next;
                *p=t;
            }else
                p=&(*p)->next;
        }
        return head;
    }
    
    //使用dummy head
    ListNode* deleteDuplicates_II(ListNode* head) {
        ListNode dummy(0);
        dummy.next=head;
        ListNode* pre=&dummy;
        ListNode* cur=head;
        while(cur){
            if(cur->next && cur->val==cur->next->val){
                while(cur->next && cur->val==cur->next->val)
                    cur=cur->next;
                cur=cur->next;
                pre->next=cur;
            }else{
                cur=cur->next;
                pre=pre->next;
            }
        }
        return dummy.next;
    }
};
