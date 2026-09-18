#include <vector>
#include <queue>

using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr){}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right){}
};

//leetcode 104: Maximum Depth of Binary Tree
int maxDepth(TreeNode* root) {
    if (!root) return 0; // if the root is null, we return 0
    int leftDepth = maxDepth(root->left); // we get the maximum depth of the left subtree
    int rightDepth = maxDepth(root->right); // we get the maximum depth of the right subtree
    return max(leftDepth, rightDepth) + 1; // we return the maximum depth of the left and right subtrees plus 1 for the current node
};

//leetcode 543: Diameter of Binary Tree
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0; // we initialize the diameter to 0
    int dfs(TreeNode* node) {
        if (!node) return 0; // if the node is null, we return 0
        int leftDepth = dfs(node->left); // we get the maximum depth of the left subtree
        int rightDepth = dfs(node->right); // we get the maximum depth of the right subtree
        diameter = max(diameter, leftDepth + rightDepth); // we update the diameter if the sum of the left and right depths is greater than the current diameter
        return max(leftDepth, rightDepth) + 1; // we return the maximum depth of the left and right subtrees plus 1 for the current node
    }
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return diameter;
    }
};
//leetcode 110: Balanced Binary Tree
bool isBalanced(TreeNode* root) {
    if (!root) return true; // if the root is null, we return true
    int leftDepth = maxDepth(root->left); // we get the maximum depth of the left subtree
    int rightDepth = maxDepth(root->right); // we get the maximum depth of the right subtree
    if (abs(leftDepth - rightDepth) > 1) return false; // if the difference between the left and right depths is greater than 1, we return false
    return isBalanced(root->left) && isBalanced(root->right); // we check if the left and right subtrees are balanced
};

//leetcode 124: binary tree maximum path sum
int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN; // we initialize the maximum sum to the minimum integer value
    int dfs(TreeNode* node){
        if (!node) return 0; // if the node is null, we return 0
        int leftSum = max(dfs(node->left), 0); // we get the maximum sum of the left subtree, or 0 if it's negative
        int rightSum = max(dfs(node->right), 0); // we get the maximum sum of the right subtree, or 0 if it's negative
        int currentSum = node->val + leftSum + rightSum; // we calculate the sum of the current node and its left and right subtrees
        maxSum = max(maxSum, currentSum); // we update the maximum sum if the current sum is greater
        return node->val + max(leftSum, rightSum); // we return the maximum sum of the current node and its left or right subtree
    }
    dfs(root);
    return maxSum;
};
