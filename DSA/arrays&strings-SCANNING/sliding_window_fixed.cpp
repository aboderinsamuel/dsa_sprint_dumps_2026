#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    string reverseVowels(string s){
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        int left = 0;
        int right = s.size() - 1;
        while(left < right){
            while(left < right && !vowels.count(s[left])) left++; // Move left pointer to the next vowel
            while(left < right && !vowels.count(s[right])) right--; // Move right pointer to the previous vowel
            swap(s[left], s[right]); // Swap the vowels
            left++;
            right--;
        }
        return s;
    }
};
