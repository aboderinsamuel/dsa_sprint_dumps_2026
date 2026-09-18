//leetcode 102. Binary Tree Level Order Traversal
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

vector<vector<int>> levelOrder(TreeNode* root){
    vector<vector<int>> result;
    if(!root) return result; // if the root is null, we return an empty vector
    queue<TreeNode*> q; // we create a queue to store the nodes of the tree
    q.push(root); // we push the root node into the queue

    while(!q.empty()){ // we loop until the queue is empty
        int size = q.size(); // we get the size of the queue
        vector<int> level; // we create a vector to store the values of the nodes at the current level
        for(int i = 0; i < size; i++){ // we loop through the nodes at the current level
            TreeNode* node = q.front(); // we get the front node of the queue
            q.pop(); // we pop the front node from the queue
            level.push_back(node->val); // we add the value of the node to the level vector
            if(node->left) q.push(node->left); // if the left child of the node is not null, we push it into the queue
            if(node->right) q.push(node->right); // if the right child of the node is not null, we push it into the queue
        }
        result.push_back(level); // we add the level vector to the result vector
    }
    return result;
};

//leetcode 199. Binary Tree Right Side View
//for this problem we can use the same approach as the level order traversal, 
//but we will only add the last node of each level to the result vector
vector<int> rightSideView(TreeNode* root){
    vector<int> result;
    if(!root) return result; // if the root is null, we return an empty vector
    queue<TreeNode*> q; // we create a queue to store the nodes of the tree
    q.push(root); // we push the root node into the queue

    while(!q.empty()){ // we loop until the queue is empty
        int size = q.size(); // we get the size of the queue
        for(int i = 0; i < size; i++){ // we loop through the nodes at the current level
            TreeNode* node = q.front(); // we get the front node of the queue
            q.pop(); // we pop the front node from the queue
            if(i == size - 1) result.push_back(node->val); // if it is the last node of the level, we add its value to the result vector
            if(node->left) q.push(node->left); // if the left child of the node is not null, we push it into the queue
            if(node->right) q.push(node->right); // if the right child of the node is not null, we push it into the queue
        }
    }
    return result;
};

//leetcode 111: Minimum Depth of Binary Tree
int minDepth(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int depth = 1;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            if (!node->left && !node->right) return depth;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        depth++;
    }
    return depth;
};

