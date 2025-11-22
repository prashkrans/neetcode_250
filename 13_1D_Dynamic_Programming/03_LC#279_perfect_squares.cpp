
// 1. Rec without memoization
// Time Complexity: O(n^(sqrt(n)))
// - This is a naive recursive approach without memoization.
// - For each number `n`, we try all perfect squares up to `sqrt(n)`.
// - This results in an exponential time complexity.

// Space Complexity: O(n)
// - The recursion stack can go as deep as `n` in the worst case.

class Solution {
public:
    int numSquares(int n) {
        if(n < 0) return INT_MAX;                        // Base case: invalid state
        if(n == 0) return 0;                             // Base case: 0 requires 0 perfect squares
        int res = INT_MAX;
        for(int i = 1; i * i <= n; i++) {                // Iterate through all perfect squares <= n
            res = min(res, numSquares(n - i * i));       // Recurse for the remaining value
        }
        return (res == INT_MAX) ? res : 1 + res;         // Return the minimum count of perfect squares
    }
};

// 2. Rec with memoization
// Time Complexity: O(n * sqrt(n))
// - For each value from 1 to n, we're trying all perfect squares up to sqrt(n)
// - Each state is computed only once due to memoization
// - Total number of states = n
// - Work per state = O(sqrt(n))

// Space Complexity: O(n)
// - O(n) for the dp array storing results for all values from 0 to n
// - O(n) for the recursion stack in worst case
// - Overall space complexity = O(n)

class Solution {
    int rec(int n, vector<int> &dp) {
        if(n<0) return INT_MAX;
        if(n==0) return dp[0] = 0;
        if(dp[n] != -1) return dp[n];
        int res = INT_MAX;
        for(int i=1; i*i <= n; i++) {
            res = min(res, rec(n - i*i, dp));
        }
        return dp[n] = (res == INT_MAX) ? res : 1 + res;
    }
public:
    int numSquares(int n) {
        vector<int> dp(n+1, -1);
        return rec(n, dp);
    }
};

// 3. Bottom-up DP
// Time Complexity: O(n * sqrt(n))
// - Outer loop runs n times (from 1 to n)
// - Inner loop runs sqrt(n) times in worst case (testing perfect squares up to sqrt(i))
// - Each operation inside loops is O(1)
// - Total: O(n * sqrt(n))

// Space Complexity: O(n)
// - Single dp array of size n+1
// - No recursion stack overhead
// - Total: O(n)

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        for(int i=1; i<=n; i++) {
            for(int j=1; j*j <= i; j++) 
                dp[i] = min(dp[i], 1 + dp[i - j*j]);
        }
        return dp[n];
    }
};