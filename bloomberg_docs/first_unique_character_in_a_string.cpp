#include <string>
#include <vector>
using namespace std;

class FirstUniqueChar{
public:
    int firstUniqChar(string s){
        //frequency table for lowercase english letters ('a to 'z') 
        vector<int> freq(26, 0);
        for(char c : s){
            freq[c - 'a']++;
        }
        for(int i=0; i<s.size(); i++){
            if(freq[s[i] - 'a'] == 1){
                return i;
            }
        }
        return -1;
    }
};
