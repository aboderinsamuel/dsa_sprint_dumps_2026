#include <vector>
#include <algorithm>

//leetcode 611. Valid Triangle Number
class Solution {
public:
    int triangleNumber(std::vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        
        // Step 1: Sort the array
        std::sort(nums.begin(), nums.end());
        int count = 0;
        
        // Step 2: Fix the largest side 'c' at index k
        for (int k = n - 1; k >= 2; --k) {
            int left = 0;
            int right = k - 1;
            
            // Step 3: Two-pointer search for valid 'a' and 'b'
            while (left < right) {
                if (nums[left] + nums[right] > nums[k]) {
                    // If nums[left] + nums[right] > nums[k], then every element 
                    // from left to right-1 added to nums[right] is also > nums[k].
                    count += (right - left);
                    --right; // Decrement right to look for smaller pairs
                } else {
                    ++left;  // Increment left to increase the sum
                }
            }
        }
        
        return count;
    }
};
