/**
 * Remove all elements from a linked list of integers that have value val.
 * 
 * Example
 * Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
 * Return: 1 --> 2 --> 3 --> 4 --> 5
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
    //递归
    ListNode* removeElements(ListNode* head, int val) {
        if(head==NULL) return head;
        if(head->val==val)
            return removeElements(head->next, val);
        else{
            head->next=removeElements(head->next, val);
            return head;
        }
    }
    
    //使用double pointer
    ListNode* removeElements_I(ListNode* head, int val) {
        ListNode **p=&head;
        while(*p){
            if((*p)->val==val)
                *p=(*p)->next;
            else
                p=&(*p)->next;
        }
        return head;
    }
    
    //使用dummy head
    ListNode* removeElements_II(ListNode* head, int val) {
        ListNode dummy(0);
        dummy.next=head;
        ListNode* cur=&dummy;
        while(cur->next){
            if(cur->next->val==val)
                cur->next=cur->next->next;
            else
                cur=cur->next;
        }
        return dummy.next;
    }
};