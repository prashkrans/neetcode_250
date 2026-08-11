/* LC#18. 4Sum */

/*
Approach 1: Backtracking with Sorted Duplicate Elimination (My method)
1. Sort the array so identical quadruplets have the same element order.
2. Recursively decide whether to include or exclude every array element.
3. Maintain a path containing the currently selected elements.
4. Stop paths longer than four because only quadruplets are required.
5. When all elements are processed, store paths with four elements and target zero.
6. A set automatically removes duplicate quadruplets.
*/

// Time Complexity: O(n^4 log n) | Note: O(2^n) >> O(n^4) | Passes 235/295 test cases
// Space Complexity: O(n^4), including the set storing unique quadruplets; O(n) auxiliary recursion space.

class Solution {                                                    // Defines the solution class.
    void rec(int i, vector<int> &nums, int target, set<vector<int>> &ans, vector<int> &path) { // Explores include/exclude choices.
        if(i == nums.size()) {                                      // Checks whether every element is processed.
            if(target == 0 && path.size() == 4)                     // Verifies a valid quadruplet sum and size.
                ans.insert(path);                                   // Stores the unique valid quadruplet.
            return;                                                 // Ends this recursive branch.
        }
        if(path.size() > 4) return;                                 // Prunes selections larger than four elements.
        path.push_back(nums[i]);                                    // Includes the current number in the path.
        rec(i + 1, nums, target - nums[i], ans, path);              // Recurses after choosing the current number.
        path.pop_back();                                            // Removes the current number for backtracking.
        rec(i + 1, nums, target, ans, path);                        // Recurses without choosing the current number.
    }
    public:                                                         // Exposes the required function publicly.
    vector<vector<int>> fourSum(vector<int>& nums, int target) {    // Finds all unique quadruplets with target sum.
        sort(nums.begin(), nums.end());                             // Sorts numbers for consistent quadruplet ordering.
        set<vector<int>> ans;                                       // Stores unique quadruplets in sorted order.
        vector<int> path;                                           // Tracks elements chosen during recursion.
        rec(0, nums, target, ans, path);                            // Starts recursive exploration from index zero.
        return {ans.begin(), ans.end()};                            // Converts the set into the required vector.
    }
};

