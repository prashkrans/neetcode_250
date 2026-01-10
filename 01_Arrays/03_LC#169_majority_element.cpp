/* LC#169. Majority Element
1. Brute Force: O(n^2)
2. Hashmap: O(n)
3. Sorting: O(nlogn)
4. Bit manipulation: O(n)
plus 2 more methods
*/

/*
### Approach 2: Frequency Counting Using Hash Map
1. Use an unordered map to store frequency count of each element present in the input array.
2. Traverse the entire array once and increment count corresponding to each encountered element.
3. After counting, iterate through the hash map entries to identify the element with maximum frequency.
4. Track both the highest frequency value and the corresponding element during iteration.
5. Since majority element appears more than n divided by two times, it will have the maximum frequency.
6. Return the element with the highest count as the majority element.
*/


// 2. Hashmap (My original solution, 6min)
// Time Complexity: O(n) 
// Space Complexity: O(n)
// where n = nums.size()

class Solution {
public:
    int majorityElement(vector<int>& nums) {                        // function to find majority element
        unordered_map<int, int> mp;                                 // hashmap to count frequencies
        int n = nums.size();                                        // size of input array
        for(int i = 0; i < n; i++) {                                // iterate through array
            mp[nums[i]]++;                                          // increment frequency of element
        }
        int maxCount = 0, res;                                      // track maximum count and result
        for(auto i: mp) {                                           // iterate through hashmap entries
            if(i.second > maxCount) {                               // check for higher frequency
                maxCount = i.second;                                // update maximum count
                res = i.first;                                      // update majority element
            }
        }
        return res;                                                 // return majority element
    }
};
