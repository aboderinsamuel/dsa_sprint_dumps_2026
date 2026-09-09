#include <cstdint>
#include <vector>
using namespace std;
//leetcode 191: Number of 1 Bits
int hammingWeight(uint32_t n){
    int count = 0;
    while(n){
        count += n & 1;
        n >>= 1;
    }
    return count;
}
//leetcode 338: Counting Bits
vector<int> countBits(int n) {
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; ++i) {
        ans[i] = ans[i >> 1] + (i & 1);
    }
    return ans;
}
//leetcode 231: Power of Two
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}
