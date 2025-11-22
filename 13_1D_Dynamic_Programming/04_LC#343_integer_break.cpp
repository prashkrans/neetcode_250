/* LC#343 Integer Break
*/

// 1. Rec without memo
// Time: O(2^(n-1)) ~ O(2^n) and not O(n^n) 
// Space: O(n) due to the rec stack


class Solution {
    int rec(int n, int k) {
        if(n == 0) {
            if(k == 2) return 1;
            return 0;
        };
        int ans = 0;
        for(int i=1; i<=n; i++) {
            int inc = (k == 0 || k == 1) ? 1 : 0;
            ans = max(ans, i * rec(n - i, k + inc));
        }
        return ans;
    }
public:
    int integerBreak(int n) {
        return rec(n, 0);
    }
};

//  2. Rec with memo
// Time Complexity: O(n^2) | 0ms beats 100%
// - The outer loop iterates through all possible values of `i` from 1 to `n`.
// - For each value of `n`, the recursion is called with a reduced value of `n`.
// - Memoization ensures that each subproblem is solved only once, resulting in O(n^2) complexity.

// Space Complexity: O(n)
// - The recursion stack can go as deep as `n` in the worst case.
// - The `dp` array requires O(n * 3) = O(n) space.

class Solution {
    int rec(int n, int k, vector<vector<int>> &dp) {
        if(n == 0) {                                        // Base case: if `n` is 0
            if(k == 2) return dp[0][2] = 1;                 // If at least two parts are formed, return 1
            return dp[0][k] = 0;                            // Otherwise, return 0
        }
        if(dp[n][k] != -1) return dp[n][k];                 // Return the result if already computed
        int ans = 0;                                        // Initialize the maximum product
        for(int i = 1; i <= n; i++) {                       // Iterate through all possible splits
            int inc = (k == 0 || k == 1) ? 1 : 0;           // Increment `k` if it's the first or second part
            ans = max(ans, i * rec(n - i, k + inc, dp));    // Calculate the maximum product
        }
        return dp[n][k] = ans;                              // Store the result in the memoization array
    }
public:
    int integerBreak(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(3, -1));  // Memoization array to store results
        return rec(n, 0, dp);                               // Start the recursive function
    }
};

// ############## yet to fix

class Solution {
public:
    int integerBreak(int n) {
        vector<vector<int>> dp(n+1, vector<int>(3, 0));
        dp[0][2] = 1;
        for(int i=1; i<=n; i++) {
            for(int j=1; j<=i; j++) {
                int k = 0;
                while(k<2) {
                    dp[i][k] = max(dp[i][k], j * dp[i-j][k]);
                    k++;
                }
            }
        }
        return dp[n][2];
    }
};


// 3. Bottom up (Yet to understand)

class Solution {
public:
    int integerBreak(int n) {
        if(n == 2) {
            return 1;
        }

        vector<int> dp(n+1, 1);

        int best = 0;
        for(int i=2; i<n; i++) {
            int w=i;
            for(int j=w; j<=n; j++) {
                dp[j] = max(dp[j], w*dp[j-w]);
            }
            best = max(best, dp[n]);
        }

        return best;
        
    }
};