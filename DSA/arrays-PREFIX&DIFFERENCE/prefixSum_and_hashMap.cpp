#include <vector>
#include <unordered_map>
using namespace std;
//count subarrays whose sum equals k


int subarraySum(vector<int>& nums, int k){
    unordered_map<long long, int> count;
    count[0] = 1;
    long long cur = 0;
    int result = 0;

    for(int x : nums){
        cur += x;
        if(count.count(cur - k)) result += count[cur - k];
        count[cur]++;
    }
    return result;
}

//leetcode 525: contiguous array
int findMaxLength(vector<int>& nums){
    unordered_map<int, int> count;
    count[0] = -1;
    int cur = 0;
    int result = 0;

    for(int i=0; i<nums.size(); i++){
        cur += (nums[i] == 1) ? 1 : -1;
        if(count.count(cur)) result = max(result, i - count[cur]);
        else count[cur] = i;
    }
    return result;
}

//leetcode 523: continuous subarray sum
bool checkSubarraySum(vector<int>& nums, int k){
    unordered_map<int, int> count;
    count[0] = -1;
    long long current = 0;
    for(int i=0; i<nums.size(); i++){
        current += nums[i];
        int mod = current % k;
        if(count.count(mod)){
            if(i - count[mod] > 1) return true;
        }
        else count[mod] = i;
    }
    return false;
}