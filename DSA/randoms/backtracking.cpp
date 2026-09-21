#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        // Calculate the total perimeter using long long to avoid overflow
        long long total_length = accumulate(matchsticks.begin(), matchsticks.end(), 0LL);
        
        // Optimization 1: A square must have 4 equal sides
        if (total_length % 4 != 0) {
            return false;
        }
        
        int target_side = total_length / 4;
        
        // Optimization 2: Sort descending so larger sticks fail early
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());
        
        // If any single stick is longer than the target side, it's impossible
        if (matchsticks > target_side) {
            return false;
        }
        
        // Tracks the current length of the 4 sides
        vector<int> sides(4, 0);
        
        return backtrack(0, matchsticks, sides, target_side);
    }

private:
    bool backtrack(int index, const vector<int>& matchsticks, vector<int>& sides, int target) {
        // Base Case: Every stick has been safely placed
        if (index == matchsticks.size()) {
            return true;
        }
        
        int current_stick = matchsticks[index];
        
        // Loop through the 4 available sides
        for (int i = 0; i < 4; ++i) {
            if (sides[i] + current_stick <= target) {
                sides[i] += current_stick; // Choose
                
                if (backtrack(index + 1, matchsticks, sides, target)) { // Explore
                    return true;
                }
                
                sides[i] -= current_stick; // Unchoose (Backtrack)
            }
            
            // Optimization 3: If this side remains 0 after backtracking, 
            // skipping subsequent empty sides avoids duplicate evaluation branches.
            if (sides[i] == 0) {
                break;
            }
        }
        
        return false;
    }
};
