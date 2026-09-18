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