/* LC#209. Minimum Size Subarray Sum 
*/

// 1. Brute Force Solution
// O(n^2) | Gets TLE, 18/21 test cases passed 
// O(1)
// where n = nums.size()

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int minSize = INT_MAX;
        for(int i = 0; i < nums.size(); i++) {
            int sum = 0;
            for(int j = i; j < nums.size(); j++) {
                sum += nums[j];
                if(sum >= target) {
                    minSize = min(minSize, j - i + 1);
                    break;
                }
            }
        }
        return (minSize == INT_MAX) ? 0 : minSize;           
    }
};

// 2. Sliding Window Approach (My original solution, 30 min)
// O(n) | 0ms, beats 100%
// O(1)
// where n = nums.size();


class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int minSize = INT_MAX;
        int l = 0, r = 0, sum = nums[l];        // l varies from 0 to r while r varies from l to n - 1
        while(l <= r && r < nums.size()) {      // Note: <= instead of < as a single element could also be >= target
            if(sum < target) {
                r++;
                if(r < nums.size()) sum += nums[r];
            } else {
                minSize = min(minSize, r - l + 1);
                sum -= nums[l++];               // Note: First decrease nums[l] from sum then increase l
            }
        }
        return minSize == INT_MAX ? 0 : minSize;
    }
};

// Same as above but with print statements
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int minSize = INT_MAX;
        int l = 0, r = 0, sum = nums[l];
        while(l <= r && r < nums.size()) {      // Note: <= instead of < as a single element could also be >= target
            if(sum < target) {
                r++;
                if(r < nums.size()) sum += nums[r];
                // cout<<"r = "<<r<<endl;
            } else {
                minSize = min(minSize, r - l + 1);
                sum -= nums[l++];               // Note: First decrease nums[l] from sum then increase l
                // cout<<"l = "<<l<<endl;
            }
            // cout<<"sum = "<<sum<<endl;
        }
        return minSize == INT_MAX ? 0 : minSize;
    }
};

// 2b. Sliding window but with nested for and while loops

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int l = 0, total = 0, res = INT_MAX;

        for (int r = 0; r < nums.size(); r++) {
            total += nums[r];
            while (total >= target) {
                res = min(r - l + 1, res);
                total -= nums[l];
                l++;
            }
        }

        return res == INT_MAX ? 0 : res;
    }
};

// 3. Prefix Sum + Binary Search (Not optimal but a follow up question)
// O(nlogn)
// O(n)