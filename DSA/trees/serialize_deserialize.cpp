#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Codec {
private:
// Helper function to deserialize the tree from the string representation
    TreeNode* deserializeHelper(const string& data, int& index){
        if(index >= data.size()) return nullptr; // Check if the index is out of bounds
        int delimiterPos = data.find(',', index); // Find the position of the next delimiter (comma) in the string
        string token = data.substr(index, delimiterPos - index); // Extract the token (value) from the string based on the current index and delimiter position
        index = delimiterPos + 1; // Update the index to point to the next token in the string

        if(token == "#") return nullptr;
        TreeNode* node = new TreeNode(stoi(token));

        node->left = deserializeHelper(data, index);
        node->right = deserializeHelper(data, index);
        return node;

    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "#";
        return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int index = 0;
        return deserializeHelper(data, index);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

//leetcode 105: Construct Binary Tree from Preorder and Inorder Traversal
class Solution {
private:
    unordered_map<int, int> idx; // Stores value -> index mapping of inorder array
    int preIdx;                  // Tracks current root in preorder array

    TreeNode* buildHelper(const vector<int>& preorder, int lo, int hi) {
        if (lo > hi) return nullptr;

        // Pick current root value from preorder and advance the pointer
        int val = preorder[preIdx++];
        TreeNode* root = new TreeNode(val);

        // Find the boundary split point using our hash map lookup
        int mid = idx[val];

        // Recursively build the left and right subtrees
        root->left = buildHelper(preorder, lo, mid - 1);
        root->right = buildHelper(preorder, mid + 1, hi);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // 1. Reset state (crucial for LeetCode's multi-testcase runner)
        idx.clear();
        preIdx = 0;

        // 2. Map all inorder values to their indices for O(1) lookups
        for (int i = 0; i < inorder.size(); i++) {
            idx[inorder[i]] = i;
        }

        // 3. Kick off the recursive tree construction
        return buildHelper(preorder, 0, inorder.size() - 1);
    }
};

