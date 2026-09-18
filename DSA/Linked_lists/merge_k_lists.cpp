// leetcode 23. Merge k Sorted Lists
#include <vector>
#include <queue>
using namespace std;

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto compare = [](ListNode* a, ListNode* b) {
        return a->val > b->val; // Min-heap
    };
    
    priority_queue<ListNode*, vector<ListNode*>, decltype(compare)> minHeap(compare);
    
    for (auto list : lists) {
        if (list) {
            minHeap.push(list);
        }
    }
    
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();
        
        tail->next = node;
        tail = tail->next;
        
        if (node->next) {
            minHeap.push(node->next);
        }
    }
    
    return dummy.next;
};
//or
ListNode* mergeKlists(ListNode* l1, ListNode* l2){
    ListNode dummy; // we create a dummy node because we want to handle the case when the head of the linked list is merged, so we need to have a previous node to point to the head of the linked list, so we create a dummy node and point it to the head of the linked list
    ListNode* tail = &dummy; // we create a tail pointer to keep track of the last node in the merged linked list, so that we can add the next node to the end of the merged linked list
    while(l1 && l2){
        if(l1->val < l2->val){ // we are comparing the values of the two linked lists, and we are adding the smaller value to the merged linked list
            tail->next = l1; // we are adding the smaller value to the merged linked list
            l1 = l1->next; // we are moving the pointer of the linked list that has the smaller value to the next node
        }else{
            tail->next = l2; // we are adding the smaller value to the merged linked list
            l2 = l2->next; // we are moving the pointer of the linked list that has the smaller value to the next node
        }
        tail = tail->next; // we are moving the tail pointer to the last node in the merged linked list
    }
    if(l1) tail->next = l1; // if there are still nodes in the first linked list, we add them to the merged linked list
    if(l2) tail->next = l2; // if there are still nodes in 
    // the second linked list, we add them to the merged linked list
    return dummy.next;
};

ListNode* mergeKListsDivideAndConquer(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    int k = lists.size();
    while(k > 1){
        for(int i=0; i<k/2; i++){
            lists[i] = mergeKlists(lists[i], lists[k-i-1]);
        }
        k = (k + 1) / 2; // Update k to the new size of the lists after merging
    }
    return lists[0];
}