//leetcode 230 : Kth Smallest Element in a BST
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> stk;
    TreeNode* curr = root;
    int count = 0;
    while (curr || !stk.empty()) {
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        curr = stk.top();
        stk.pop();
        count++;
        if (count == k) return curr->val;
        curr = curr->right;
    }
    return -1; // This line should never be reached
}
// or 

void inorder(TreeNode* root, vector<int>& array){
    if(!root) return;
    inorder(root->left, array); // Inorder traversal: left, root, right
    array.push_back(root->val);
    inorder(root->right, array);
};
int kthSmallest(TreeNode* root, int k) {
    vector<int> array;
    inorder(root, array);
    return array[k-1];
};

//leetcode 98 : Validate Binary Search Tree
bool dfs(TreeNode* root, long min, long max){
    if(!root) return true;
    if(root->val <= min || root->val >= max) return false;
    return dfs(root->left, min, root->val) && dfs(root->right, root->val, max);
}
bool isValidBST(TreeNode* root){
    return dfs(root, LONG_MIN, LONG_MAX);
}
//leetcode 530 : Minimum Absolute Difference in BST
int getMinDiff(TreeNode* root) {
    vector<int> array;
    inorder(root, array);
    int minDiff = INT_MAX;
    for(int i = 1; i < array.size(); i++){
        minDiff = min(minDiff, array[i] - array[i-1]);
    }
    return minDiff;
};