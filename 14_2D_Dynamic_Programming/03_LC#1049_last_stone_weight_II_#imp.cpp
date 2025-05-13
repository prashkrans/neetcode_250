/* LC#1049. Last Stone Weight II
This problem uses DP and is totally different from LC#1046 Last Stone Weight which uses a max heap

Also, this code is the same as "partition a set into two subsets such that the difference of subset sums is minimum"
Refer: partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum
https://www.naukri.com/code360/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494?leftPanelTabValue=PROBLEM

**Prefer B over A here**

### Approach:
Say you have four stones a,b,c,d.
First you smash b against c, you get (b-c)
Now you smash (b-c) against a
You get a-(b-c) which is same as (a+c)-(b)
Now you smash d against (a+c)-b
You get d-((a+c)-b) which is same as (d+b)-(a+c).

Basically for the given stones we can create two sets [#IMP],the sum of second set of stones to be 
subtracted from sum of first one.
Ideally we want sum of each set to be sum(stones)/2 so that they cancel each other out.

So to solve the problem we try to select a set of stones such that their sum comes as close as possible 
to sum(stones)/2 from the lower side.

### Mathematical Logic:
This problem is actually a disguised partition problem - we're trying to find a way to assign "+" or "-" signs 
to numbers to minimize the resulting sum. Mathematically, we're trying to divide the stones into two groups 
A and B such that |sum(A) - sum(B)| is minimized.

This transforms into a dynamic programming problem, specifically a variant of the "subset sum" problem, where 
we're trying to find a subset that sums as close as possible to half the total sum.

*/

// A1. Rec without memo using sum1 and sum2 as the sums of set 1 and set 2
// O(2^n) as each element has two choices either to be in set1 or set2 | Gets TLE 78/90
// O(n) due to the recursion stack which goes deep atmost to the size of stones
// where n = stones.size()

class Solution {
    int rec(int i, vector<int> &stones, int sum1, int sum2) {
        if(i == stones.size()) return abs(sum1 - sum2);
        int left = rec(i+1, stones, sum1 + stones[i], sum2);
        int right = rec(i+1, stones, sum1, sum2 + stones[i]);
        return min(left, right);
    }
public:
    int lastStoneWeightII(vector<int>& stones) {
        return rec(0, stones, 0, 0);
    }
};

// A2. Rec with memo using sum1 and sum2 as the sums of set 1 and set 2
// O(sum^2) where sum is the total sum of stone weights and both sum1 and sum2 could be as large as sum
// O(sum^2) due to the 2D DP array
// where n = stones.size()

class Solution {
    int rec(int i, vector<int> &stones, int sum1, int sum2, vector<vector<int>> &dp) {
        if(i == stones.size()) return abs(sum1 - sum2);
        if(dp[sum1][sum2] != -1) return dp[sum1][sum2];
        int left = rec(i+1, stones, sum1 + stones[i], sum2, dp);
        int right = rec(i+1, stones, sum1, sum2 + stones[i], dp);
        return dp[sum1][sum2] = min(left, right);
    }
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        vector<vector<int>> dp(sum + 1, vector<int>(sum + 1, -1));
        return rec(0, stones, 0, 0, dp);
    }
};

// B1. Rec without memo using sumDiff instead of sum1 and sum2
// O(2^n) as each element has two choices either to be in set1 or set2 | Gets TLE 78/90
// O(n) due to the recursion stack whose depth is atmost n
// where n = stones.size()

class Solution {
    int rec(int i, vector<int> &stones, int sumDiff) {
        if(i == stones.size()) return abs(sumDiff);         // Base case: all stones processed, return abs difference [#IMP] abs(sumDiff)
        int left = rec(i+1, stones, sumDiff + stones[i]);   // Choose to add current stone to one subset
        int right = rec(i+1, stones, sumDiff - stones[i]);  // Choose to add current stone to the other subset
        return min(left, right);                            // Return the minimal difference from both choices
    }
public:
    int lastStoneWeightII(vector<int>& stones) {
        return rec(0, stones, 0);                           // Start recursion with 0 index and 0 initial difference
    }
};


// B2. Rec with memo using sumDiff instead of sum1 and sum2 (Prefer this solution)
// O(n*sum) where sum is the total sum of stone weights and sumDiff could be as large as sum
// O(n*sum) due to the 2D DP array
// where n = stones.size()

class Solution {
    int rec(int i, vector<int> &stones, int sumDiff, unordered_map<int, unordered_map<int, int>> &dp) {
        if(i == stones.size()) return abs(sumDiff);
        if(dp[i].count(sumDiff)) return dp[i][sumDiff];
        int left = rec(i+1, stones, sumDiff + stones[i], dp);
        int right = rec(i+1, stones, sumDiff - stones[i], dp);
        return dp[i][sumDiff] = min(left, right);
    }
public:
    int lastStoneWeightII(vector<int>& stones) {
        unordered_map<int, unordered_map<int, int>> dp;
        return rec(0, stones, 0, dp);
    }
};