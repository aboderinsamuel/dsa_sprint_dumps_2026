//leetcode 125 : valide palindrome
#include <string>
#include <vector>
using namespace std;

bool isPalindrome(string s){
    int start = 0;
    int end = s.length() - 1;
    while(start < end){
        while(start < end && !isalnum(s[start])) start++;
        while(start < end && !isalnum(s[end])) end--;
        if(tolower(s[start]) != tolower(s[end])) return false;
        start++;
        end--;
    }return true;

};

//leetcode 11: container with most water

int maxArea(vector<int>& height){
    int left = 0;
    int right = height.size() - 1;
    int max_area = 0;

    while(left < right){
        int distance = right - left;
        int area = distance * min(height[left], height[right]);
        max_area = max(max_area, area);
        if(height[left] < height[right]) left++; // 
        else right--;
    }
    return max_area;
}

//leetcode 42: Trapping Rain Water
int trap(vector<int>& height){
    int left = 0;
    int right = height.size() - 1;
    int left_max = 0;
    int right_max = 0;
    int water = 0;
    while(left < right){
        if(height[left] <= height[right]){ // 
            if(height[left] >= left_max){ // if current height is greater than or equal to the maximum height seen so far from the left
                left_max = height[left]; // update the maximum height seen so far from the left
            }else{
                water -= height[left]; // subtract the current height from the total water
            }
            left++;
        }
        else if(height[left] > height[right]){ // if current height is greater than the height at the right pointer
            if(height[right] >= right_max){ // if current height is greater than or equal to the maximum height seen so far from the right
                right_max = height[right]; // update the maximum height seen so far from the right
            }else{
                water -= height[right]; // subtract the current height from the total water
            }
            right--;
            
        }
    }
    return water;
}