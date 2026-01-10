/*219. Contains Duplicate II
*/


// O(n)
// O(n) due to unordered map
// where n = nums.size()

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for(int i = 0; i < nums.size(); i++) {
            if(mp.count(nums[i]) && abs(mp[nums[i]] - i) <= k) return true;
            else mp[nums[i]] = i;
        }
        return false;
    }
};

// Same as above but compact

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for(int i = 0; i < nums.size(); i++) {
            if(mp.count(nums[i]) && (i - mp[nums[i]]) <= k) return true; // removed abs as mp[nums[i]] would always be smaller than i
            mp[nums[i]] = i;    // removed else condition as we return true above
        }
        return false;
    }
};