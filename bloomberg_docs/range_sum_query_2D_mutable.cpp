#include <vector>
using namespace std;

class NumArray1DMutable{
    vector<vector<int>> tree; // segment tree
    vector<vector<int>> data; // store the original data for updates
    int R, C; // number of rows and columns

    void add(int r, int c, int delta) {
        for (int i = r; i <= R; i += i & -i) {
            for (int j = c; j <= C; j += j & -j) {
                tree[i][j] += delta;
            }
        }
    }
    
    int query(int r, int c){
        int sum = 0;
        for(int i=r; i<=R; i-= i & -i){
            for(int j=c; j<=C; j -= j & -j){
                sum += tree[i][j];
            }
        }
        return sum;
    }
public:
    NumArray1DMutable(vector<vector<int>>& matrix){
        if(matrix.empty() || matrix[0].empty()) return;
        R = matrix.size();
        C = matrix[0].size();
        tree.resize(R + 1, vector<int>(C + 1, 0));
        data = matrix;

        for(int r=0; r<R; r++){
            for(int c=0; c<C; c++){
                add(r + 1, c + 1, data[r][c]);
            }
        }
    }
    void update(int row, int col, int val){
        int delta = val - data[row][col];
        data[row][col] = val;
        add(row + 1, col + 1, delta);
    }
    int sumRegion(int row1, int col1, int row2, int col2){
        return query(row2 + 1, col2 + 1) - query(row1, col2 + 1) - query(row2 + 1, col1) + query(row1, col1);
    }
};