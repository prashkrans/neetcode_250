/* LC#560. Subarray Sum Equals K

1. Brute force: O(n^2)
2. Hashmap: O(n)
*/

/*
### Approach: Prefix Sum with Hash Map Counting
1. Use prefix sum technique to track cumulative sum while iterating through the array elements.
2. Maintain a hash map storing frequency of each prefix sum encountered so far.
3. Initialize hash map with zero sum frequency one to count subarrays starting at index zero. [#IMP]
4. For each element, compute current prefix sum and calculate difference with target k.
5. If this difference exists in hash map, it means a subarray ending at current index sums to k.
6. Add frequency of the difference to the answer to count all such subarrays.
7. Update hash map with current prefix sum for future subarray calculations.
*/

// 2. Using a hashmap and prefixSum (currSum) | Tricky but important
// Time Complexity: O(n)
// Space Complexity: O(n)
// where n = nums.size();

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {                     // function to count subarrays with sum k
        int ans = 0, currSum = 0;                                   // stores result and running prefix sum
        unordered_map<int, int> mp;                                 // hashmap to store prefix sum frequencies
        mp[0] = 1;                                                  // handle subarrays starting from index zero
        for(int i = 0; i < nums.size(); i++) {                      // iterate through array elements
            currSum += nums[i];                                     // update prefix sum
            int diff = currSum - k;                                 // required previous prefix sum
            ans += mp[diff];                                        // add count of valid subarrays
            mp[currSum]++;                                          // increment frequency of current prefix sum
        }
        return ans;                                                 // return total count of subarrays
    }
};
