//leetcode 63: Unique Paths II
#include <vector>
using namespace std;

class Solution{
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid){
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        
        vector<vector<int>> dp(m, vector<int>(n, 0));
        if(obstacleGrid[0][0] == 1) return 0; // if the starting cell has an obstacle, return 0
        dp[0][0] = 1; // starting point

        for(int r=0; r<m; r++){
            for(int c=0; c<n; c++){
                if(r == 0 && c == 0) continue; // skip the starting cell
                if(obstacleGrid[r][c] == 1){
                    dp[r][c] = 0; // if there's an obstacle, no paths to this cell
                    continue;
                }
                if(r > 0) dp[r][c] += dp[r-1][c]; // paths from the cell above
                if(c > 0) dp[r][c] += dp[r][c-1]; // paths from the cell to the left
            }
        }
        return dp[m-1][n-1]; // return the number of unique paths to the bottom-right corner
    }
};

//test inside a main function
int main() {
    Solution solution;
    vector<vector<int>> obstacleGrid = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    int result = solution.uniquePathsWithObstacles(obstacleGrid);
    // Expected output: 2
    return 0;
};
