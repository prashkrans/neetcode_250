/* LC#2958. Length of Longest Subarray With at Most K Frequency
*/

/*
### Approach 1: Sliding Window with Frequency Constraint
1. Use two pointers to maintain a dynamic window representing the current subarray.
2. Maintain a frequency map to track occurrences of each number inside the window.
3. Expand the right pointer while element frequency remains less than or equal to k.
4. Update the answer whenever a valid window configuration is achieved.
5. If frequency exceeds k, shrink window by moving left pointer and updating counts.
6. This approach ensures each element enters and leaves the window at most once.
7. Sliding window guarantees linear time complexity with controlled frequency tracking.
*/

// 1. Sliding Window with Frequency Constraint (My original solution)
// Time Complexity: O(n) | 78ms beats 21%
// Space Complexity: O(n)
// where n = nums.size();

class Solution {                                                                           
public:                                                                                    
    int maxSubarrayLength(vector<int>& nums, int k) {                                     // Finds longest valid subarray
        int l = 0, r = 0, n = nums.size(), ans = 0;                                       // Sliding window pointers and answer
        unordered_map<int, int> freq;                                                     // Frequency map for elements
        while(r < n) {                                                                    // Expand window using right pointer
            freq[nums[r]]++;                                                              // Include current element in window
            if(freq[nums[r]] <= k) {                                                      // Check frequency constraint
                ans = max(ans, r - l + 1);                                                // Update maximum valid length
                r++;                                                                      // Move right pointer forward
            }
            else {                                                                        // Frequency constraint violated
                freq[nums[r]]--;                                                          // Revert addition of current element
                freq[nums[l]]--;                                                          // Remove left element from window
                l++;                                                                      // Shrink window from left
            }
        }
        return ans;                                                                       // Return maximum subarray length
    }
};
