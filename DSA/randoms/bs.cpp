//leetcode 4: median of two sorted arrays

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size()){
            return findMedianSortedArrays(nums2, nums1); // always make sure nums1 is the smaller array to optimize the binary search
        }
        int m = nums1.size();
        int n = nums2.size();

        int left = 0; // left boundary of the search space
        int right = m; // right boundary of the search space
        while(left <= right){
            int i = left + (right-left)/2;
            // i + j = (m+n+!)/2
            int j = ((m + n +1) /2) - i; // j is the index in nums2 that complements i to partition the combined arrays into two halves
            
            int nums1Left = (i == 0) ? INT_MIN : nums1[i-1]; // if i is 0, it means there are no elements on the left side of nums1, so we use INT_MIN to represent that
            int nums1Right = (i == m) ? INT_MAX : nums1[i]; // if i is m, it means there are no elements on the right side of nums1, so we use INT_MAX to represent that
            int nums2Left = (j == 0) ? INT_MIN : nums2[j-1]; // if j is 0, it means there are no elements on the left side of nums2, so we use INT_MIN to represent that
            int nums2Right = (j == n) ? INT_MAX : nums2[j]; // if j is n, it means there are no elements on the right side of nums2, so we use INT_MAX to represent that

            if(nums1Left <= nums2Right && nums2Left <= nums1Right){ // if the largest element on the left side of nums1 is less than or equal to the smallest element on the right side of nums2, and the largest element on the left side of nums2 is less than or equal to the smallest element on the right side of nums1, then we have found the correct partition
                if((m+n)% 2 == 0){ // if the total number of elements is even, the median is the average of the two middle elements
                    int leftMax = max(nums1Left, nums2Left); // the largest element on the left side of the partition
                    int rightMin = min(nums1Right, nums2Right); // the smallest element on the right side of the partition
                    return (leftMax + rightMin) / 2.0; // the median is the average of the two middle elements
                }else{
                    return max(nums1Left, nums2Left); // if the total number of elements is odd, the median is the largest element on the left side of the partition
                }
            }else if(nums1Left > nums2Right){ // if the largest element on the left side of nums1 is greater than the smallest element on the right side of nums2, it means we need to move the partition in nums1 to the left
                right = i-1; // move the right boundary of the search space to the left
            }else{
                left = i+ 1; // if the largest element on the left side of nums2 is greater than the smallest element on the right side of nums1, it means we need to move the partition in nums1 to the right
            }
        }
        return 0.0;
    }
};
