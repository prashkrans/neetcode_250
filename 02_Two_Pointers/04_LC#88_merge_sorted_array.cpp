/* LC#88. Merge Sorted Array

Multiple ways:
1. Merging them then sorting: O((m + n)log(m + n))
2. Using two pointers: O(m + n)
3. Using three pointers (With or without O(n) extra space): O(m + n)

### Approach 2: Two Pointer Merge Using Temporary Array
1. Use two pointers to traverse both sorted arrays starting from their first valid elements.
2. Compare current elements of both arrays and append the smaller one into temporary array.
3. Increment pointer corresponding to the chosen element after each comparison.
4. Continue merging until one of the arrays is completely traversed.
5. Append remaining elements from the unfinished array into temporary array.
6. Copy all elements from temporary array back into the first array to maintain sorted order.
7. This method preserves sorting by sequential comparison and merging.
*/

// 2. Two Pointer Merge Using Temporary Array (My original solution | 10 minutes)
// Time Complexity: O(m + n) | 0ms, beats 100%
// Space Complexity: O(m + n)

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {      // function to merge two sorted arrays
        vector<int> temp;                                                   // temporary array to store merged result
        int i = 0, j = 0;                                                   // pointers for nums1 and nums2
        while(i < m && j < n) {                                             // traverse both arrays
            if(nums1[i] <= nums2[j]) {
                temp.push_back(nums1[i++]);                                 // push smaller element from nums1
            } else {
                temp.push_back(nums2[j++]);                                 // push smaller element from nums2
            }
        }
        while(i < m) temp.push_back(nums1[i++]);                            // append remaining nums1 elements
        while(j < n) temp.push_back(nums2[j++]);                            // append remaining nums2 elements
        for(int k = 0; k < m + n; k++) nums1[k] = temp[k];                  // copy merged result back to nums1
    }
};
