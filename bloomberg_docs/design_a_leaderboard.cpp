#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Leaderboard{
private:
    unordered_map<int, int> player_scores; //playerID -> total goals
    int topN; //how many top players to report
public:
    //constructor: store how many top players we'll ever be asked for
    Leaderboard(int n){
        topN = n;
    }
    void recordGoal(int playerId, int goals){
        player_scores[playerId] += goals;
    }
    //Return the topN players's scores in descending order
    vector<int> topPlayers(){
        //Use a min-heap to keep track of the top N players
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        for(auto& entry : player_scores){
            int playerId = entry.first;
            int score = entry.second;
            minHeap.push({score, playerId});
            if(minHeap.size() > topN){
                minHeap.pop();
            }
        }
        vector<int> result;
        while(!minHeap.empty()){
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        reverse(result.begin(), result.end()); //to get descending order
        return result;
    }
};
