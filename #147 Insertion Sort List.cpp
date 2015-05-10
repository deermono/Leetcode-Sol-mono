/**
 * Sort a linked list using insertion sort.
 *
 * Tags: Linkedlist, Sort
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
     * 使用double pointer
     * 检测(*p)->next，默认head排好序
     * 如果待排序数比前面一个大，说明它在正确的位置，直接跳过
     * 如果不在正确位置，就从头找第一个比它大的数
     * 例如1->2->3->5->4->NULL
     * 现在要插入4
     * 经过while循环，pos现在是3->next的地址（注意，非常重要，不是5而是3->next的地址）
     * 然后(*p)->next=t->next; --> 5->NULL
     * t->next=*pos; 4->5
     * *pos=t; 3->4
     */
    ListNode* insertionSortList(ListNode* head) {
        ListNode **p=&head;
        while(*p && (*p)->next){
            if((*p)->next->val<(*p)->val){
                ListNode **pos=&head;
                ListNode *t=(*p)->next;
                while((*pos)->val<t->val)
                    pos=&(*pos)->next;
                (*p)->next=t->next;
                t->next=*pos;
                //*pos指向的东西变了
                *pos=t;
            }
            else
                p=&(*p)->next;
        }
        return head;
    }
    
    //使用dummy head
    ListNode* insertionSortList_I(ListNode* head) {
        ListNode dummy(INT_MIN);
        ListNode *cur=head;
        while(cur){
            ListNode *pos=&dummy;
            ListNode *tmp=cur->next;
            while(pos->next && pos->next->val<cur->val)
                pos=pos->next;
            cur->next=pos->next;
            pos->next=cur;
            cur=tmp;
        }
        return dummy.next;
    }

};
