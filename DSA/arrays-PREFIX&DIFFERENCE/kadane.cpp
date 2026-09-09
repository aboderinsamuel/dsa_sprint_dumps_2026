#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// At its heart, Kadane's Algorithm is a dynamic programming technique used to find the maximum sum of a contiguous subarray. 
// The beauty of Kadane’s is that it reduces a brute force \(O(n^2)\) problem down to a highly optimized \(O(n)\) time complexity and \(O(1)\) space complexity. 
// [1] (https://www.youtube.com/watch?v=hLPkqd60-28&t=123), [2] (https://yuminlee2.medium.com/kadanes-algorithm-maximum-subarray-sum-da29008a7753), 
//     [3] (https://neetcode.io/solutions/maximum-subarray)Instead of looking at every single possible subarray, the algorithm focuses on a single choice at 
//         each step as you iterate through the array: [1] (https://algo.monster/liteproblems/53), [2] (https://www.geeksforgeeks.org/dsa/largest-sum-contiguous-subarray/)"
//             At index i, should I extend the existing subarray, or should I throw it away and start a completely new subarray from this element?" 
//             [1] (https://www.geeksforgeeks.org/dsa/largest-sum-contiguous-subarray/), [2] (https://algo.monster/liteproblems/53)It keeps track of two variables
//             :current_sum: The maximum sum of a subarray ending at the current position.max_sum: The global maximum sum discovered across the entire array so far. 
//             [1] (https://yuminlee2.medium.com/kadanes-algorithm-maximum-subarray-sum-da29008a7753), [2] (https://www.geeksforgeeks.org/dsa/largest-sum-contiguous-subarray/), 
//             [3] (https://www.youtube.com/watch?v=hLPkqd60-28&t=123)If current_sum ever drops below zero, it means adding it to subsequent elements will only pull their sums down. 
//             Thus, you drop the current chain and reset current_sum to 0 (or start fresh with the current element). [1] (https://www.youtube.com/watch?v=AHZpyENo7k4&t=928), 
//             [2] (https://neetcode.io/solutions/maximum-subarray)

//LeetCode 53: Maximum Subarray 
int maxSubArray(vector<int>& nums){
    int max_sum = INT_MIN;
    int current_sum = 0;
    for(int num : nums){
        current_sum += num;
        if(current_sum > max_sum){
            max_sum = current_sum;
        }
        if(current_sum < 0){
            current_sum = 0;
        }
    }
    return max_sum;
};

// leetcode 152: Maximum Product Subarray
int maxProduct(vector<int>& nums){
    int max_product = INT_MIN;
    int current_max = 1;    
    int current_min = 1;
    for(int num : nums){
        if(num < 0){
            swap(current_max, current_min);
        }
        current_max = max(num, current_max*num);
        current_min = min(num, current_min*num);
        max_product = max(max_product, current_max);
    }
    return max_product;
}

// leetcode 918: Maximum Sum Circular Subarray
int maxSubarraySumCircular(vector<int>& nums){
    int total_sum = 0;
    int max_sum = nums[0];
    int min_sum = nums[0];
    int current_max = 0;
    int current_min = 0;


    for(int num : nums){
        total_sum += num;

        current_max = max(num, current_max + num);
        max_sum = max(max_sum, current_max);

        current_min = min(num, current_min + num);
        min_sum = min(min_sum, current_min);
    }
    if(max_sum > 0){
        return max(max_sum, total_sum - min_sum);
    }
    return max_sum;
}
