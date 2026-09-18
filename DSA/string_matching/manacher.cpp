//leetcode 5: Longest Palindromic Substring
#include <string>
#include <vector>
using namespace std;

class Solution{
public:
    string longestPalindrome(string s){
        if(s.empty()) return "";
        //track the starting index and maximum length found so far
        int start = 0, max_len = 0;

        //helper lambda function to expand around the center and find the longest palindrome
        auto expandAroundCenter = [&](int left, int right){
            while(left >= 0 && right < s.length() && s[left] == s[right]){
                left--;
                right++;
            }
            //return the length of the palindrome found
            return right - left - 1;
        };
        for(int i=0; i<s.length(); i++){
            //case 1: odd length palindrome
            int len1 = expandAroundCenter(i, i);
            //case 2: even length palindrome
            int len2 = expandAroundCenter(i, i+1);

            int current_max_len = max(len1, len2);

            //if we found a strictly longer palindrome, update our pointers
            if(current_max_len > max_len){
                max_len = current_max_len;
                start = i - (current_max_len - 1) / 2; //calculate the starting index of the palindrome
            }
        }
        return s.substr(start, max_len);
    }
};

//time : O(n^2) where n is the length of the input string s. This is because for each character in the string, we potentially expand around it to check for palindromes, which can take linear time in the worst case.
//space : O(1) as we are using only a constant amount of extra space for variables and not using any additional data structures that scale with the input size.

//in the same way, leetcode 647: Palindromic Substrings can be solved using the same approach, but instead of keeping track of the longest palindrome, we can keep a count of all palindromic substrings found during the expansion process.

int countSubstrings(string s) {
    int count = 0;
    auto expandAroundCenter = [&](int left, int right){
        while(left >= 0 && right < s.length() && s[left] == s[right]){
            count++;
            left--;
            right++;
        }
    };
    for(int i=0; i<s.length(); i++){
        //case 1: odd length palindrome
        expandAroundCenter(i, i);
        //case 2: even length palindrome
        expandAroundCenter(i, i+1);
    }
    return count;
};
//time : O(n^2) where n is the length of the input string s. This is because for each character in the string, we potentially expand around it to check for palindromes, which can take linear time in the worst case.
//space : O(1) as we are using only a constant amount of extra space for
