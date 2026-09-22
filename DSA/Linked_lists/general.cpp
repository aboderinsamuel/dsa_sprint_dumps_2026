//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//leetcode 25. Reverse Nodes in k-Group
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);

        ListNode* prev = &dummy;
        while(true){
            //Find the kth node
            ListNode* check  = prev;
            for(int i=0; i < k; i++){
                check = check->next;
                if(!check){
                    return dummy.next;
                }
            }

            ListNode* curr = prev->next;
            for(int i=0; i<k-1; i++){
                ListNode* nxt = curr->next;
                curr->next = nxt->next;
                nxt->next = prev->next;
                prev->next = nxt;
            }
            prev = curr;
        }
    }
};

// leetcode 92. Reverse Linked List II
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {

        ListNode dummy(0, head);

        ListNode* prev = &dummy;
        for(int i=1; i<left; i++){
            prev = prev->next;
        }

        ListNode* curr = prev->next;
        for(int i=0; i<right-left; i++){
            ListNode* nxt = curr->next;
            curr->next = nxt->next;
            nxt->next = prev->next;
            prev->next = nxt;
        }
        return dummy.next;
    }
};
//leetcode 206. Reverse Linked List
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while(curr){
            ListNode* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        return prev;
    }
};

//leetcode 622. Design Circular Queue
#include <vector>
using namespace std;
class MyCircularQueue {
private:
    vector<int> data;
    int head;
    int count;
    int cap;
public:
    MyCircularQueue(int k) : data(k), head(0), count(0), cap(k){
        
    }
    
    bool enQueue(int value) {
        if(isFull()) return false;
        data[(head+count)%cap] = value;
        count++;
        return true;
    }
    
    bool deQueue() {
        if(isEmpty()) return false;
        head = (head+1)%cap;
        count--;
        return true;
    }
    
    int Front() {
        return isEmpty() ? -1 : data[head];
    }
    
    int Rear() {
        return isEmpty() ? -1 : data[(head+count-1)%cap];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == cap;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
////or.....

// leetcode 460 : LFU Cache
#include <unordered_map>
#include <list>
using namespace std;

class LFUCache{
private:
    struct Entry{
        int value;
        int freq;
        list<int>::iterator it; // pointer to the position of the key in the frequency list
    };

    int cap;
    int minFreq;
    unordered_map<int, Entry> nodes; // key to Entry mapping
    unordered_map<int, list<int>> freqList; // frequency to list of keys mapping

    void touch(int key){
        Entry& e = nodes[key]; // get the entry for the key
        freqList[e.freq].erase(e.it); // remove the key from its current frequency list
        if(freqList[e.freq].empty()){
            freqList.erase(e.freq); // remove the frequency list if it's empty
            if(minFreq == e.freq) minFreq++; // update minFreq if needed
        }
        e.freq++; // increment the frequency
        freqList[e.freq].push_front(key); // add the key to the front of the new frequency list
        e.it = freqList[e.freq].begin(); // update the iterator to the new position
    }

    LFUCache(int capacity) : cap(capacity), minFreq(0) {}

    int get(int key){
        if(!nodes.count(key)) return -1; // key not found
        touch(key); // update the frequency of the key
        return nodes[key].value; // return the value
    }
    void put(int key, int value){
        if(cap <= 0) return; // no capacity
        if(nodes.count(key)){
            nodes[key].value = value; // update the value
            touch(key); // update the frequency
            return;
        }
        if((int)nodes.size() >= cap){
            int evict = freqList[minFreq].back(); // get the least frequently used key
            freqList[minFreq].pop_back(); // remove it from the frequency list
            if(freqList[minFreq].empty()) freqList.erase(minFreq); // remove the frequency list if it's empty
            nodes.erase(evict); // remove the key from the nodes map
        }
        freqList[1].push_front(key); // add the new key to the frequency list for frequency 1
        nodes[key] = {value, 1, freqList[1].begin()}; // add the new key with frequency 1
        minFreq = 1; // reset minFreq to 1
    }

};

// leetcode 146 : LRU Cache
class LRUCache {
private:
    int cap;
    list<pair<int, int>> cache; // list of key-value pairs
    unordered_map<int, list<pair<int, int>>::iterator> pos; // key to iterator mapping

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = pos.find(key);
        if(it == pos.end()) return -1; // key not found
        cache.splice(cache.begin(), cache, it->second); // move the accessed key-value pair
        return it->second->second; // return the value
    }

    void put(int key, int value) {
        auto it = pos.find(key);
        if(it != pos.end()){
            it->second->second = value; // update the value
            cache.splice(cache.begin(), cache, it->second); // move the existing key-value pair to the front
            return;
        }
        if((int)cache.size() == cap){
            pos.erase(cache.back().first); // remove the least recently used key from the map
            cache.pop_back(); // remove the least recently used key-value pair from the list
        }
        cache.emplace_front(key, value); // add the new key-value pair to the front
        pos[key] = cache.begin(); // update the map with the new iterator
    }
};



//leetcode 287 Find the Duplicate Number

class Solution {
public:
    int findDuplicate(vector<int>& nums){
        int slow = nums[0];
        int fast = nums[0];
        do{
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        while(slow != fast);
        slow = nums[0];
        while(slow != fast){
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
//linked lists cycle
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head) return false;

        ListNode* slow = head;
        ListNode* fast = head;

        while(fast != nullptr && fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast) return true;
        }
        return false;
    }
};

// leetcode 143. Reorder List
class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast->next && fast->next->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* prev = nullptr;
        ListNode* curr = slow->next;
        slow->next = nullptr;
        while(curr){
            ListNode* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }

        ListNode* first = head;
        ListNode* second = prev;
        while(second){
            ListNode* n1 = first->next;
            ListNode* n2 = second->next;
            first->next = second;
            second->next = n1;
            first  = n1;
            second = n2;
        }
    }
};
//leetcode 19: Remove Nth Node From End of List
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0, head);
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        for(int i=0; i<=n; i++){
            fast = fast->next;
        }
        while(fast){
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return dummy.next;
    }
};

//leetcode 138. Copy List with Random Pointer
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        unordered_map<Node*, Node*> copy; // old -> new

        // ★ Pass 1: Clone all nodes and store them in the map
        for (Node* cur = head; cur; cur = cur->next) {
            copy[cur] = new Node(cur->val);
        }

        // ★ Pass 2: Connect the next and random pointers for the clones
        for (Node* cur = head; cur; cur = cur->next) {
            copy[cur]->next = copy[cur->next];
            copy[cur]->random = copy[cur->random];
        }

        return copy[head];
    }
};





//TREE
//LEETCODE 199 : Binary Tree Right Side View

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#include <queue>
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int size = q.size();
            for(int i=0; i<size; i++){
                TreeNode* node = q.front();
                q.pop();
                if(i == size-1) result.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return result;
    }
};

// You're asked to walk around the outside of the tree in two parts:
//
// Stand on the left side of the tree.
// Record the nodes you can see (the left view).
// Output them from bottom to top.
// Then stand on the right side of the tree.
// Record the nodes you can see (the right view).
// Output them from top to bottom.
// Don't repeat the root, since it was already included from the left side.
//
// Finally, concatenate the two sequences.
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
};

class Solution {
public:
    vector<int> walkBothSides(TreeNode* root) {
        if (!root) return {};
        vector<int> leftView;
        vector<int> rightView;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i=0; i<levelSize; i++) {
                TreeNode* curr = q.front();
                q.pop();
                if (i == 0) leftView.push_back(curr->val); // First node
                if (i == levelSize - 1) rightView.push_back(curr->val);
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        reverse(leftView.begin(), leftView.end()); // Bottom to top for left view
        for (int i=1; i<rightView.size(); i++) { // Start from 1 to avoid root duplication
            leftView.push_back(rightView[i]);
        }
        return leftView;
    }
};
