#include <vector>
using namespace std;

class NumMatrix2DMutable {
    vector<vector<int>> tree;
    vector<vector<int>> mat;
    int R, C;

    void add(int r, int c, int delta) {
        for (int i = r; i <= R; i += i & -i) {
            for (int j = c; j <= C; j += j & -j) {
                tree[i][j] += delta;
            }
        }
    }

    int query(int r, int c) {
        int sum = 0;
        for (int i = r; i > 0; i -= i & -i) {
            for (int j = c; j > 0; j -= j & -j) {
                sum += tree[i][j];
            }
        }
        return sum;
    }

public:
    NumMatrix2DMutable(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        mat = matrix;
        R = matrix.size();
        C = matrix[0].size();
        tree.resize(R + 1, vector<int>(C + 1, 0));
        
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                add(r + 1, c + 1, mat[r][c]);
            }
        }
    }
    
    void update(int row, int col, int val) {
        int delta = val - mat[row][col];
        mat[row][col] = val;
        add(row + 1, col + 1, delta);
    }
    
    int sumRegion(int r1, int c1, int r2, int c2) {
        return query(r2 + 1, c2 + 1) 
             - query(r1, c2 + 1) 
             - query(r2 + 1, c1) 
             + query(r1, c1);
    }
};
