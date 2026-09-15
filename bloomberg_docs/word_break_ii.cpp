#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

class Solution{
private:
    unordered_set<string> dict; 
    //this unordered_set is used to store the dictionary words for O(1) lookup
    unordered_map<int, vector<string>> memo;
    //this unordered_map is used to store the results of subproblems for
    // memoization

    vector<string> dfs(const string& s, int start){
        if(start == s.size()) return {""}; //base case: if we reach the end of the string, return a vector with an empty string
        if(memo.count(start)) return memo[start]; //if we have already computed the result for this start index, return it
        vector<string> result;
        for(int i=start; i<s.size(); i++){
            string word = s.substr(start, i-start+1);
            if(!dict.count(word)) continue; //if the current substring is not in the dictionary, skip it
            vector<string> subList = dfs(s, i+1); //recursively call dfs for the next index
            for(string sub : subList){
                if(sub.empty()) result.push_back(word);
                else result.push_back(word + " " + sub); //combine the current word with the results of the subproblem
            }
        }
        return memo[start] = result;
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict){
        for(string word : wordDict){
            dict.insert(word); //insert each word from the dictionary into the unordered_set
        }
        return dfs(s, 0); //start the dfs from index 0
    }


};