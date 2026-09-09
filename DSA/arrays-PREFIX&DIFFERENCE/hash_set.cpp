#include <unordered_set>
#include <vector>

using namespace std;

bool containsDuplicate(vector<int> nums){
    unordered_set<int> seen;
    for(int x : nums){
        if(seen.count(x)) return true;
        seen.insert(x);
    }
    return false;
}
//sub-pattern bucket counting