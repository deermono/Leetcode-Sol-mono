/**
 * Given a list, rotate the list to the right by k places, where k is
 * non-negative.
 *
 * For example:
 * Given 1->2->3->4->5->NULL and k = 2,
 * return 4->5->1->2->3->NULL.
 *
 * Tags: Linked List, Two Pointers
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
    //求出链表长度，然后得到rotate处的listnode
    ListNode* rotateRight(ListNode* head, int k) {
        if(head==NULL || head->next==NULL || k==0) return head;
        int len=1;
        ListNode *tail=head;
        while(tail->next){
            len++;
            tail=tail->next;
        }
        k%=len;
        tail->next=head;
        for(int i=0;i<len-k;i++)
            tail=tail->next;
        head=tail->next;
        tail->next=NULL;
        return head;
    }
    
    //使用两个指针，其中fast比slow先走k步
    //这样fast到达链表末尾时，slow就到了rotate处
    //需注意的是，如果k大于链表长度，在fast走完第一遍时计算一下k%len
    //如果不计算len，只是将fast重新指回head逻辑上是可以的
    //但是如果k远大于len，将会多走非常多步，TLE
    ListNode* rotateRight_II(ListNode* head, int k) {
        if(head==NULL || k==0) return head;
        int len=1;
        ListNode *slow=head;
        ListNode *fast=head;
        while(k--){
            if(fast->next!=NULL){
                fast=fast->next;
                len++;
            }else{
                fast=head;
                k%=len;
                if(k==0)
                    return head;
            }
        }
        while(fast->next!=NULL){
            slow=slow->next;
            fast=fast->next;
        }
        fast->next=head;
        head=slow->next;
        slow->next=NULL;
        return head;
    }
};
