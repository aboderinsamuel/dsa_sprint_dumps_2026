#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

class Solution{
private:
//this is to store the check-in information for each passenger
// example: checkIns[1] = {"A", 3} means passenger with id 1 checked in at station "A" at time 3
// reason: to efficiently calculate the travel time when the passenger checks out
    unordered_map<int, pair<string, int>> checkIns;
    //this is to store the total travel time and count of trips for each station pair
    //examplt: checkOuts["A->B"] = {totalTime, count}
    //example: checkOuts["A->B"] = {10, 2} means total travel time from station "A" to 
    //station "B" is 10 and there have been 2 trips
    // reason: to efficiently calculate the average travel time between any two stations
    unordered_map<string, pair<int, int>> checkOuts;
public:
    void checkIn(int id, string stationName, int t){
        checkIns[id] = {stationName, t};
    }
    
    void checkOut(int id, string stationName, int t){
        auto [startStation, startTime] = checkIns[id];
        int travelTime = t - startTime;
        auto& [totalTime, count] = checkOuts[startStation + "->" + stationName];
        totalTime += travelTime;
        count++;
    }
    
    double getAverageTime(string startStation, string endStation){
        auto& [totalTime, count] = checkOuts[startStation + "->" + endStation];
        return (double)totalTime / count;
    } 
};
