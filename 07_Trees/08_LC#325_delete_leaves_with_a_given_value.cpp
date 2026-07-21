/* LC#1325. Delete Leaves With a Given Value
1. Preorder recursion
2. Postorder recursion (Prefer this) [#IMP]

*/

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

 /*
### Approach 1: Repeated Leaf Pruning Using Depth-Bounded Recursion
1. Compute the maximum depth of the binary tree to bound how many pruning iterations may be required.
2. Define a recursive function that removes a node only if it is a leaf and equals target.
3. Recursively process left and right subtrees before deciding whether to delete current node.
4. Apply the pruning function repeatedly for depth iterations to handle newly formed target leaves.
5. This relies on tree height, recursion, leaf detection, and iterative convergence to stable structure.
6. Worst case occurs in skewed trees, causing repeated full traversals until no target leaves remain.
*/

// 1. Recursion (Preorder traversal + maxDepth): Repeated Leaf Pruning Using Depth-Bounded Recursion (My original solution | 15 min)
// Time Complexity: O(n*h)
// Space Complexity: O(h) ~ O(n)
// where n: no. of nodes and h: height of the binary tree = n in the worst case

class Solution {                                                                           
    int maxDepth(TreeNode* root) {                                                          // Computes depth of the binary tree
        if(!root) return 0;                                                                 // Base case: null node has zero depth
        return 1 + maxDepth(root->left) + maxDepth(root->right);                            // Recursively sum depths of subtrees
    }
    TreeNode* rec(TreeNode* root, int target) {                                             // Recursively removes target leaf nodes
        if(!root) return nullptr;                                                           // Base case: null node remains null
        if(!root->left && !root->right && root->val == target) return nullptr;              // Remove leaf node matching target
        root->left = rec(root->left, target);                                               // Process left subtree recursively
        root->right = rec(root->right, target);                                             // Process right subtree recursively
        return root;                                                                        // Return updated root pointer
    }
public:                                                                                     // Public access specifier
    TreeNode* removeLeafNodes(TreeNode* root, int target) {                                 // Removes all target valued leaf nodes
        // variable name maxDepth doesn't work also, height = (maxDepth(root) - 1) doesn't work here.
        int depth = maxDepth(root);                                                         // Compute maximum possible tree depth
        while(depth--) root = rec(root, target);                                            // Repeatedly prune target leaves
        return root;                                                                        // Return final pruned tree
    }
};

/* ### Approach 2: Postorder Recursive Leaf Removal [#IMP]
1. Traverse the binary tree using postorder traversal so children are processed before their parent nodes.
2. Recursively call the function on left and right subtrees to remove target valued leaf nodes first.
3. After recursion, check if the current node has become a leaf and matches the target value.
4. If both children are null and value equals target, return null to delete the node.
5. This uses recursion, tree traversal, and conditional pruning to ensure single pass removal.
6. Postorder traversal guarantees newly formed leaves are correctly handled in the same recursion.
*/

// 2. Recursion (Postorder Traversal - Prefer this method) [#IMP]
// Time Complexity: O(n) | 0ms beats, 100%
// Space Complexity: O(h) ~ O(n)
// where n: no. of nodes and h: height of the binary tree = n in the worst case

class Solution {                                                                            
public:                                                                                     
    TreeNode* removeLeafNodes(TreeNode* root, int target) {                                 // Removes target valued leaf nodes recursively
        if(root == nullptr) return nullptr;                                                 // Base case: empty node remains null
        root->left = removeLeafNodes(root->left, target);                                   // Recursively process left subtree
        root->right = removeLeafNodes(root->right, target);                                 // Recursively process right subtree
        if(root->left == nullptr && root->right == nullptr && root->val == target) {        // Check if current node is target leaf
            return nullptr;                                                                 // Remove current node if condition satisfied
        }                                                                                   // Don't use delete root; as it fails when the tree is like [1, 1, 1]
        return root;                                                                        // Return updated subtree root
    }
};
