/* LC#229. Majority Element II

Multiple methods:
1. Brute force
2. Hashmap
3. Sorting
4. Other special methods
*/


// 2. Using a hashmap (My original solution)
// O(n)
// O(n)
// where n = nums.size();

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;
        unordered_map<int, int> mp;
        for(int i = 0; i < nums.size(); i++) mp[nums[i]]++;
        for(auto i: mp) {
            if(i.second > n / 3) ans.push_back(i.first);
        }        
        return ans;
    }
};