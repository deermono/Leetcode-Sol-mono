/**
 * Merge k sorted linked lists and return it as one sorted list. Analyze and
 * describe its complexity.
 *
 * Tags: Divide and Conquer, Linkedlist, Heap
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    //使用优先级队列，需要自定义比较函数
    struct compare{
        bool operator()(const ListNode* l1, ListNode* l2){
            return l1->val>l2->val;
        }
    };
    
    ListNode* mergeKLists_I(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, compare> heap;
        for(int i=0;i<lists.size();i++)
            if(lists[i])
                heap.push(lists[i]);
        ListNode dummy(0);
        ListNode* curNode=&dummy;
        while(!heap.empty()){
            curNode->next=heap.top();
            heap.pop();
            curNode=curNode->next;
            if(curNode->next)
                heap.push(curNode->next);
        }
        return dummy.next;
    }
    
    //使用mergeTwoLists()
    ListNode* mergeKLists_II(vector<ListNode*>& lists) {
        if(lists.empty())
            return NULL;
        int len=lists.size();
        while(len>1){
            for(int i=0;i<len/2;i++)
                lists[i]=mergeTwoLists(lists[i], lists[len-1-i]);
            len=(len+1)/2;
        }
        return lists[0];
    }
    
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
};
