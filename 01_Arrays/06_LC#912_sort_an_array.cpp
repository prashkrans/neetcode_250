/* LC#912. Sort an Array
1. O(n^2) sorting algos
2. O(nlogn) sorting algos (a. Merge Sort b. Quick Sort, etc.)
*/

/*
### Approach: Divide and Conquer Using Merge Sort
1. Apply divide and conquer strategy by recursively splitting the array into two halves until single element subarrays remain.
2. Each recursive call divides the array using midpoint calculation based on start and end indices.
3. Single element subarrays are already sorted and serve as base cases for recursion.
4. Merge two sorted subarrays by comparing elements from both halves and storing them in temporary array.
5. Remaining elements from either half are appended once one subarray is exhausted.
6. Copy merged result back into original array segment to maintain sorted order.
7. Recursively merging sorted halves produces fully sorted array with guaranteed logarithmic depth.
*/


// 1. MergeSort (Easier than quicksort, and passess 100% but takes O(n) space instead of O(1)) - Prefer this
// Time Complexity: O(nlog2n)
// Space Complexity: O(n)
// where n = nums.size()

class Solution {
    void merge(vector<int> &arr, int start, int mid, int end) {         // merge two sorted subarrays
        int i = start, n = mid + 1, j = mid + 1, m = end + 1;           // define boundaries for both halves
        vector<int> temp;                                               // temporary array for merged result
        while(i < n && j < m) {                                         // merge elements from both halves
            if(arr[i] <= arr[j]) temp.push_back(arr[i++]);              // take smaller element from left
            else temp.push_back(arr[j++]);                              // take smaller element from right
        }
        while(i < n) temp.push_back(arr[i++]);                          // append remaining left elements
        while(j < m) temp.push_back(arr[j++]);                          // append remaining right elements
        for(int k = 0; k < temp.size(); k++) arr[start + k] = temp[k];  // copy merged result back to array
    }

    void mergeSort(vector<int> &arr, int start, int end) {              // recursive merge sort function
        if(start >= end) return;                                        // base case for single element
        int mid = (start + end) / 2;                                    // calculate middle index
        mergeSort(arr, start, mid);                                     // sort left half recursively
        mergeSort(arr, mid + 1, end);                                   // sort right half recursively
        merge(arr, start, mid, end);                                    // merge sorted halves
    }
public:
    vector<int> sortArray(vector<int>& nums) {                          // function to sort entire array
        mergeSort(nums, 0, nums.size() - 1);                            // apply merge sort algorithm
        return nums;                                                    // return sorted array
    }
};


// 2a. QuickSort (Three types only one is accepted while both first and second gets TLE) | TODO
// TODO

// 2c. QuickSort (Previously accepted solution but getting TLE now) | Same as 2b. but compact.

class Solution {
    int partition(vector<int> &nums, int s, int e) {
        int p_idx = s;
        int pivot = nums[e];
        for(int i = s; i < e; i++) {
            if(nums[i] < pivot) {
                swap(nums[p_idx], nums[i]);
                p_idx++;
            }
        }
        swap(nums[p_idx], nums[e]);
        return p_idx;
    }

    void quickSort(vector<int> &nums, int s, int e) {
       if(s >= e) return;
       int x = partition(nums, s, e);
       quickSort(nums, s, x - 1);
       quickSort(nums, x + 1, e);       // or, quickSort(nums, x, e); but it takes slightly more time
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
};

// 2c. QuickSort (My original solution) - This code is absolutely correct but slightly longer (But, avoid this)
// Time Complexity: O(nlog2n) | Gets TLE, passes 19/21 
// Space Complexity: O(1) as we modify the given array itself
// My previous accepted submission itself is getting TLE, passes 19/21 and this is a slightly modified version of that.


class Solution {
    int partition(vector<int> &nums, int s, int e) {
        int count = 0;
        int pivot = nums[s];
        for(int i = s; i <= e; i++) {
            if(nums[i] < pivot) count++;
        }
        swap(nums[s], nums[s + count]);
        int l = s, r = e;
        while(l < s + count && r > s + count) {
            if(nums[r] < nums[s + count]) swap(nums[l++], nums[r]);
            else r--;
        }
        return s + count;
    }

    void quickSort(vector<int> &nums, int s, int e) {
       if(s >= e) return;
       int x = partition(nums, s, e);
       quickSort(nums, s, x - 1);
       quickSort(nums, x + 1, e);   // but quickSort(nums, x, e) fails here
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
};