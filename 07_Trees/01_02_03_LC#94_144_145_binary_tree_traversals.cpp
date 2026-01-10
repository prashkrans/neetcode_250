/*
01_LC#94. Binary Tree Inorder Traversal
02_LC#144. Binary Tree Preorder Traversal
03_LC#145. Binary Tree Postorder Traversal

Three ways:
1. Recursive DFS
2. Iterative DFS using a stack (TODO)
3. Special Methods - Morris Traversal (Skipped here)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// Method 1: Recursive DFS (Prefer this over iterative)
// Time complexity: O(n) as each node is visited once
// Auxiliary space: O(n) due to the recursion stack
// where n is the no. of nodes

// 1a. Binary Tree Inorder Traversal
class Solution {
    vector<int> res;
    void inorderTraversalDfs(TreeNode* root) {
        if(!root) return;
        inorderTraversalDfs(root->left);
        res.push_back(root->val);
        inorderTraversalDfs(root->right);
    }
    
public:
    vector<int> inorderTraversal(TreeNode* root) {
        inorderTraversalDfs(root);
        return res;
    }
};

// 1b.  Binary Tree Preorder Traversal
class Solution {
    void preorderTraversalDfs(TreeNode* root, vector<int> &ans) {
        if(root == nullptr) return;
        ans.push_back(root->val);
        preorderTraversalDfs(root->left, ans);
        preorderTraversalDfs(root->right, ans);
    }
    
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        preorderTraversalDfs(root, ans);
        return ans;
    }
};

// 1c. Binary Tree Postorder Traversal
class Solution {
    vector<int> ans;

    void postorderTraversalDfs(TreeNode* root) {
        if(root == NULL) return;
        postorderTraversalDfs(root->left);
        postorderTraversalDfs(root->right);
        ans.push_back(root->val);
    }
    
public:
    vector<int> postorderTraversal(TreeNode* root) {
        postorderTraversalDfs(root);
        return ans;
    }
};


// Method 2: Iterative DFS using a stack (TODO)