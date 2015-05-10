/**
 * Given a linked list, swap every two adjacent nodes and return its head.
 *
 * For example,
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 *
 * Your algorithm should use only constant space. You may not modify the values
 * in the list, only nodes itself can be changed.
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
    //使用double pointer
    ListNode *swapPairs(ListNode *head) {
        //p是指针的指针，也就是存放了head的地址
        //所以*p就相当于指向head
        ListNode **p=&head;
        while (*p && (*p)->next) {
            ListNode *t=(*p)->next;
            (*p)->next=t->next;
            t->next=*p;
            //将*p指向的东西改变了，注意，并非p指向的东西
            //对第一次交换来说，head本来指向Node1，现在变成了指向Node2（新的链表头）
            *p=t;
            //将p存放的指针的地址改变了
            //对第一次交换来说，p先前存放的是head，此后p和head就没有关系了
            p=&(*p)->next->next;
        }
        return head;
    }
    
    //使用dummy head
    ListNode* swapPairs_I(ListNode* head) {
        ListNode dummy(0);
        dummy.next=head;
        ListNode* cur=&dummy;
        while(cur->next && cur->next->next){
            ListNode* tmp=cur->next->next;
            cur->next->next=tmp->next;
            tmp->next=cur->next;
            cur->next=tmp;
            cur=cur->next->next;
        }
        return dummy.next;
    }
};
