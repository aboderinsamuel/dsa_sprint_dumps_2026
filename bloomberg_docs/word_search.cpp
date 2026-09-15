#include <string>
#include <vector>
using namespace std;

class Solution{
private:
    int rows, cols;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //up, down, left, right

    bool dfs(int r, int c, int index, vector<vector<char>>& board, const string& word){
        if(index == word.length()) return true; //base case: if we have matched all characters in the word, return true
        if(r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != word[index]) return false; //if we are out of bounds or the current character does not match, return false
        char temp = board[r][c]; //store the current character
        board[r][c] = '#'; //mark the current cell as visited
        //explore all 4 directions (up, down, left, right)
        for(auto& dir : directions){
            int newRow = r + dir.first;
            int newCol = c + dir.second;
            if(dfs(newRow, newCol, index + 1, board, word)) return true; //if we find a match in any direction, return true
        }
        board[r][c] = temp; //restore the original character
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty() || board[0].empty() || word.empty()) return false;
        rows = board.size();
        cols = board[0].size();
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(dfs(i, j, 0, board, word)) return true;
            }
        }
        return false;
    }
};
