//leetcode 141. Linked List Cycle
#include <climits>
#include <vector>

using namespace std;

class ListNode{
public:
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL){}
};

class Solution{
public:
    bool hasCycle(ListNode* head){
        if(!head) return false;
        // this is the slow pointer
        ListNode* slow = head;
        // this is the fast pointer
        ListNode* fast = head;

        while(fast != nullptr && fast->next != nullptr) // the reason we are using the fast pointer here and not the slow pointer is because the fast pointer is moving at a faster pace and it will reach the end of the linked list first if there is no cycle
        {
            slow = slow->next; // move the slow pointer by one step
            fast = fast->next->next; // move the fast pointer by two steps

            if(slow == fast) // if the slow pointer and the fast pointer meet, then there is a cycle in the linked list
                return true;
        }
        return false; // if the fast pointer reaches the end of the linked list, then there is no cycle in the linked list
    }
};

//leetcode 876. Middle of the Linked List
ListNode* middleNode(ListNode* head) {
    if(!head) return nullptr;
    ListNode* slow = head;
    ListNode* fast = head;

    while(fast != nullptr && fast->next != nullptr) // the reason we are using the fast pointer here and not the slow pointer is because the fast pointer is moving at a faster pace and it will reach the end of the linked list first if there is no cycle
    {
        slow = slow->next; // move the slow pointer by one step
        fast = fast->next->next; // move the fast pointer by two steps
    }
    return slow; // when the fast pointer reaches the end of the linked list, the slow pointer will be at the middle of the linked list HOW do we know that?: Because the fast pointer moves twice as fast as the slow pointer, so when the fast pointer reaches the end, the slow pointer will be at the middle.
}
//leetcode 287. Find the Duplicate Number
int findDuplicate(vector<int>& nums) {
    int slow = nums[0]; // this is the slow pointer
    int fast = nums[0]; // this is the fast pointer
    do{
        slow = nums[slow]; // move the slow pointer by one step
        fast = nums[nums[fast]]; // move the fast pointer by two steps
    }
    while(slow != fast); // if the slow pointer and the fast pointer meet, then there is a cycle in the linked list
    slow = nums[0]; // reset the slow pointer to the beginning of the linked list
    while(slow != fast) // if the slow pointer and the fast pointer meet, then there is a cycle in the linked list
    {
        slow = nums[slow]; // move the slow pointer by one step
        fast = nums[fast]; // move the fast pointer by one step
    }
    return slow; // when the slow pointer and the fast pointer meet, that is the duplicate number
};

//;leetcode 142. Linked List Cycle II

ListNode* detectCycle(ListNode* head) {
    if(!head) return nullptr;
    ListNode* slow = head; // this is the slow pointer
    ListNode* fast = head; // this is the fast pointer
    while(fast != nullptr && fast->next != nullptr) // the reason we are using the fast pointer here and not the slow pointer is because the fast pointer is moving at a faster pace and it will reach the end of the linked list first if there is no cycle
    {
        slow = slow->next; // move the slow pointer by one step
        fast = fast->next->next; // move the fast pointer by two steps
        if(slow == fast) // if the slow pointer and the fast pointer meet, then there is a cycle in the linked list
        {
            slow = head; // reset the slow pointer to the beginning of the linked list
            while(slow != fast) // if the slow pointer and the fast pointer meet, then there is a cycle in the linked list
            {
                slow = slow->next; // move the slow pointer by one step
                fast = fast->next; // move the fast pointer by one step
            }
            return slow; // when the slow pointer and the fast pointer meet, that is the start of the cycle in the linked list
        }
    }
    return nullptr; // if there is no cycle in the linked list, return nullptr
}