#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

bool carPooling(vector<vector<int>>& trips, int capacity){
    sort(trips.begin(), trips.end(), [](const vector<int>& a, const vector<int>& b){
        return a[1] < b[1];
    });
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    int passengers = 0;
    for(auto& trip : trips){
        int numPassengers = trip[0];
        int from = trip[1];
        int to = trip[2];

        while(!minHeap.empty() && minHeap.top().first <= from){
            passengers -= minHeap.top().second;
            minHeap.pop();
        }
        passengers += numPassengers;
        if(passengers > capacity){
            return false;
        }
        minHeap.push({to, numPassengers});
    }
    return true;
};