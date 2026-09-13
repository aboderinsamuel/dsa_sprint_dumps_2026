#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
using namespace std;

//leetcode 703: Kth Largest Element in a Stream

class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k;
public:
    KthLargest(vector<int>& nums, int k){
        this->k = k;
        for(int num : nums){
            minHeap.push(num);
            if(minHeap.size() > k){
                minHeap.pop();
            }
        }
    }
    int add(int val){
        minHeap.push(val);
        if(minHeap.size() > k){
            minHeap.pop();
        }
        return minHeap.top();
    }
};

//leetcode 973: K Closest Points to Origin
class Solution {
private:
    priority_queue<pair<int, vector<int>>> maxHeap;
public:
    vector<vector<int>> KClosest(vector<vector<int>>& points, int k){
        for(auto& point : points){
            int x = point[0];
            int y = point[1];
            int dist = x * x + y * y;
            maxHeap.push({dist, point});
            if(maxHeap.size() > k){
                maxHeap.pop();
            }
        }
        vector<vector<int>> result;
        while(!maxHeap.empty()){
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        return result;  
    }
};

// leetcode 347: Top K Frequent Elements
class Solution {
public:
    vector<int> topKfrequent(vector<int>& nums, int k){
        unordered_map<int, int> freqMap;
        for(int num : nums){
            freqMap[num]++;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        for(auto& entry : freqMap){
            minHeap.push({entry.second, entry.first});
            if(minHeap.size() > k){
                minHeap.pop();
            }
        }
        vector<int> result;
        while(!minHeap.empty()){
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return result;
    }
};

// leetcode 1046: Last Stone Weight
class Solution {
private:
    priority_queue<int> maxHeap;
public:
    int lastStoneWeight(vector<int>& stones){
        for(int stone : stones){
            maxHeap.push(stone);
        }
        while(maxHeap.size() > 1){
            int stone1 = maxHeap.top();
            maxHeap.pop();
            int stone2 = maxHeap.top();
            maxHeap.pop();
            if(stone1 != stone2){
                maxHeap.push(stone1 - stone2);
            }
        }
        return maxHeap.empty() ? 0 : maxHeap.top();
    }
};