#include <vector>
using namespace std;
// Leetcode 136. Single Number
int singleNumber(vector<int>& nums){
    int ans = 0;
    for(int num : nums){
        ans ^= num;
    }
    return ans;
}

//leetcode 268: Missing number
int missingNumber(vector<int>& nums){
    int n = nums.size();
    int ans = n;
    for(int i=0; i<n; i++){
        ans ^= i;
        ans ^= nums[i];
    }
    return ans;
}
//leetcode 260: Single number III
vector<int> singleNumberIII(vector<int>& nums){
    int xorAll = 0;
    for(int num : nums){
        xorAll ^= num;
    }
    unsigned int diffBit = (unsigned int)xorAll & (unsigned int)(-xorAll);
    int ans1 = 0;
    int ans2 = 0;
    for(int num : nums){
        if(num & diffBit){
            ans1 ^= num;
        }else{
            ans2 ^= num;
        }
    }
    return {ans1, ans2};
}