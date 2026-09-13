#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

// leetcode 621: Task Scheduler
// https://leetcode.com/problems/task-scheduler/

int leastInterval(vector<int>& tasks, int n){
    vector<int> freq(26, 0);
    for(int task : tasks){
        freq[task - 'A']++;
    }
    priority_queue<int> maxHeap;
    for(int f : freq){
        if(f > 0){
            maxHeap.push(f);
        }
    }
    int time = 0;
    while(!maxHeap.empty()){
        vector<int> temp;
        for(int i = 0; i <= n; i++){
            if(!maxHeap.empty()){
                temp.push_back(maxHeap.top());
                maxHeap.pop();
            }
        }
        for(int f : temp){
            if(--f > 0){
                maxHeap.push(f);
            }
        }
        time += maxHeap.empty() ? temp.size() : n + 1;
    }
    return time;
}

// leetcode 767: Reorganize String
// https://leetcode.com/problems/reorganize-string/

//code plus expanations, no space in between lines:
string reorganizeString(string s) {
    // 1. Build a frequency map for all lowercase English letters
    vector<int> freq(26, 0);
    for(char c : s) {
        freq[c - 'a']++; // Map 'a' -> 0, 'b' -> 1, ..., 'z' -> 25
    }
    
    // 2. Insert all present characters into a Max-Heap
    // Pairs are stored as {frequency, character} so the heap sorts by highest frequency first
    priority_queue<pair<int, char>> maxHeap;
    for(int i = 0; i < 26; i++) {
        if(freq[i] > 0) {
            maxHeap.push({freq[i], (char)(i + 'a')});
        }
    }
    
    string result = "";
    
    // 3. Process pairs of characters to guarantee no identical adjacent elements
    while(maxHeap.size() > 1) {
        // Extract the two most frequent characters available
        auto first = maxHeap.top();   maxHeap.pop();
        auto second = maxHeap.top();  maxHeap.pop();
        
        // Alternatingly append them to the result string
        result += first.second;
        result += second.second;
        
        // Decrement counts and push back into the heap if they have remaining instances
        if(--first.first > 0) {
            maxHeap.push(first);
        }
        if(--second.first > 0) {
            maxHeap.push(second);
        }
    }
    
    // 4. Handle the final remaining character (if any)
    if(!maxHeap.empty()) {
        auto last = maxHeap.top();
        
        // If the last character appears more than once, it's impossible to 
        // place it without it touching itself (e.g., "aa")
        if(last.first > 1) {
            return "";
        }
        
        // Otherwise, safely append the final single character
        result += last.second;
    }
    
    return result;
}

long long totalCost(vector<int>& costs, int k, int candidates){
    int n = costs.size();
    priority_queue<int, vector<int>, greater<int>> left_heap;
    priority_queue<int, vector<int>, greater<int>> right_heap;
    for(int i = 0; i < candidates; i++){
        left_heap.push(costs[i]);
        right_heap.push(costs[n - 1 - i]);
    }
    long long total_cost = 0;
    int left_index = candidates;
    int right_index = n - 1 - candidates;

    for(int i = 0; i < k; i++){
        int left_cost = left_heap.empty() ? INT_MAX : left_heap.top();
        int right_cost = right_heap.empty() ? INT_MAX : right_heap.top();
        
        if(left_cost <= right_cost){
            total_cost += left_cost;
            left_heap.pop();
            if(left_index <= right_index){
                left_heap.push(costs[left_index]);
                left_index++;
            }
        } else {
            total_cost += right_cost;
            right_heap.pop();
            if(left_index <= right_index){
                right_heap.push(costs[right_index]);
                right_index--;
            }
        }
    }
    return total_cost;
}