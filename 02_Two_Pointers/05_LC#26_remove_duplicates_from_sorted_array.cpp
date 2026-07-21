/* LC#26. Remove Duplicates from Sorted Array
Multiple approaches:
1. Sorted Set i.e. set<int> st;
2. Temporary array based duplicate removal
3. Two pointers (Prefer this method)
*/

// 1. Using a sorted set
// Time Complexity: O(nlogn) | 2ms, beats 14.98%
// Space Complexity: O(k) ~ O(n) where k = no. of unique elements which is = n in the worst case
// where n = nums.size();

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        set<int> uniqueElements;
        for(int i = 0; i < nums.size(); i++) {
            uniqueElements.insert(nums[i]);
        }
        int count = uniqueElements.size();
        int i = 0;
        for(auto j: uniqueElements) {
            nums[i++] = j;
        }
        return count;
    }
};

/*
### Approach 2: Extra Array Based Duplicate Removal
1. Since array is sorted, duplicate elements always appear consecutively.
2. Track the current unique element while iterating through the array.
3. Store each newly encountered unique element inside a separate vector.
4. Skip elements equal to the previously stored unique value.
5. After traversal, the auxiliary vector contains only unique elements.
6. Copy these unique elements back into the original array from beginning.
7. Return the size of auxiliary vector as the count of unique elements.
*/

// 2. Extra Array Based Duplicate Removal (My original solution but this takes O(n) extra space)
// Time Complexity: O(2n) ~ O(n) | 0ms, beats 100%
// Space Complexity: O(n) due to the vector uniqueElements
// where n = nums.size();

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {                     // function to remove duplicates from sorted array
        int curr = nums[0];                                       // store current unique element
        vector<int> uniqueElements(1, curr);                      // store unique elements encountered
        for(int i = 0; i < nums.size(); i++) {                    // iterate through input array
            if(nums[i] != curr) {                                 // check for new unique element
                uniqueElements.push_back(nums[i]);                // add new unique element
                curr = nums[i];                                   // update current element
            }
        }
        int count = uniqueElements.size();                        // number of unique elements
        for(int i = 0; i < count; i++) {                          // overwrite original array
            nums[i] = uniqueElements[i];                          // copy unique elements back
        }
        return count;                                             // return count of unique elements
    }
};

/*
### Approach 3: Two Pointer In-Place Method (Prefer this method)
1. Since the array is sorted, duplicates appear consecutively.
2. Use two pointers:
   - l tracks the index of the last unique element.
   - r scans the array.
3. If nums[r] differs from nums[l], increment l and copy nums[r] to nums[l].
4. This overwrites duplicates in-place without using extra space.
5. Continue until r reaches the end.
6. The number of unique elements is l + 1.
*/


// 3. Using two pointers (Easy to understand and takes O(1) extra space (Prefer this method):
// Time Complexity: O(n) | 0ms, beats 100%
// Space Complexity: O(1)
// where n = nums.size();

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {           // remove duplicates in-place from sorted array
        int l = 0, r = 0;                               // l = position of last unique element
        while(r < nums.size()) {                        // iterate through the array
            if(nums[l] != nums[r]) {                    // found a new unique element
                nums[++l] = nums[r];                    // place it at next unique position
            }
            r++;                                        // move right pointer
        }
        return l + 1;                                   // number of unique elements
    }
};
