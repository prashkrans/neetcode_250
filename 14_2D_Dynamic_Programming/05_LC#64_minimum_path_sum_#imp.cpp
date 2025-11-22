/* LC#64. Minimum Path Sum

Note: No visited array is required here since only right and down directions are allowed

### Approach 1: Recursive DFS for Minimum Path Sum
1. The problem is modeled as finding the minimum cost path from the top-left 
to the bottom-right of a grid.
2. A recursive DFS function explores all valid paths by moving either right or down 
from the current cell (i, j).
3. If a move goes out of bounds, the function returns INT_MAX to signify an invalid path 
that should not be chosen.
4. The base case is reaching the destination cell, which returns the cost 
at that grid cell directly.
5. For other cells, the function recursively calculates the cost of going right 
and the cost of going down.
6. It selects the minimum of these two costs and adds the current cell's value 
to this minimum to compute total cost.
7. INT_MAX checks prevent paths from including invalid branches, ensuring correctness 
of path cost computation.
8. This solution is exponential since it recalculates many overlapping subproblems 
without memoization, giving O(2^(m+n)) time.
9. The recursion stack can go as deep as m+n in the worst case, leading to 
O(m + n) space complexity.
*/

// 1. Rec without memo
// Time Complexity: O(2^(m+n)) | Gets TLE at 26/66                      // Each cell makes two recursive calls: down and right
// Space Complexity: O(m + n)                                           // Recursion stack depth is at most m + n

class Solution {
    int dfs(int i, int j, int m, int n, vector<vector<int>> &grid) {
        if(i < 0 || i == m || j < 0 || j == n) return INT_MAX;          // Out of bounds: return max to avoid invalid path
        if(i == m-1 && j == n-1) return grid[m-1][n-1];                 // Reached bottom-right: return its value
        int right = dfs(i, j + 1, m, n, grid);                          // Move right and get min path sum
        int down = dfs(i + 1, j, m, n, grid);                           // Move down and get min path sum
        int minCost = min(right, down);                                 // Choose the smaller of right and down paths
        return (minCost == INT_MAX) ? INT_MAX : grid[i][j] + minCost;   // Add current cell value to min path sum
    }
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();                                            // Total rows
        int n = grid[0].size();                                         // Total columns
        return dfs(0, 0, m, n, grid);                                   // Start DFS from top-left corner
    }
};

// 2. Rec with memo (Prefer this and 3a)
// O(m*n)
// O(m*n)

class Solution {
    int dfs(int i, int j, int m, int n, vector<vector<int>> &grid, vector<vector<int>> &dp) {
        if(i < 0 || i == m || j < 0 || j == n) return INT_MAX;
        if(i == m-1 && j == n-1) return grid[m-1][n-1];
        if(dp[i][j] != -1) return dp[i][j];
        int right = dfs(i, j + 1, m, n, grid, dp);
        int down = dfs(i + 1, j, m, n, grid, dp);
        int minCost = min(right, down);
        return dp[i][j] = (minCost == INT_MAX) ? INT_MAX : grid[i][j] + minCost;
    }
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return dfs(0, 0, m, n, grid, dp);
    }
};

// 3a. Bottom up DP (bottom right to top left) (Prefer this over 3b)
// Time Complexity: O(m * n)                                        // Each cell is visited once in bottom-up DP
// Space Complexity: O(m * n)                                       // DP table of same size as input grid

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();                                        // Number of rows
        int n = grid[0].size();                                     // Number of columns
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));         // DP table to store min path sums
        for(int i=m-1; i>=0; i--) {
            for(int j=n-1; j>=0; j--) {
                if(i == m-1 && j == n-1) dp[i][j] = 0;              // Base case: bottom-right cell has no cost added
                else if(j == n-1) dp[i][j] = dp[i+1][j];            // Only down move possible in last column
                else if(i == m-1) dp[i][j] = dp[i][j+1];            // Only right move possible in last row
                else dp[i][j] = min(dp[i][j+1], dp[i+1][j]);        // Choose minimum between right and down paths
                dp[i][j] += grid[i][j];                             // Add current cell's value to computed path cost
            }
        }
        return dp[0][0];                                            // Return the min path sum from top-left corner
    }
};
    

// 3b. Bottom up DP (top left to bottom right)
// O(m*n) | 0ms beats 100%
// O(m*n)

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(i == 0 && j == 0) dp[i][j] = 0;
                else if(j == 0) dp[i][j] = dp[i-1][j];
                else if(i == 0) dp[i][j] = dp[i][j-1];
                else dp[i][j] = min(dp[i][j-1], dp[i-1][j]);
                dp[i][j] += grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};