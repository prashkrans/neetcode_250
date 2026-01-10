/* LC#27. Remove Element
*/

// 1. Modify the values and sort it (My original solution)
// O(n) + O(nlogn) ~ O(nlogn) due to sorting | 0ms, beats 100%
// O(1) or O(n) depeding on quick sort or merge sort

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int count = 0;
        for(auto &i: nums) {
            if(i == val) {
                i = 51;                         // since, 0 <= nums[i] <= 50 
                count++;
            }
        }
        sort(nums.begin(), nums.end());
        return nums.size() - count;
    }
};

// same as above but different variable names
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0;
        int n = nums.size();
        for(int i=0; i<n; i++) {
            if(nums[i] == val) {
                nums[i] = 51;
                k++;
            }
        }
        sort(nums.begin(), nums.end());
        return n - k;
    }
};