#include <vector>
using namespace std;

class NumArray1DMutable{
    // Binary Indexed Tree (Fenwick Tree) implementation for 1D mutable range sum queries
    vector<int> tree;
    // Original array to keep track of the values for updates
    vector<int> arr;
    int n;

    void add(int i, int delta){
        for(; i<=n; i += i & -i){
            tree[i] += delta;
        }
    }
    int query(int i){
        int sum = 0;
        for(; i>0; i -= i & -i){
            sum += tree[i];
        }
        return sum;
    }
public:
    NumArray1DMutable(vector<int>& nums){
        n = nums.size();
        tree.reserve(n+1);
        arr = nums;
        for(int i=0; i<n; i++){
            add(i+1, arr[i]);
        }
    }

    void update(int index, int val){
        int delta = val - arr[index];
        arr[index] = val;
        add(index+1, delta);
    }
    
    int sumRange(int left, int right){
        return query(right+1) - query(left);
    }
};