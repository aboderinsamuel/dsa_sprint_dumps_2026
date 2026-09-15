#include <vector>
using namespace std;

class NumMatrix2DImmutable {
    vector<vector<int>> pref;

public:
    NumMatrix2DImmutable(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        int R = matrix.size(), C = matrix[0].size();
        pref.resize(R + 1, vector<int>(C + 1, 0));
        
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                pref[r + 1][c + 1] = matrix[r][c] 
                                   + pref[r][c + 1] 
                                   + pref[r + 1][c] 
                                   - pref[r][c];
            }
        }
    }
    
    int sumRegion(int r1, int c1, int r2, int c2) {
        return pref[r2 + 1][c2 + 1] 
             - pref[r1][c2 + 1] 
             - pref[r2 + 1][c1] 
             + pref[r1][c1];
    }
};
