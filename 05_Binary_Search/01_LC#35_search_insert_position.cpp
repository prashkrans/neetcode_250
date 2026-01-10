/* LC#35. Search Insert Position
*/

/*
### Approach: Binary Search for Insert Position
1. Handle boundary cases where target is smaller than first element or larger than last element.
2. Apply binary search on the sorted array to efficiently locate the target or its correct insertion index.
3. Maintain two pointers representing current search range and narrow the range based on comparisons.
4. If target equals the middle element, return its index immediately.
5. Otherwise, adjust search boundaries until left and right pointers converge.
6. The final left pointer represents the correct insertion position for the target.
*/

// 1a. Binary Search (My original solution)
// Time Complexity: O(log n) | 0ms, beats 100%
// Space Complexity: O(1)
// where n = nums.size();

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {               // function to find insert position
        if(target < nums[0]) return 0;                              // insert at beginning if smaller
        if(target > nums.back()) return nums.size();                // insert at end if larger
        int l = 0, r = nums.size() - 1;                             // initialize binary search bounds
        while(l < r) {                                              // continue until bounds converge
            int mid = l + (r - l) / 2;                              // compute middle index safely
            if(target == nums[mid]) return mid;                     // exact match found
            else if(target < nums[mid]) r = mid;                    // search left half
            else l = mid + 1;                                       // search right half
        }
        return l;                                                   // return insertion position
    }
};

// 1b. Compact Binary Search with l <= r, r = mid - 1 and l = mid + 1 (Prefer this)
// Time Complexity: O(log n) | 0ms, beats 100%
// Space Complexity: O(1)
// where n = nums.size();

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(target == nums[mid]) return mid;
            else if(target < nums[mid]) r = mid - 1;
            else l = mid + 1;         
        }
        return l; 
    }
};