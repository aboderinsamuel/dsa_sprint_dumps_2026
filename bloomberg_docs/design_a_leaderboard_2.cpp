#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

class LeaderBoard{
private:
    unordered_map<int, int> scores; // playerId -> total score  
public:
    void addScore(int playerId, int score){
        // Implement the logic to add score for the player
        scores[playerId] += score;
    }
    int top(int k){
        priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap to keep track of top k scores
        for(auto& [id, score] : scores){
            minHeap.push(score);
            if(minHeap.size() > k){
                minHeap.pop();
            }
        }
        int total = 0;
        while(!minHeap.empty()){
            total += minHeap.top();
            minHeap.pop();
        }
        return total;
    }
    void reset(int playerId){
        scores.erase(playerId);
    }
};
//time:
//addScore : O(1)
//Reset O(1)
//Top O(n log k)

//Space:
//O(n)