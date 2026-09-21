// leetcode 3. Longest Substring Without Repeating Characters
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;
unordered_set<char> window;
int lengthOfLongestSubstring(string s) {
    unordered_set<char> window;
    int left = 0;
    int answer = 0;
    for(int right=0; right < s.size(); right++){
        while(window.count(s[right])){
            window.erase(s[left]);
            left++;
        }
        window.insert(s[right]);
        answer = max(answer, right - left + 1);
    }
    return answer;
};
//leetcode 424: Longest Repeating Character Replacement
int characterReplacement(string s, int k) {
    unordered_map<char, int> window;
    int left = 0;
    int max_count = 0;
    int answer = 0;
    for(int right=0; right < s.size(); right++){
        window[s[right]]++;
        max_count = max(max_count, window[s[right]]);
        while(right - left + 1 - max_count > k){
            window[s[left]]--;
            left++;
        }
        answer = max(answer, right - left + 1);
    }
    return answer;
};
//leetcode 76: Minimum Window Substring
string minWindow(string s, string t) {
    unordered_map<char, int> window;
    unordered_map<char, int> need;
    for(char c: t) need[c]++;
    int left = 0;
    int right = 0;
    int valid = 0;
    int start = 0;
    int len = INT_MAX;
    while(right < s.size()){
        char c = s[right];
        right++;
        if(need.count(c)){
            window[c]++;
            if(window[c] == need[c]) valid++; // When the count of a character in the window equals the count needed, increment valid
        }
        while(valid == need.size()){
            if(right - left < len){
                start = left;
                len = right - left;
            }
            char d = s[left];
            left++;
            if(need.count(d)){
                if(window[d] == need[d]) valid--;
                window[d]--;
            }
        }
    }
    return len == INT_MAX ? "" : s.substr(start, len);
};
//leetcode 438: Find All Anagrams in a String
vector<int> findAnagrams(string s, string p) {
    unordered_map<char, int> window;
    unordered_map<char, int> need;
    for(char c: p) need[c]++;
    int left = 0;
    int right = 0;
    int valid = 0;
    vector<int> result;
    while(right < s.size()){
        char c = s[right];
        right++;
        if(need.count(c)){
            window[c]++;
            if(window[c] == need[c]) valid++;
        }
        while(right - left >= p.size()){
            if(valid == need.size()) result.push_back(left);
            char d = s[left];
            left++;
            if(need.count(d)){
                if(window[d] == need[d]) valid--;
                window[d]--;
            }
        }
    }
    return result;
};
//time : O(n) where n is the length of the input string s. Each character is processed at most twice (once when added to the window and once when removed).
//space : O(m) where m is the number of unique characters in string p. The space is used for the need and window hash maps.

//leetcode 567: Permutation in String
bool checkInclusion(string s1, string s2) {
    unordered_map<char, int> window;
    unordered_map<char, int> need;
    for(char c: s1) need[c]++;
    int left = 0;
    int right = 0;
    int valid = 0;
    while(right < s2.size()){
        char c = s2[right];
        right++;
        if(need.count(c)){
            window[c]++;
            if(window[c] == need[c]) valid++;
        }
        while(right - left >= s1.size()){
            if(valid == need.size()) return true;
            char d = s2[left];
            left++;
            if(need.count(d)){
                if(window[d] == need[d]) valid--;
                window[d]--;
            }
        }
    }
    return false;
};
// time : O(n) where n is the length of the input string s2. Each character is processed at most twice (once when added to the window and once when removed).
// space : O(m) where m is the number of unique characters in string s1.

// leetcode 30: Substring with Concatenation of All Words
vector<int> findSubstring(string s, vector<string>& words) {
    unordered_map<string, int> need;
    for(const string& word: words) need[word]++;
    int wordLen = words[0].size();
    int totalLen = wordLen * words.size();
    vector<int> result;
    for(int i = 0; i < wordLen; i++){
        int left = i;
        int right = i;
        int valid = 0;
        unordered_map<string, int> window;
        while(right + wordLen <= s.size()){
            string str = s.substr(right, wordLen);
            right += wordLen;
            if(need.count(str)){
                window[str]++;
                if(window[str] == need[str]) valid++;
            }
            while(right - left >= totalLen){
                if(valid == need.size()) result.push_back(left);
                string d = s.substr(left, wordLen);
                left += wordLen;
                if(need.count(d)){
                    if(window[d] == need[d]) valid--;
                    window[d]--;
                }
            }
        }
    }
    return result;
};

// time : O(n * m) where n is the length of the input string s and m is the length of each word in words. The outer loop runs for wordLen iterations, and the inner while loop processes each character in s once.
// space : O(k) where k is the number of unique words in the input vector words

//now i want to implement sliding window fixed techniques in popularly and commonly asked and high frequency problems:

//leetcode 567: permutation in String
bool checkInclusion(string s1, string s2) {
    unordered_map<char, int> window;
    unordered_map<char, int> need;
    for(char c: s1) need[c]++;
    int left = 0;
    int right = 0;
    int valid = 0;
    while(right < s2.size()){
        char c = s2[right];
        right++;
        if(need.count(c)){
            window[c]++;
            if(window[c] == need[c]) valid++;
        }
        while(right - left >= s1.size()){
            if(valid == need.size()) return true;
            char d = s2[left];
            left++;
            if(need.count(d)){
                if(window[d] == need[d]) valid--;
                window[d]--;
            }
        }
    }
    return false;
};
// the obvious difference bewteen the code of fixed sliding window and variable sliding window is that in fixed sliding window we have a fixed size of the window which is equal to the length of the string s1 and in variable sliding window we have a variable size of the window which can be increased or decreased based on the conditions.
// the difference in code:
// 1. FIXED SLIDING WINDOW TEMPLATE (e.g., Target size is K)
/* if (right - left == K) { 
    // 1. Check if the exact fixed window matches criteria
    if (valid == need.size()) return true; 
    
    // 2. Safely slide the left pointer forward exactly 1 step
    char d = s[left++]; 
    // (Update maps / valid variables...)
}

// 2. VARIABLE SLIDING WINDOW TEMPLATE
while (invalid_condition_met) { 
    // Keep shrinking from the left until your window is healthy again
    char d = s[left++];
    // (Update maps / valid variables...)
}
*/
// leetcode 643: Maximum Sum of Subarray of Size K
int findMaxAverage(vector<int>& nums, int k) {
    int left = 0;
    int right = 0;
    int sum = 0;
    int max_sum = INT_MIN;
    while(right < nums.size()){
        sum += nums[right];
        right++;
        if(right - left == k){
            max_sum = max(max_sum, sum);
            sum -= nums[left];
            left++;
        }
    }
    return max_sum / k;
};
//see why its fixed var:
// 1. The window size is fixed at k, so we only check the condition when the window size is exactly k.
// 2. We slide the left pointer forward exactly 1 step when the window size is
//    k, and we update the sum accordingly.

//leetcode 438: Find All Anagrams in a String
vector<int> findAnagrams(string s, string p) {
    unordered_map<char, int> window;
    unordered_map<char, int> need;
    for(char c: p) need[c]++;
    int left = 0;
    int right = 0;
    int valid = 0;
    vector<int> result;
    while(right < s.size()){
        char c = s[right];
        right++;
        if(need.count(c)){
            window[c]++;
            if(window[c] == need[c]) valid++;
        }
        while(right - left >= p.size()){
            if(valid == need.size()) result.push_back(left);
            char d = s[left];
            left++;
            if(need.count(d)){
                if(window[d] == need[d]) valid--;
                window[d]--;
            }
        }
    }
    return result;
};
//why its fixed: The window size is fixed at the length of string p, so we only check the condition when the window size is exactly the length of p.
// time : O(n) where n is the length of the input string s. Each character is processed at most twice (once when added to the window and once when removed).
// space : O(m) where m is the number of unique characters in string p. The space is used for the need and window hash maps.


