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

TreeNode* buildTreeHelper(vector<int>& preorder, vector<int>& inorder){
    if(preorder.empty() || inorder.empty()) return nullptr;
    int rootVal = preorder[0];
    TreeNode* root = new TreeNode(rootVal);
    int rootIndex = 0;
    for(int i = 0; i < inorder.size(); i++){
        if(inorder[i] == rootVal){
            rootIndex = i;
            break;
        }
    }
    vector<int> leftPreorder(preorder.begin() + 1, preorder.begin() + 1 + rootIndex);
    vector<int> rightPreorder(preorder.begin() + 1 + rootIndex, preorder.end());
    vector<int> leftInorder(inorder.begin(), inorder.begin() + rootIndex);
    vector<int> rightInorder(inorder.begin() + 1 + rootIndex, inorder.end());
    root->left = buildTreeHelper(leftPreorder, leftInorder);
    root->right = buildTreeHelper(rightPreorder, rightInorder);
    return root;
}
