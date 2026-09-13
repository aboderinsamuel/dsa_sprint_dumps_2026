#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class LotterySystem{
private:
    unordered_map<int, int> indexOf;
    vector<int> participants;
public:
    LotterySystem(){}
    bool isgnUp(int id){
        if(indexOf.count(id)) return false;
        participants.push_back(id);
        indexOf[id] = participants.size() - 1; // record where we just put it in the array
        return true;
    }
    bool signOut(int id){
        if(!indexOf.count(id)) return false;
        int indexToRemove = indexOf[id];
        int lastIndex = participants.back();

        //move the last person into the slow we're vacating
        participants[indexToRemove] = lastIndex;
        indexOf[lastIndex] = indexToRemove;
        participants.pop_back();
        indexOf.erase(id);
        return true;
    }
    int drAwWinner(){
        int randomIndex = rand() % participants.size();
        return participants[randomIndex];
    }
};
// Time Complexity: O(1) for signUp, signOut, and drawWinner
// Space Complexity: O(n) where n is the number of participants