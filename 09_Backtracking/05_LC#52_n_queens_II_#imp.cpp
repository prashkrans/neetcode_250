/* LC#52. N-Queens II
Verified that its is exactly same as LC#51. N-Queens I so, refer it for the detailed approach.

Approach 1a:
a. For all cols (0 to n) try to place a queen in each row
b. Three cases:
    b1. All cells to the left in the same row   |   (i, j-1)
    b2. All cells in the upper left diagonal    |   (i-1, j-1)
    b3. All cells in the lower left diagonal    |   (i+1, j-1)      

Approach 1b: (TODO)
a. For all rows (0 to n) try to place a queen in each cols
b. Three cases:
    b1. All cells above in the same col         |   (i-1, j)
    b2. All cells in the upper left diagonal    |   (i-1, j-1)
    b3. All cells in the upper right diagonal   |   (i-1, j+1)
*/

// 1. Backtrack with path pruning (isSafe())
// Running time: O(n!) i.e. factorial of n where n is the board side
// Auxiliary space: O(n)

class Solution {
    bool isSafe(int i, int j, int n, vector<string> &board) {
        // check left cells in the same row, top left diag and bottom left diag
        int r = i, c = j;
        while(j>=0) {                                   // Check left (row)
            if(board[i][j] == 'Q') return false;
            j--;
        }
        j = c;
        while(i>=0 && j>=0) {                           // Check upper-left diagonal
            if(board[i][j] == 'Q') return false;
            i--;    
            j--;
        }
        i = r;  j = c;
        while(i<n && j>=0) {                            // Check lower-left diagonal
            if(board[i][j] == 'Q') return false;
            i++;    
            j--;
        }
        return true;                                     // Position is safe
    }

    void backtrack(int j, int n, vector<string> &board, vector<vector<string>> &ans) {
        if(j==n) {                                       // All queens placed successfully
            ans.push_back(board);
            return;
        }
        for(int i=0; i<n; i++) {                         // Try each row in current column
            if(isSafe(i, j, n, board)) {                 // Check if position is safe
                board[i][j] = 'Q';                       // Place queen
                backtrack(j+1, n, board, ans);           // Recur for next column
                board[i][j] = '.';                       // Remove queen (backtrack)
            }
        }
    }

public:
    int totalNQueens(int n) {
        vector<vector<string>> ans;                      // Store all solutions
        vector<string> board(n, string(n, '.'));         // Initialize empty board
        backtrack(0, n, board, ans);                     // Start backtracking from column 0
        return ans.size();                               // Return all valid arrangements
    }
};