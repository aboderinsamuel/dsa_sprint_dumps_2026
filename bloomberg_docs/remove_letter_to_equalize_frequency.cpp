#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution{
private:
    bool hasEqualFrequency(const vector<int>& count){
        int common_freq = -1;
        for(int freq : count){
            if(freq == 0) continue; // skip characters that don't appear
            if(common_freq == -1){
                common_freq = freq; // first non-zero frequency
            }
            else if(freq != common_freq){
                return false; // found a different frequency
            }
        }
        return true;
    }
public:
    bool equalFrequency(string word){
        vector<int> count(26, 0);
        for(char c : word){
            count[c - 'a']++;
        }
        for(int i=0; i<26; i++){
            if(count[i] > 0){
                count[i]--; //remove the occurence of this character
                if(hasEqualFrequency(count)){
                    return true;
                }
                count[i]++; // restore the character
            }
        }
        return false;
    }
};