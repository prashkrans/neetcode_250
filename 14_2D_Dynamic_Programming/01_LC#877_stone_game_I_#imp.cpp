/* LC#877. Stone Game I
Note: This problem is a special as well as easier case of LC#1140 Stone Game II (refer it)

Easiest Leetcode Medium
Go through the comments, its hilarious like, Hint : Bob is gonna get robbed tonight.

This question has such constraints that only Alice could win even when Bob plays optimally. Simply return true.

Better example: [3,2,10,4]
*/

// 1. Return true since Alice wins always given the constraints
// O(1) time and O(1) space

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};

//  2. Rec without memo
//  O(2^n) Gets TLE at 26/46
//  O(n) since the recursion stack depth is at most O(n)


class Solution {
    int rec(int l, int r, vector<int> &piles, char player) {
        if(l > r) return 0;
        
        if(player == 'A') { // Alice's turn. She picks the pile that maximizes score
            int pickLeft = piles[l] + rec(l+1, r, piles, 'B');
            int pickRight = piles[r] + rec(l, r-1, piles, 'B');
            return max(pickLeft, pickRight);
        }
        else { // Bobs's turn. He also picks the pile that maximizes his score => minimizes Alice's score
            int pickLeft = -piles[l] + rec(l+1, r, piles, 'A');
            int pickRight = -piles[r] + rec(l, r-1, piles, 'A');
            return min(pickLeft, pickRight);
        }      
    }
    
public:
    bool stoneGame(vector<int>& piles) {
        const int n = piles.size();
        int scoreDiff = rec(0, n-1, piles, 'A');
        return (scoreDiff > 0);
    }
};

// 3. Rec with memo (Prefer this method)
// Time Complexity: O(n²)
// We have n² different subproblems (all possible (l,r) pairs)
// Each subproblem is computed exactly once due to memoization

// Space Complexity: O(n²)
// The DP table is an n×n matrix
// The recursion stack depth is at most O(n)

class Solution {
    int rec(int l, int r, vector<int> &piles, char player, vector<vector<int>> &dp) {
        if(l > r) return 0;                                                          // Base case: no more piles to pick
        if(dp[l][r] != -1) return dp[l][r];                                          // Return memoized result if available
        if(player == 'A') { // Alice's turn. She picks the pile that maximizes score
            int pickLeft = piles[l] + rec(l+1, r, piles, 'B', dp);                   // Pick leftmost pile and recurse
            int pickRight = piles[r] + rec(l, r-1, piles, 'B', dp);                  // Pick rightmost pile and recurse
            return dp[l][r] = max(pickLeft, pickRight);                              // Store and return the best option
        }
        else { // Bob's turn. He also picks the pile that maximizes his score => minimizes Alice's score
            int pickLeft = -piles[l] + rec(l+1, r, piles, 'A', dp);                  // Pick leftmost pile (negative for score diff)
            int pickRight = -piles[r] + rec(l, r-1, piles, 'A', dp);                 // Pick rightmost pile (negative for score diff)
            return dp[l][r] = min(pickLeft, pickRight);                              // Store and return the best option
        }      
    }
    
public:
    bool stoneGame(vector<int>& piles) {
        const int n = piles.size();                                                  // Get number of piles
        vector<vector<int>> dp(n, vector<int>(n, -1));                               // Initialize DP table with -1
        int scoreDiff = rec(0, n-1, piles, 'A', dp);                                 // Calculate final score difference
        return (scoreDiff > 0);                                                      // Return true if Alice wins
    }
};

// 4. Bottom up DP (TODO) | Yet to understand fully
// O(n^2) time
// O(n^2) space
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        const int n = piles.size();                                                  // Get number of piles
        vector<vector<int>> dp(n, vector<int>(n, 0));                                // Initialize DP table with 0
        
        // Base case: when l == r, only one pile left
        for (int i = 0; i < n; i++) {
            dp[i][i] = piles[i];                                                     // If only one pile, Alice gets it
        }
        
        // Fill dp table diagonally from smaller subproblems to larger ones
        for (int len = 2; len <= n; len++) {                                         // Consider all possible lengths
            for (int l = 0; l <= n - len; l++) {                                     // Consider all possible starts
                int r = l + len - 1;                                                 // Calculate end position
                
                // For odd lengths, it's Alice's turn; for even lengths, it's Bob's turn
                // But we can calculate the optimal score difference directly
                int pickLeft = piles[l] - dp[l+1][r];                                // Alice takes left, subtract Bob's optimal play
                int pickRight = piles[r] - dp[l][r-1];                               // Alice takes right, subtract Bob's optimal play
                
                dp[l][r] = max(pickLeft, pickRight);                                 // Store the best option
            }
        }
        
        return dp[0][n-1] > 0;                                                       // Return true if Alice wins
    }                                                                                // Time: O(n²), Space: O(n²)
};

// Incorrect Codes
// ###########################################
// Ignore the codes below as they are incorrect since in the codes below only Alice plays optimally while Bob does not. 
// But the problems asks that both Alice and Bob should play optimally

class Solution {
    int rec(int l, int r, vector<int> &piles, char player) {
        if(l > r) return 0;
        if(player == 'A') {
            if(piles[l] <= piles[r]) 
                return piles[r] + rec(l, r-1, piles, 'B');
            else
                return piles[l] + rec(l+1, r, piles, 'B');
        }
        else {
            if(piles[l] > piles[r]) 
                return -1*piles[r] + rec(l, r-1, piles, 'A');
            else
                return -1*piles[l] + rec(l+1, r, piles, 'A');
        }      
    }
public:
    bool stoneGame(vector<int>& piles) {
        const int n = piles.size();
        int scoreDiff = rec(0, n-1, piles, 'A');
        return (scoreDiff > 0);
    }
};

// or, same as above but with print debuggers for better understanding
class Solution {
    int rec(int l, int r, vector<int> &piles, char player) {
        if(l > r) return 0;
        if(player == 'A') {
            if(piles[l] <= piles[r]) {
                cout<<"Alice picks: "<<piles[r]<<endl;
                return piles[r] + rec(l, r-1, piles, 'B');
            }
            else {
                cout<<"Alice picks: "<<piles[l]<<endl;
                return piles[l] + rec(l+1, r, piles, 'B');       
            }
        }
        else {
            if(piles[l] > piles[r]) {
                cout<<"Bob picks: "<<piles[r]<<endl;
                return -1*piles[r] + rec(l, r-1, piles, 'A');
            }
            else {
                cout<<"Bob picks: "<<piles[l]<<endl;
                return -1*piles[l] + rec(l+1, r, piles, 'A');       
            }
        }      
    }
public:
    bool stoneGame(vector<int>& piles) {
        const int n = piles.size();
        int scoreDiff = rec(0, n-1, piles, 'A');
        cout<<"scoreDiff: "<<scoreDiff<<endl;
        if(scoreDiff >= 0) return true;
        else return false;
    }
};