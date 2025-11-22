/* LC#77. Combinations

/*
### Approach: Backtracking with Skip-Take Recursion
1. Use a recursive function `rec` to generate all combinations of size `k` from the array `[1, 2, ..., n]`.
2. Base cases:
   - If the size of the current path exceeds `k`, return (prune invalid paths).
   - If the index `i` reaches the end of the array:
     - If the size of the current path is exactly `k`, add it to the result.
3. Recursive steps:
   - Include the current element in the combination and recurse.
   - Exclude the current element from the combination and recurse.
4. Backtrack by removing the last element from the path after exploring each branch.

### Notes:
- This approach generates all possible subsets and filters out those of size `k`.
- It is not the most efficient solution for the combinations problem but is easy to understand.
*/

//  1a. Skip take recursion without path pruning (Prefer 1b ove 1a): 
//  O(2^n) time and O(n) space
// 
class Solution {
    void rec(int i, vector<int> &nums, int k, vector<int> &path, vector<vector<int>> &ans) {
        if(i == nums.size()) {
            if(path.size() == k) ans.push_back(path);
            return;
        }
        path.push_back(nums[i]);
        rec(i+1, nums, k, path, ans);
        path.pop_back();
        rec(i+1, nums, k, path, ans);
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> nums;
        for(int i=0; i<n; i++) nums.push_back(i+1);
        vector<int> path;
        rec(0, nums, k, path, ans);
        return ans;
    }
};

// 1b. Skip take recursion with path pruning (Prefer this over 1a):
// Time Complexity: O(2^n)
// - For each element, we have two choices: include it in the combination or exclude it.
// - This results in 2^n recursive calls in the worst case.

// Space Complexity: O(n)
// - The recursion stack can go as deep as n, where n is the size of the input array.
// - Additional space is used for the `path` vector, which can also grow up to size k.

class Solution {
    void rec(int i, vector<int> &nums, int k, vector<int> &path, vector<vector<int>> &ans) {
        if(path.size() > k) return;                      // Prune paths that exceed the required size
        if(i == nums.size()) {                           // Base case: reached the end of the array
            if(path.size() == k) ans.push_back(path);    // Add valid combinations to the result
            return;
        }
        path.push_back(nums[i]);                         // Include the current element
        rec(i + 1, nums, k, path, ans);                  // Recurse with the current element included
        path.pop_back();                                 // Backtrack: remove the current element
        rec(i + 1, nums, k, path, ans);                  // Recurse without the current element
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;                         // Result vector to store all combinations
        vector<int> nums;                                // Generate the array [1, 2, ..., n]
        for(int i = 0; i < n; i++) nums.push_back(i + 1);
        vector<int> path;                                // Temporary vector to store the current combination
        rec(0, nums, k, path, ans);                      // Start the recursion
        return ans;                                      // Return the result
    }
};



// 1c. Skip take recursion: Gets Memory Limit Exceeded 
// Problem: Passing path by value and not by reference, thus getting MLE
class Solution {
    void rec(int i, vector<int> &nums, int k, vector<int> path, vector<vector<int>> &ans) {
        if(i == nums.size()) {
            if(path.size() == k) ans.push_back(path);
            return;
        }
        path.push_back(nums[i]);
        rec(i+1, nums, k, path, ans);
        path.pop_back();
        rec(i+1, nums, k, path, ans);
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> nums;
        for(int i=0; i<n; i++) nums.push_back(i+1);
        rec(0, nums, k, vector<int>(), ans);
        return ans;
    }
};

// 1d. Skip take recursion: Gets Memory Limit Exceeded 
// Problem: Passing path by value and not by reference, thus getting MLE
class Solution {
    void rec(int i, vector<int> &nums, int k, vector<int> path, vector<vector<int>> &ans) {
        if(path.size() > k) return;
        if(i == nums.size()) {
            if(path.size() == k) ans.push_back(path);
            return;
        }
        rec(i+1, nums, k, path, ans);
        path.push_back(nums[i]);
        rec(i+1, nums, k, path, ans);   // Note. not path.pop_back() here since we are passing by value but this gets MLE
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> nums;
        for(int i=0; i<n; i++) nums.push_back(i+1);
        vector<int> path;
        rec(0, nums, k, path, ans);
        return ans;
    }
};