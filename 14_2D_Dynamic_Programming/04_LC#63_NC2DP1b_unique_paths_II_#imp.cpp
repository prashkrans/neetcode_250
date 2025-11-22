// LC#63. NC2DP1b. Unique Paths II

// Note: No visited array is required here since only right and down directions are allowed

// Method 1: Rec without memo:
// O(2^(m*n)) since we have two directions/choices at each cell
// O(m + n) since only right and down allowed so rec stack depth is atmost m + n

class Solution {
    int dfs(int i, int j, int m, int n, vector<vector<int>> &grid) {
        if(i < 0 || i == m || j < 0 || j == n || grid[i][j] == 1) return 0;
        if(i == m-1 && j == n-1) return 1;
        return dfs(i, j + 1, m, n, grid) + dfs(i + 1, j, m, n, grid);
    }
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        return dfs(0, 0, m, n, obstacleGrid);
    }
};

// Method 2: Rec with memo (Prefer this and method 3)
// O(m*n) since each cell is processed atmost once | 0ms beats 100%
// O(m*n) due to the 2D DP array

class Solution {
    int dfs(int i, int j, int m, int n, vector<vector<int>> &grid, vector<vector<int>> &dp) {
        if(i < 0 || i == m || j < 0 || j == n || grid[i][j] == 1) return 0;
        if(i == m-1 && j == n-1) return dp[m-1][n-1] = 1;
        if(dp[i][j] != -1) return dp[i][j];
        return dp[i][j] = dfs(i, j + 1, m, n, grid, dp) + dfs(i + 1, j, m, n, grid, dp);
    }
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return dfs(0, 0, m, n, obstacleGrid, dp);
    }
};

// Method 3: Bottom up DP
// O(m*n) | 0ms beats 100%
// O(m*n) due to the 2D DP array

// the addtion was giving an error hence used long long instead of int
typedef long long ll;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {   // Function to count unique paths with obstacles
        int m = obstacleGrid.size();                                    // Number of rows
        int n = obstacleGrid[0].size();                                 // Number of columns
        if(obstacleGrid[m-1][n-1] == 1) return 0;                       // If destination has obstacle, no path exists
        vector<vector<ll>> dp(m+1, vector<ll>(n+1, 0));                 // DP table with padding includes last row and col = 0
        for(int i=m-1; i>=0; i--) {                                     // Iterate from bottom row up
            for(int j=n-1; j>=0; j--) {                                 // Iterate from rightmost column left
                if(i==m-1 && j==n-1) dp[i][j] = 1;                      // Base case: destination cell has 1 path
                else if(obstacleGrid[i][j] == 0)                        // If current cell has no obstacle
                    dp[i][j] = dp[i][j+1] + dp[i+1][j];                 // Paths = paths from right + paths from below
                else dp[i][j] = 0;                                      // If obstacle present, no paths through this cell
            }
        }
        return dp[0][0];                                                // Return total paths from top-left to bottom-right
    }
};