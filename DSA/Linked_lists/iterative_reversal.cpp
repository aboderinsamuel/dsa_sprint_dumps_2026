//leetcode 206. Reverse Linked List

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution{
public:
    ListNode* reverseList(ListNode* head){
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while(curr != nullptr){ // this means that we are traversing the linked list until we reach the end of the linked list
            ListNode* nextTemp = curr->next; // we are storing the next node in a temporary variable because we are going to change the next pointer of the current node to point to the previous node, so we need to store the next node in a temporary variable so that we don't lose it
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }
};
//leetcode 92. Reverse Linked List II
ListNode* reverseBetween(ListNode* head, int left, int right) {
    if(!head) return nullptr;
    ListNode* dummy = new ListNode(0); // we create a dummy node because we want to handle the case when the left node is the head of the linked list, so we need to have a previous node to point to the left node, so we create a dummy node and point it to the head of the linked list
    dummy->next = head; // we point the next pointer of the dummy node to the head of the linked list
    ListNode* prev = dummy;
    ListNode* curr = prev->next; // this is the left node
    ListNode* nextTemp;

    for(int i = 0; i < left - 1; i++) // we are moving the prev pointer to the node before the left node
        prev = prev->next;

    for(int i = 0; i < right - left; i++){ // we are reversing the linked list from left to right
        nextTemp = curr->next; // we are storing the next node in a temporary variable because we are going to change the next pointer of the current node to point to the previous node, so we need to store the next node in a temporary variable so that we don't lose it
        curr->next = nextTemp->next; // we are changing the next pointer of the current node to point to the next node of the next node
        nextTemp->next = prev->next; // we are changing the next pointer of the next node to point to the previous node
        prev->next = nextTemp; // we are changing the next pointer of the previous node to point to the next node
    }
    return dummy->next;
};

//leetcode 25. Reverse Nodes in k-Group
ListNode* reverseKGroup(ListNode* head, int k) {
    if(!head || k == 1) return head; // if the head is null or k is 1, then we don't need to reverse the linked list
    ListNode* dummy = new ListNode(0); // we create a dummy node because we want to handle the case when the head of the linked list is reversed, so we need to have a previous node to point to the head of the linked list, so we create a dummy node and point it to the head of the linked list
    dummy->next = head; // we point the next pointer of the dummy node to the head of the linked list
    ListNode* prev = dummy;
    ListNode* curr = head;
    ListNode* nextTemp;

    int count = 0; // we are counting the number of nodes in the linked list
    while(curr != nullptr){ // this means that we are traversing the linked list until we reach the end of the linked list
        count++;
        curr = curr->next;
    }

    while(count >= k){ // this means that we have at least k nodes in the linked list
        curr = prev->next; // this is the first node in the group of k nodes
        nextTemp = curr->next; // this is the second node in the group of k nodes

        for(int i = 1; i < k; i++){ // we are reversing the group of k nodes
            curr->next = nextTemp->next; // we are changing the next pointer of the current node to point to the next node of the next node
            nextTemp->next = prev->next; // we are changing the next pointer of the next node to point to the previous node
            prev->next = nextTemp; // we are changing the next pointer of the previous node to point to the next node
            nextTemp = curr->next; // we are moving the nextTemp pointer to the next node in the group of k nodes
        }
        prev = curr; // we are moving the prev pointer to the last node in the group of k nodes
        count -= k; // we are decrementing count by k because we have reversed a group of k nodes
    }
    return dummy->next;
}
