/* LC#1406. Stone Game III (Maximize score difference)

Note: This problem is slightly different from LC#877 Stone Game I and LC#1140 Stone Game II 
since in those two we maximize the score of Alice while in this problem we need to maximize the
score difference instead of score of Alice. Hence, needs a modified but easier approach.
Here, we don't need char player 'A' or 'B' or aliceTurn = true or false

This needs more practice

### Approach: Dynamic Programming with Recursion and Memoization
1.  Use a recursive function (DFS) that calculates the maximum possible score
    difference starting from a given index `i` in the stoneValue array.
2.  At every index `i`, try taking 1, 2, or 3 stones, summing their values,
    and subtracting the result of the opponent's best move (recursively).
3.  Store results in a memoization table (dp array) to avoid redundant
    calculations, ensuring time efficiency by avoiding recomputation.
4.  The recursive base case returns 0 if all stones are taken, meaning no
    further gain or loss can be made from that point.
5.  The key insight is modeling the game as a zero-sum situation, where one
    player's gain is the other's loss, leading to the subtraction step.
6.  After evaluating all options, return the max score difference the current
    player can enforce from index `i` onward using optimal strategy.
7.  At the end, compare the final score difference from index 0 to decide if
    Alice wins, Bob wins, or it is a tie based on positivity of the result.
*/

// A1. Rec without memo:
// O(3^n) | Gets TLE at 160/185
// O(n)

// Time Complexity: O(3^n)                        // Each state branches into up to 3 recursive calls (no memoization)
// Space Complexity: O(n)                         // Max recursion depth is n due to DFS stack

class Solution {
    int rec(int i, vector<int> &stoneValue) {
        const int n = stoneValue.size();                                     // Store length of stoneValue
        if(i == n) return 0;                                                 // Base case: no stones left
        int res = INT_MIN;                                                   // Initialize result as very negative
        int sum = 0;                                                         // Sum of current player's taken stones
        int j=i;                                                             
        while(j < n && j < i + 3) {                                          // Take up to 3 stones if available
            sum += stoneValue[j];                                            // Add current stone value to sum
            res = max(res, sum - rec(j+1, stoneValue));                      // Maximize current diff by subtracting opponent
            j++;                                                             // Move to next stone
        }
        return res;                                                          // Return best score difference from index i
    }
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int scoreDiff = rec(0, stoneValue);                                  // Compute net score difference from start
        if(scoreDiff > 0) return "Alice";                                    // Alice wins if scoreDiff > 0
        else if(scoreDiff < 0) return "Bob";                                 // Bob wins if scoreDiff < 0
        else return "Tie";                                                   // Tie if both scores are equal
    }
};

//  A2. Rec with memo (Prefer this method)
//  Time Complexity: O(n)                           // Each state i is visited once and memoized
//  Space Complexity: O(n)                          // For the dp array used for memoization

class Solution {
    // Returns the maximum score difference (Alice's score - Bob's score) 
    // that can be achieved starting from position i
    int dfs(int i, vector<int>& stoneValue, vector<int>& dp) {
        if (i >= stoneValue.size()) return 0;                              // Base case: no more stones to take

        if (dp[i] != INT_MIN) return dp[i];                                // Return cached result if available

        int sum = 0;                                                       // To accumulate values of stones taken
        int best = INT_MIN;                                                // Tracks max score difference achievable

        // Try taking 1, 2, or 3 stones
        for (int j = i; j < i + 3 && j < stoneValue.size(); j++) {
            sum += stoneValue[j];                                          // Add current stone to sum
            // Current sum minus opponent's best play
            best = max(best, sum - dfs(j + 1, stoneValue, dp));            // Maximize Alice's score difference
        }

        return dp[i] = best;                                               // Cache and return best score difference
    }

public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();                                         // Number of stones
        vector<int> dp(n + 1, INT_MIN);                                    // DP array to store max score diff, not using -1 here

        int scoreDiff = dfs(0, stoneValue, dp);                            // Start DFS from index 0

        if (scoreDiff > 0) return "Alice";                                 // Alice wins if scoreDiff > 0
        else if (scoreDiff < 0) return "Bob";                              // Bob wins if scoreDiff < 0
        else return "Tie";                                                 // Tie if scoreDiff == 0
    }
};

// A3. Bottom up TODO


/* Refer the dry run below to understand the approach better
### Dry Run: stoneValue = [1, 2, 3, 7]

Calling rec(0):
- i = 0
  -> Take 1 stone (1), sum = 1
     -> rec(1):
        - i = 1
          -> Take 1 stone (2), sum = 2
             -> rec(2):
                - i = 2
                  -> Take 1 stone (3), sum = 3
                     -> rec(3):
                        - i = 3
                          -> Take 1 stone (7), sum = 7
                             -> rec(4) = 0 → score = 7 - 0 = 7
                          -> result at i=3 = max(-INF, 7) = 7
                        → rec(3) returns 7
                     → score = 3 - 7 = -4
                  -> Take 2 stones (3+7), sum = 10
                     -> rec(4) = 0 → score = 10 - 0 = 10
                  → result at i=2 = max(-4, 10) = 10
                → rec(2) returns 10
             → score = 2 - 10 = -8
          -> Take 2 stones (2+3), sum = 5
             -> rec(3) = 7 → score = 5 - 7 = -2
          -> Take 3 stones (2+3+7), sum = 12
             -> rec(4) = 0 → score = 12 - 0 = 12
          → result at i=1 = max(-8, -2, 12) = 12
        → rec(1) returns 12
     → score = 1 - 12 = -11
  -> Take 2 stones (1+2), sum = 3
     -> rec(2) = 10 → score = 3 - 10 = -7
  -> Take 3 stones (1+2+3), sum = 6
     -> rec(3) = 7 → score = 6 - 7 = -1
→ result at i=0 = max(-11, -7, -1) = -1

Final scoreDiff = -1 → return "Bob"
*/



// My custom methods: (Takes more time but easier to understand and remember)
// B1. Rec without memo: Works great but gets TLE at 160/185
// B2. Rec without memo
// B3. Bottom up DP (TODO)

// B1a. Rec without memo with sumA and sumB instead of gameSum
// O(3^n) | Gets TLE at 160/185
// O(n) due to the recursion stack
// Gets TLE at 160/185
class Solution {
    int rec(int i, vector<int> &stoneValue, int sumA, int sumB, char player) {
        if(i==stoneValue.size()) return sumA - sumB;
        int res = (player == 'A') ? INT_MIN : INT_MAX;
        int j=i;
        int currSum = 0;
        while(j<stoneValue.size() && j<i+3) {
            currSum += stoneValue[j];
            if(player == 'A') res = max(res, rec(j+1, stoneValue, sumA + currSum, sumB, 'B'));
            else res = min(res, rec(j+1, stoneValue, sumA, sumB + currSum, 'A'));
            j++;
        }
        return res;
    }
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int gameSum = rec(0, stoneValue, 0, 0, 'A');
        if(gameSum > 0) return "Alice";
        else if(gameSum < 0) return "Bob";
        return "Tie";
    }
};

// B1b. Rec without memo using gameSum (Prefer this method over B1a)
// or same as above but merging sumA and sumB into gameSum = sumA - sumB
// O(3^n) | Gets TLE at 160/185
// O(n) due to the recursion stack

class Solution {
    int rec(int i, vector<int> &stoneValue, int gameSum, char player) {
        if(i==stoneValue.size()) return gameSum;
        int res = (player == 'A') ? INT_MIN : INT_MAX;
        int j=i;
        int currSum = 0;
        while(j<stoneValue.size() && j<i+3) {
            currSum += stoneValue[j];
            if(player == 'A') res = max(res, rec(j+1, stoneValue, gameSum + currSum, 'B'));
            else res = min(res, rec(j+1, stoneValue, gameSum - currSum, 'A'));
            j++;
        }
        return res;
    }
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int gameSum = rec(0, stoneValue, 0, 'A');
        if(gameSum > 0) return "Alice";
        else if(gameSum < 0) return "Bob";
        return "Tie";
    }
};

/* B2b. Rec with memo using gameSum (Prefer this method)
Time and Space Complexity Analysis for Stone Game III (Memoized Recursive Version)
Time Complexity: O(N)
---------------------
- Let N be the length of the stoneValue array.
- There are two players (Alice and Bob), and we use a 2D dp table: dp[i][player], where player ∈ {0,1}.
- Each index i (0 ≤ i < n) has at most 2 states (one for each player).
- For each dp[i][player], we try up to 3 possible moves (taking 1, 2, or 3 stones).
- Since memoization ensures each (i, player) state is only computed once, total work is:
    => O(2N * 3) = O(N)

Space Complexity: O(N)
-----------------------
- dp table: O(N) space for dp[n][2]
- Recursion stack: In the worst case, the recursion goes as deep as n (taking 1 stone at each turn).
    => O(n) auxiliary stack space
Total space: O(n) + O(n) = O(n)
*/

class Solution {
    vector<vector<int>> dp; // dp[i][player]: 0 for Alice, 1 for Bob

    int rec(int i, vector<int> &stoneValue, int player) {
        if(i == stoneValue.size()) return 0;

        if(dp[i][player] != INT_MIN && player == 0) return dp[i][player];
        if(dp[i][player] != INT_MAX && player == 1) return dp[i][player];

        int res = (player == 0) ? INT_MIN : INT_MAX;
        int currSum = 0;

        for(int j = i; j < i + 3 && j < stoneValue.size(); ++j) {
            currSum += stoneValue[j];
            if(player == 0) { // Alice's turn: maximize score difference
                res = max(res, currSum + rec(j + 1, stoneValue, 1));
            } else { // Bob's turn: minimize Alice's score
                res = min(res, -currSum + rec(j + 1, stoneValue, 0));
            }
        }

        dp[i][player] = res;
        return res;
    }

public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        dp = vector<vector<int>>(n, vector<int>(2));
        // Initialize dp[i][0] for Alice as INT_MIN, dp[i][1] for Bob as INT_MAX
        for(int i = 0; i < n; ++i) {
            dp[i][0] = INT_MIN;
            dp[i][1] = INT_MAX;
        }

        int gameSum = rec(0, stoneValue, 0); // 0: Alice, 1: Bob

        if(gameSum > 0) return "Alice";
        else if(gameSum < 0) return "Bob";
        return "Tie";
    }
};



// ##########################################################################################3
// Ignore this code: This code works when all values of stoneValue are non-negative
class Solution {
    string rec(int i, vector<int> &stoneValue, int sumA, int sumB, char player) {
        if(i==stoneValue.size()) {
            if(sumA > sumB) return "Alice";
            else if(sumA < sumB) return "Bob";
            return "Tie";
        }
        int j=i;
        int currSum = 0;
        while(j<stoneValue.size() && j<i+3) {
            currSum += stoneValue[j];
            j++;
        }
        if(player == 'A') return rec(j, stoneValue, sumA + currSum, sumB, 'B');
        else return rec(j, stoneValue, sumA, sumB + currSum, 'A');
    }
public:
    string stoneGameIII(vector<int>& stoneValue) {
        return(rec(0, stoneValue, 0, 0, 'A'));
    }
};