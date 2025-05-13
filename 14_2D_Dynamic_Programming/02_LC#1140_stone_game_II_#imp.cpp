/* LC#1140. Stone Game II (MinMax DP)

### Approach: Dynamic Programming with Minimax and Variable Window Size
1. Define a recursive function rec(i, m, turn) that computes the maximum score
Alice can obtain from index i with parameter M, and current player's turn.
2. M determines the maximum number of stones a player can take in a move, up
to 2 * M stones from the current position.
3. Alice tries to maximize the score by taking j stones and adding their sum
plus the result of Bob’s best response (recursion with turn = false).
4. Bob tries to minimize Alice's score by choosing j stones and calling the
recursion with Alice’s turn, without adding to the score (zero-sum model).
5. Each recursive call explores options from 1 to 2M stones and memoizes the
result using a 3-level unordered_map to avoid recomputation.
6. The recursion ends when i == n (no stones left), returning 0 as the base
case, meaning no value left to gain.
7. The final result is the maximum score Alice can achieve starting from
index 0, M = 1, and it's Alice’s turn, as returned by stoneGameII().
*/

// 1a. Rec without memo
// gets TLE 25/92
/*
Time Complexity: O(2^n)
1. At each index i, the function can make up to 2 * m recursive calls.
2. Since m increases (up to n in the worst case), each recursive call may
   lead to multiple new calls (branching factor up to O(n)).
3. The recursion explores all combinations of i, m, and turn without
   memoization — meaning overlapping subproblems are recalculated.
4. The total number of such recursive states grows exponentially with n,
   leading to an overall time complexity of O(2^n) in the worst case.

Space Complexity: O(n)
1. The recursive depth corresponds to the number of remaining piles,
   i.e., in the worst case the recursion goes n levels deep.
2. No additional memory (like memoization table or arrays) is used;
   space is consumed only by the call stack.
3. Therefore, the maximum space used is proportional to the depth of
   recursion, which is O(n).
*/

class Solution {
    int rec(int i, vector<int> &piles, int m, bool aliceTurn) {
        const int n = piles.size();
        if(i == n) return 0;
        int res = (aliceTurn) ? INT_MIN : INT_MAX;
        int j = i;
        int x = 2*m;
        int currSumAlice = 0;
        while(j<n && j<i+x) {
            int newM = max(m, j-i+1);
            currSumAlice += piles[j];
            if(aliceTurn) {
                res = max(res, currSumAlice + rec(j+1, piles, newM, false));
            }
            else res = min(res, rec(j+1, piles, newM, true));       // [#IMP] Bob minimizes but doesn't subtract currSum here
            j++;
        }
        return res;        
    }
public:
    int stoneGameII(vector<int>& piles) {
        int scoreAlice = rec(0, piles, 1, true);
        return scoreAlice;
    }
};

// or, similar to above but return scoreDiff instead of scoreAlice
// 1b. Rec without memo
// gets TLE 25/92

class Solution {
    int rec(int i, vector<int> &piles, int m, bool aliceTurn) {
        const int n = piles.size();
        if(i == n) return 0;
        int res = (aliceTurn) ? INT_MIN : INT_MAX;
        int j = i;
        int x = 2*m;
        int currSum = 0;
        while(j<n && j<i+x) {
            int newM = max(m, j-i+1);
            currSum += piles[j];
            if(aliceTurn) {
                res = max(res, currSum + rec(j+1, piles, newM, false));
            }
            else res = min(res, -currSum + rec(j+1, piles, newM, true));    // [#IMP] Bob minimizes and also subtracts currSum here
            j++;
        }
        return res;        
    }
public:
    int stoneGameII(vector<int>& piles) {
        int scoreDiff = rec(0, piles, 1, true);
        int totalPiles = 0;
        for(int i=0; i<piles.size(); i++) totalPiles += piles[i];
        int scoreAlice = (totalPiles + scoreDiff)/2;
        return scoreAlice;
    }
};

// 2a. Rec with memo (Pseudo 3D DP Hashmap)

// Time Complexity: O(n*n*2) ~ O(n^2)                         // At most n * n * 2 states, each exploring up to 2M moves
// Space Complexity: O(n*n*2) ~ O(n^2)                        // For pseudo-3D DP: dp[i][m][aliceTurn] where aliceTurn ∈ {0,1}

class Solution {
    int rec(int i, vector<int> &piles, int m, bool aliceTurn, unordered_map<int, unordered_map<int, unordered_map<int, int>>> &dp) {
        const int n = piles.size();                                             // Total number of piles
        if(i == n) return 0;                                                    // No more stones to pick
        
        if(dp[i][m].count(aliceTurn)) return dp[i][m][aliceTurn];               // Memoization check

        int res = (aliceTurn) ? INT_MIN : INT_MAX;                              // Initialize result based on turn
        int currSum = 0;                                                        // Track stones taken in this move
        int x = 2*m;                                                            // Max number of stones allowed to take
        int j = i;
        while(j < n && j < i + x) {                                             // Try taking 1 to 2M stones
            currSum += piles[j];                                                // Accumulate stone values
            int newM = max(m, j - i + 1);                                       // Update M based on max stones taken
            if(aliceTurn) {                                                         
                res = max(res, currSum + rec(j + 1, piles, newM, false, dp));   // Alice adds value to score
            }
            else {
                res = min(res, rec(j + 1, piles, newM, true, dp));              // Bob minimizes Alice's gain
            }
            j++;
        }
        return dp[i][m][aliceTurn] = res;                                       // Memoize and return result
    }
public:
    int stoneGameII(vector<int>& piles) {
        const int n = piles.size();                                             // Get number of piles
        unordered_map<int, unordered_map<int, unordered_map<int, int>>> dp;     // 3D DP map
        int scoreAlice = rec(0, piles, 1, true, dp);                            // Start recursion from 0 with M=1 and Alice's turn
        return scoreAlice;                                                      // Return maximum score Alice can achieve
    }
};


// or, similar to above but return scoreDiff instead of scoreAlice
// 2b. Rec with memo (3D DP)

class Solution {
    int rec(int i, vector<int> &piles, int m, bool aliceTurn, unordered_map<int, unordered_map<int, unordered_map<int, int>>> &dp) {
        const int n = piles.size();
        if(i == n) return 0;
        // if(dp.count(i) && dp[i].count(m) && dp[i][m].count(aliceTurn)) return dp[i][m][aliceTurn]; // redundant
        if(dp[i][m].count(aliceTurn)) return dp[i][m][aliceTurn];
        int res = (aliceTurn) ? INT_MIN : INT_MAX;
        int x = 2*m;
        int currSum = 0;
        for(int j=i; j<n && j<i+x; j++) {
            currSum += piles[j];
            int newM = max(m, j-i+1);
            if(aliceTurn) {
                res = max(res, currSum + rec(j+1, piles, newM, false, dp));
            }
            else {
                res = min(res, -currSum + rec(j+1, piles, newM, true, dp));
            }
        }
        return dp[i][m][aliceTurn] = res;     
    }
public:
    int stoneGameII(vector<int>& piles) {
        const int n = piles.size();
        unordered_map<int, unordered_map<int, unordered_map<int, int>>> dp;
        int scoreDiff = rec(0, piles, 1, true, dp);
        int totalPiles = 0;
        for(int i=0; i<n; i++) totalPiles += piles[i];
        int scoreAlice = (totalPiles + scoreDiff)/2;
        return scoreAlice;
    }
};

// or, same as above but using unordered_map<int, map<pair<int, int>, int>> &dp

class Solution {
    int rec(int i, vector<int> &piles, int m, bool aliceTurn, unordered_map<int, map<pair<int, int>, int>> &dp) {
        const int n = piles.size();
        if(i == n) return 0;
        if(dp[i].count({m, aliceTurn})) return dp[i][{m, aliceTurn}];
        int res = (aliceTurn) ? INT_MIN : INT_MAX;
        int currSum = 0;
        int x = 2*m;
        int j = i;
        while(j<n && j<i+x) {
            currSum += piles[j];
            int newM = max(m, j-i+1);
            if(aliceTurn) {
                res = max(res, currSum + rec(j+1, piles, newM, false, dp));
            }
            else {
                res = min(res, rec(j+1, piles, newM, true, dp));
            }
            j++;
        }
        return dp[i][{m, aliceTurn}] = res;     
    }
public:
    int stoneGameII(vector<int>& piles) {
        const int n = piles.size();
        unordered_map<int, map<pair<int, int>, int>> dp;
        int scoreAlice = rec(0, piles, 1, true, dp);
        return scoreAlice;
    }
};

// or, same as above but using map<pair<bool, pair<int, int>>, int> &dp

class Solution {
    int rec(int i, vector<int> &piles, int m, bool aliceTurn, map<pair<bool, pair<int, int>>, int> &dp) {
        const int n = piles.size();
        if(i == n) return 0;
        if(dp.count({aliceTurn, {i, m}})) return dp[{aliceTurn, {i, m}}];
        int res = (aliceTurn) ? INT_MIN : INT_MAX;
        int currSum = 0;
        int x = 2*m;
        int j = i;
        while(j<n && j<i+x) {
            currSum += piles[j];
            int newM = max(m, j-i+1);
            if(aliceTurn) {
                res = max(res, currSum + rec(j+1, piles, newM, false, dp));
            }
            else {
                res = min(res, rec(j+1, piles, newM, true, dp));
            }
            j++;
        }
        return dp[{aliceTurn, {i, m}}] = res;     
    }
public:
    int stoneGameII(vector<int>& piles) {
        const int n = piles.size();
        map<pair<bool, pair<int, int>>, int> dp;
        int scoreAlice = rec(0, piles, 1, true, dp);
        return scoreAlice;
    }
};

/*
### Approach B1: Recursive Subset Partitioning with Min Difference
1. The problem is modeled as partitioning the array of stones into two subsets such that 
the absolute difference of their sums is minimized.
2. A recursive function is used to try all possible ways of assigning stones into 
two subsets, by either adding or subtracting each stone's weight from a running 
difference.
3. For each stone, the algorithm chooses to either include it in the "left" group 
(by adding to sumDiff) or in the "right" group (by subtracting from sumDiff).
4. This forms a binary decision tree where each node represents the current difference 
after considering a subset of stones.
5. The base case is when all stones are used, at which point the absolute value of 
the accumulated sumDiff is returned.
6. The final answer is the minimum absolute difference that can be obtained among all 
possible subsets formed this way.
7. This is an exponential-time brute-force approach since every stone leads to 
two recursive calls, resulting in O(2^n) time.
8. No memoization is used, so redundant subproblems are recalculated, which 
limits the efficiency for larger inputs.
*/
