#include <string>
#include <unordered_set>
using namespace std;

class Solution{
public:
    int lengthofLongestSubstring(string s){
        unordered_set<char> window;
        int left = 0;
        int answer = 0;
        for(int right=0; right<s.size(); right++){
            while(window.count(s[right])){
                window.erase(s[left]);
                left++;
            }
            window.insert(s[right]);
            answer = max(answer, right-left+1);
        }
        return answer;
    }
};