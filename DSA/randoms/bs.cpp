//leetcode 4: median of two sorted arrays

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size()){
            return findMedianSortedArrays(nums2, nums1);
        }
        int m = nums1.size();
        int n = nums2.size();

        int left = 0;
        int right = m;
        while(left <= right){
            int i = left + (right-left)/2;
            // i + j = (m+n+!)/2
            int j = ((m + n +1) /2) - i;
            
            int nums1Left = (i == 0) ? INT_MIN : nums1[i-1];
            int nums1Right = (i == m) ? INT_MAX : nums1[i];
            int nums2Left = (j == 0) ? INT_MIN : nums2[j-1];
            int nums2Right = (j == n) ? INT_MAX : nums2[j];

            if(nums1Left <= nums2Right && nums2Left <= nums1Right){
                if((m+n)% 2 == 0){
                    int leftMax = max(nums1Left, nums2Left);
                    int rightMin = min(nums1Right, nums2Right);
                    return (leftMax + rightMin) / 2.0;
                }else{
                    return max(nums1Left, nums2Left);
                }
            }else if(nums1Left > nums2Right){
                right = i-1;
            }else{
                left = i+ 1;
            }
        }
        return 0.0;
    }
};
