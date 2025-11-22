/* LC#377. Combination Sum IV
*/

// 1. Rec without memo

// Time Complexity: O(n^target) where n is the size of nums array
// Space Complexity: O(target) due to recursion stack depth

// Explanation:
// - For each recursive call, we try all n numbers in nums
// - The recursion depth can go up to target (if we subtract 1 each time)
// - Each recursive call branches into n more calls, creating a tree of height O(target)
// - Without memoization, we recalculate many overlapping subproblems
// - Total number of operations is O(n^target) in worst case
// - The recursion stack uses O(target) space at maximum depth

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        if(target < 0) return 0;
        if(target == 0) return 1;
        int ans = 0;
        for(int i=0; i<nums.size(); i++) {
            ans += combinationSum4(nums, target - nums[i]);
        }
        return ans;
    }
};

// 2. Rec with memo (Prefer this method)

// Time Complexity: O(target * nums.size()) = O(t * n) where n = nums.size() and t = target
// - Each subproblem is solved once due to memoization, and there are `target` subproblems.
// - For each subproblem, we iterate through `nums`, resulting in O(target * nums.size()).
// 0ms beats 100%

// Space Complexity: O(target/m) = O(target) if m = 1 where m: min value of nums
// - The recursion stack can go as deep as `target` in the worst case.
// - The `dp` array requires O(target) space.

class Solution {
    int rec(vector<int> &nums, int target, vector<int> &dp) {
        if(target < 0) return 0;                        // Base case: no valid combination
        if(target == 0) return dp[0] = 1;               // Base case: one valid combination (empty set)
        if(dp[target] != -1) return dp[target];         // Return the result if already computed
        int ans = 0;                                    // Initialize the count of combinations
        for(int i = 0; i < nums.size(); i++) {          // Iterate through all numbers
            ans += rec(nums, target - nums[i], dp);     // Recursive call for the reduced target
        }
        return dp[target] = ans;                        // Store the result in the memoization array
    }
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, -1);                 // Memoization array to store results for subproblems
        return rec(nums, target, dp);                   // Start the recursive function
    }
};

// 3. Bottom Up DP

// Time Complexity: O(target * nums.size())
// - The outer loop runs from 1 to `target`, and the inner loop iterates through `nums`.
// - This results in O(target * nums.size()) iterations.

// Space Complexity: O(target)
// - The `dp` array requires O(target) space to store the number of combinations for each subproblem.

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {    // Using uint instead of int to support 1 + INT_MAX
        vector<uint> dp(target + 1, 0);                // Initialize the DP array with 0
        dp[0] = 1;                                     // Base case: one way to make target 0 (empty set)
        for(int i = 1; i <= target; i++) {             // Iterate through all target values from 1 to target
            for(int j = 0; j < nums.size(); j++) {     // Iterate through all numbers in nums
                if(i - nums[j] >= 0)                   // Check if the current number can contribute to the target
                    dp[i] += dp[i - nums[j]];          // Add the combinations for the reduced target
            }
        }
        return dp[target];                             // Return the number of combinations for the given target
    }
};