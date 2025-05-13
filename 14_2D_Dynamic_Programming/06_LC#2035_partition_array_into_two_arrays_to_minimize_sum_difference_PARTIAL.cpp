/* LC#2035. Partition Array Into Two Arrays to Minimize Sum Difference

All codes are correct but they get TLE (even DP) since the problem is set to be solve using divide and conquer only 
(meet in the middle approach) - SKIPPED

Here's how it works:
A.  Divide: 
    Split the array into two roughly equal halves (first n/2 elements and last n/2 elements)
B   Conquer:
    For each half, generate all possible subset sums and their corresponding subset sizes
    This gives you 2^(n/2) combinations for each half, which is much more manageable than 2^n
C.  Combine:
    For each subset sum and size from the first half, find the best matching subset from the second half
    The optimal pairing will give you the minimum difference
*/

// Rec without memo
// No need to maintain path1 and path2 vectors, their size itself are suff
// Gets TLE 134/201

class Solution {
    int rec(int i, vector<int> &nums, int sumDiff, int firstHalfSize) {
        const int n = nums.size();
        if(i == n) {
            return (firstHalfSize == n/2 && (n - firstHalfSize) == n/2) ? abs(sumDiff) : INT_MAX;
        }
        int left = rec(i+1, nums, sumDiff + nums[i], firstHalfSize + 1);
        int right = rec(i+1, nums, sumDiff - nums[i], firstHalfSize);
        return min(left, right);
    }
public:
    int minimumDifference(vector<int>& nums) {
        return rec(0, nums, 0, 0);
    }
};

// Rec without memo
// Gets TLE 134/201

class Solution {
    int rec(int i, vector<int> &nums, int sumDiff, vector<int> &path1, vector<int> &path2) {
        const int n = nums.size();
        if(i == n) {
            return (path1.size() == n/2 && path2.size() == n/2) ? abs(sumDiff) : INT_MAX;
        }
        path1.push_back(nums[i]);
        int left = rec(i+1, nums, sumDiff + nums[i], path1, path2);
        path1.pop_back();
        path2.push_back(nums[i]);
        int right = rec(i+1, nums, sumDiff - nums[i], path1, path2);
        path2.pop_back();
        return min(left, right);
    }
public:
    int minimumDifference(vector<int>& nums) {
        vector<int> path1, path2;
        return rec(0, nums, 0, path1, path2);
    }
};


// All codes below are rec with memo

// Rec with memo | 2D DP unordered_map
// Gets TLE 134/201

class Solution {
    int rec(int i, vector<int> &nums, int sumDiff, vector<int> &path1, vector<int> &path2, unordered_map<int, unordered_map<int, int>> &dp) {
        const int n = nums.size();
        if(i == n) {
            return (path1.size() == n/2 && path2.size() == n/2) ? abs(sumDiff) : INT_MAX;
        }
        if(dp[i].count(sumDiff)) return dp[i][sumDiff];
        path1.push_back(nums[i]);
        int left = rec(i+1, nums, sumDiff + nums[i], path1, path2, dp);
        path1.pop_back();
        path2.push_back(nums[i]);
        int right = rec(i+1, nums, sumDiff - nums[i], path1, path2, dp);
        path2.pop_back();
        return dp[i][sumDiff] = min(left, right);
    }
public:
    int minimumDifference(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        unordered_map<int, unordered_map<int, int>> dp;
        vector<int> path1, path2;
        return rec(0, nums, 0, path1, path2, dp);
    }
};

// Rec with memo | Psuedo 3D DP unordered_map
// Gets TLE 121/201 => This tells that unordered_map<string, int> is faster than unordered_map<int, unordered_map<int, unordered_map<int, int>>> dp;

class Solution {
    int rec(int i, vector<int> &nums, int sumDiff, int firstHalfSize, unordered_map<string, int> &dp) {
        const int n = nums.size();
        if(i == n) {
            return (firstHalfSize == n/2 && (n - firstHalfSize) == n/2) ? abs(sumDiff) : INT_MAX;
        }
        string key = to_string(i) + '#' + to_string(sumDiff) + '#' + to_string(firstHalfSize);
        if(dp.count(key)) return dp[key];
        int left = rec(i+1, nums, sumDiff + nums[i], firstHalfSize + 1, dp);
        int right = rec(i+1, nums, sumDiff - nums[i], firstHalfSize, dp);
        return dp[key] = min(left, right);
    }
public:
    int minimumDifference(vector<int>& nums) {
        unordered_map<string, int> dp;
        return rec(0, nums, 0, 0, dp);
    }
};

// Rec with memo | 3D DP unordered_map
// Gets TLE 116/201

class Solution {
    int rec(int i, vector<int> &nums, int sumDiff, int firstHalfSize, unordered_map<int, unordered_map<int, unordered_map<int, int>>> &dp) {
        const int n = nums.size();
        if(i == n) {
            return (firstHalfSize == n/2 && (n - firstHalfSize) == n/2) ? abs(sumDiff) : INT_MAX;
        }
        if(dp[i][sumDiff].count(firstHalfSize)) return dp[i][sumDiff][firstHalfSize];
        int left = rec(i+1, nums, sumDiff + nums[i], firstHalfSize + 1, dp);
        int right = rec(i+1, nums, sumDiff - nums[i], firstHalfSize, dp);
        return dp[i][sumDiff][firstHalfSize] = min(left, right);
    }
public:
    int minimumDifference(vector<int>& nums) {
        unordered_map<int, unordered_map<int, unordered_map<int, int>>> dp;
        return rec(0, nums, 0, 0, dp);
    }
};

