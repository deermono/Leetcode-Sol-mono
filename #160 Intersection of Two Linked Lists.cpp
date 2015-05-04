/**
 * Write a program to find the node at which the intersection of two singly
 * linked lists begins.
 *
 * For example, the following two linked lists:
 *
 * A:          a1 → a2
 *                    ↘
 *                      c1 → c2 → c3
 *                    ↗
 * B:     b1 → b2 → b3
 * begin to intersect at node c1.
 *
 * Notes:
 * If the two linked lists have no intersection at all, return null.
 * The linked lists must retain their original structure after the function
 * returns.
 * You may assume there are no cycles anywhere in the entire linked structure.
 * Your code should preferably run in O(n) time and use only O(1) memory.
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
    //让两个链表分别走m+n长度，如果有交集就会在交换序列之后相遇
    //如果没有交集的话就是同时到了末尾但仍然不相等
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA==NULL || headB==NULL) return NULL;
        ListNode *p1=headA;
        ListNode *p2=headB;
        while(p1!=p2){
            p1=(p1->next==NULL)?headB:p1->next;
            p2=(p2->next==NULL)?headA:p2->next;
            if(p1->next==NULL && p2->next==NULL && p1!=p2)
                return NULL;
        }
        return p1;
    }
    
    //首先计算两个链表的长度，让较长的链表先走完多余的部分，同样长度时开始检测两个链表是否相交
    ListNode *getIntersectionNode_I(ListNode *headA, ListNode *headB) {
        int l1=0, l2=0;
        ListNode* curA=headA;
        ListNode* curB=headB;
        while(curA){
            l1++;
            curA=curA->next;
        }
        while(curB){
            l2++;
            curB=curB->next;
        }
        curA=headA, curB=headB;
        if(l1>l2)
            for(int i=0;i<l1-l2;i++)
                curA=curA->next;
        else
            for(int i=0;i<l2-l1;i++)
                curB=curB->next;
        while(curA!=curB){
            curA=curA->next;
            curB=curB->next;
        }
        return curA;
    }
};
