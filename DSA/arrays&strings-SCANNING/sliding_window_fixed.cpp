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
            // If the character at the left pointer is not a vowel, we keep moving the left pointer to the right until we find a vowel or the pointers cross
            while(left < right && !vowels.count(s[left])) left++;
            // If the character at the right pointer is not a vowel, we keep moving the right pointer to the left until we find a vowel or the pointers cross
            while(left < right && !vowels.count(s[right])) right--;
            swap(s[left], s[right]); // Swap the vowels
            left++;
            right--;
        }
        return s;
    }
};
