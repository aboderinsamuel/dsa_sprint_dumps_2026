//leetcode 75: Sort Colors
#include <vector>
using namespace std;

void sortColors(vector<int>& nums){
    int low = 0, mid = 0, high = nums.size()-1;
    while(mid <= high){
        if(nums[mid] == 0){
            swap(nums[mid], nums[low]);
            low++;
            mid++;
        }else if(nums[mid] == 1){
            mid++; // if the current element is 1, we just move the mid pointer forward
        }else{
            swap(nums[mid], nums[high]);
            high--;
        }
    }
};

vector<int> sortColors2(vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[mid], nums[low]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++; // if the current element is 1, we just move the mid pointer forward
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
    return nums;
}

//leetcode 912: Sort an Array
void sortArray(vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;
    while (mid <= high) {
        if (nums[mid] < 0) {
            swap(nums[mid], nums[low]);
            low++;
            mid++;
        } else if (nums[mid] > 0) {
            swap(nums[mid], nums[high]);
            high--;
        } else {
            mid++;
        }
    }
};

// The submission implements a Dutch National Flag algorithm which only handles
// three categories (negative, zero, positive) and is not a general-purpose 
// O(n log n) sorting algorithm.

// using mergesort

vector<int> merge(vector<int>& left, vector<int>& right) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }
    return result;
}
vector<int> mergeSort(vector<int>& nums) {
    if (nums.size() <= 1) return nums;
    int mid = nums.size() / 2;
    vector<int> left(nums.begin(), nums.begin() + mid);
    vector<int> right(nums.begin() + mid, nums.end());
    left = mergeSort(left);
    right = mergeSort(right);
    return merge(left, right);
};

vector<int> sortArray2(vector<int>& nums) {
    return mergeSort(nums);
};
