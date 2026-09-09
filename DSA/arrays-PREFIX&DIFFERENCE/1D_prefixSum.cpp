#include <vector>
#include <unordered_map>
using namespace std;

//Leetcode 303: Range sum Query- Immutable
class NumArray{
private:
    vector<int> prefix;
public:
    NumArray(vector<int>& nums){
        prefix.resize(nums.size()+1, 0);
        for(int i=0; i<nums.size(); i++){
            prefix[i+1] = prefix[i] + nums[i];
        }
    }
    int sumRange(int left, int right){
        return prefix[right+1] - prefix[left];
    }
};

//leetcode 238 : product of array except self
vector<int> productExceptSelf(vector<int>& nums){
    int n = nums.size();
    vector<int> ans(n, 1);
    int prefix = 1;
    for(int i=0; i<n; i++){
        ans[i] = prefix;
        prefix *= nums[i];
    }
    int suffix = 1;
    for(int i=n-1; i>=0; i--){
        ans[i] *= suffix;
        suffix *= nums[i];
    }
    return ans;
}

//leetcode 724: Find pivot index
int pivotIndex(vector<int>& nums){
    int totalSum = 0;
    for(int num: nums){
        totalSum += num;
    }
    int leftSum = 0;
    for(int i=0; i<nums.size(); i++){
        if(leftSum == totalSum - leftSum - nums[i]){
            return i;
        }
        leftSum += nums[i];
    }
    return -1;
}