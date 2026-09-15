#include <vector>
using namespace std;
class Solution{
private:
    vector<pair<int,int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};
    void dfs(vector<vector<char>>& grid, int r, int c){
        int m = grid.size();
        int n = grid[0].size();
        if(r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == '0') return;
        grid[r][c] = '0'; // mark as visited
        for(auto& dir : directions){
            int newR = r + dir.first;
            int newC = c + dir.second;
            dfs(grid, newR, newC);
        }
    }

public:
    int numIslands(vector<vector<char>>& grid){
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        if(n == 0) return 0;
        int count = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == '1'){
                    count++;
                    dfs(grid, i, j);
                }
            }
        }
        return count;
    }
};