#include <climits>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){
    if(root == NULL || root == p || root == q){
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if(left != NULL && right != NULL){
        return root;
    }
    return left != NULL ? left : right;
};

//leetcode 235: Lowest Common Ancestor of a Binary Search Tree
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q){
    if(root == NULL){
        return NULL;
    }
    if(p->val < root->val && q->val < root->val){
        return lowestCommonAncestorBST(root->left, p, q);
    }
    else if(p->val > root->val && q->val > root->val){
        return lowestCommonAncestorBST(root->right, p, q);
    }
    else{
        return root;
    }
};

