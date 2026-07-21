/* LC#337. House Robber III
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
### Approach 1: Recursive Tree Dynamic Programming Without Memoization
- This is a tree version of the classic house robber problem.
- At each node, we have two choices: rob it or skip it.
- If we rob the current node, we cannot rob its immediate children, so we must skip to the grandchildren.
- If we skip the current node, we can consider robbing its children.
- We take the maximum of these two options.

1. Treat the binary tree as houses where robbing a node forbids robbing its immediate children due to adjacency constraint.
2. For every node, compute two choices recursively, robbing the current node or skipping it entirely based on profits.
3. If the current node is robbed, recursively add values from its grandchildren since children cannot be robbed.
4. If the current node is not robbed, recursively add values from its left and right children directly.
5. Use recursion to evaluate both choices for each node, applying the max function to select optimal profit.
6. This approach relies on tree recursion, overlapping subproblems, and exhaustive exploration without caching results.
*/


// 1. Recursion without memoization
// Time Complexity: O(2^n) since each node has two options | Gets TLE, passes 122/124 test cases
// Space Complexity: O(h) ~ O(n) due to the recursion stack
// where n = number of nodes and h = height of the binary tree = n - 1 (worst case i.e. linear tree)

class Solution {                                                                            
public:                                                                                     
    int rob(TreeNode* root) {                                                                   // Function to compute maximum robbery amount
        if(!root) return 0;                                                                     // Base case: empty node yields zero profit
        
        int nodeRobbedLeft = 0, nodeRobbedRight = 0;                                            // Stores profit from grandchildren when current is robbed
        if(root->left) nodeRobbedLeft = rob(root->left->left) + rob(root->left->right);         // Recurse on left child's children
        if(root->right) nodeRobbedRight = rob(root->right->left) + rob(root->right->right);     // Recurse on right child's children
        int nodeRobbed = root->val + nodeRobbedLeft + nodeRobbedRight;                          // Total profit if current node is robbed

        int nodeNotRobbedLeft = rob(root->left), nodeNotRobbedRight = rob(root->right);         // Profit when current is not robbed
        int nodeNotRobbed =  nodeNotRobbedLeft + nodeNotRobbedRight;                            // Sum of profits from immediate children

        return max(nodeRobbed, nodeNotRobbed);                                                  // Choose maximum of robbing or not robbing current node
    }
};

// 2. Recursion with memoization
// Time Complexity: O(n) | 7ms, beats 34.37%
// Space Complexity: O(h) ~ O(n) due to the recursion stack
// where n = number of nodes and h = height of the binary tree

class Solution {
    unordered_map<TreeNode* , int> dp;
public:
    int rob(TreeNode* root) {
        if(!root) return 0;
        if(dp.count(root)) return dp[root];

        int nodeRobbedLeft = 0, nodeRobbedRight = 0;
        if(root->left) nodeRobbedLeft = rob(root->left->left) + rob(root->left->right);
        if(root->right) nodeRobbedRight = rob(root->right->left) + rob(root->right->right);      
        int nodeRobbed = root->val + nodeRobbedLeft + nodeRobbedRight;

        int nodeNotRobbedLeft = rob(root->left);
        int nodeNotRobbedRight = rob(root->right);
        int nodeNotRobbed =  nodeNotRobbedLeft + nodeNotRobbedRight;

        return dp[root] = max(nodeRobbed, nodeNotRobbed);
    }
};

// Ignore the codes below as they are partially or totally incorrect:
// Level order traversal doesn't work for this problem

class Solution {
public:
    int rob(TreeNode* root) {
        vector<int> levelSums;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int qSize = q.size();
            int currLvlSum = 0;
            for(int i = 0; i < qSize; i++) {
                TreeNode *curr = q.front();
                q.pop();
                currLvlSum += curr->val;
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);        
            }
            levelSums.push_back(currLvlSum);
        }
        int evenSum = 0, oddSum = 0;
        for(int i = 0; i < levelSums.size(); i++) {
            if(i % 2 == 0) evenSum += levelSums[i];
            else oddSum += levelSums[i];
        }
        return evenSum >= oddSum ? evenSum : oddSum;
    }
};


class Solution {
    void houseRobberRec(int i, vector<int> &arr, int currSum, int &ans) {
        if(i >= arr.size()) {
            ans = max(ans, currSum);
            return;
        }
        houseRobberRec(i + 2, arr, currSum + arr[i], ans);
        houseRobberRec(i + 1, arr, currSum, ans);
    }
public:
    int rob(TreeNode* root) {
        vector<int> levelSums;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int qSize = q.size();
            int currLvlSum = 0;
            for(int i = 0; i < qSize; i++) {
                TreeNode *curr = q.front();
                q.pop();
                currLvlSum += curr->val;
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);        
            }
            levelSums.push_back(currLvlSum);
        }
        int ans = 0;
        houseRobberRec(0, levelSums, 0, ans);
        return ans;        
    }
};

// Totally incorrect
class Solution {
    pair<int, int> houseRobberRec(TreeNode* curr) {
        if(!curr) return {0, 0};


        int left = houseRobberRec(curr->left);
        int right = houseRobberRec(curr->right);
        int nodeNotRobbed = max(left, right);

        int nodeRobbed = curr->val; 

        return {nodeRobbed, nodeNotRobbed};
    }

public:
    int rob(TreeNode* root) {
        pair<int, int> ans = houseRobberRec(root);
        return ans.first >= ans.second ? ans.first : ans.second;
    }
};