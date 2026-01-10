/* 75. Sort Colors

Multiple ways to solve:
1. Brute force i.e. sort the array: O(nlogn)
2. Counting Sort: O(n)
3. Three pointers (2-3 variations) | TODO - Follow up: Could you come up with a one-pass algorithm using only constant extra space?
*/

/*
### Approach 2: Counting Sort for Three Distinct Values
1. Use counting technique since array contains only three distinct values zero, one, and two.
2. Create a frequency array of fixed size three to store count of each color.
3. Traverse the input array once and increment the corresponding count for each element.
4. Overwrite the original array by placing zeros, then ones, and finally twos based on counts.
5. Maintain an index pointer to track current write position in the array.
6. This method avoids comparisons and swapping, ensuring linear time complexity.
7. Fixed size frequency array guarantees constant extra space usage.
*/


// 2a. Counting sort (Compact version of 2b - This is too easy to be a medium problem hence refer method 3)
// Time Complexity: O(2n) ~ O(n) (Two pass)
// Space Complexity: O(3) ~ O(1) 
// where n = nums.size()

class Solution {
public:
    void sortColors(vector<int>& nums) {                          // function to sort colors
        vector<int> count(3, 0);                                  // frequency array for values 0, 1, and 2
        for(int i = 0; i < nums.size(); i++) count[nums[i]]++;    // count occurrences of each color
        int i = 0;                                                // index for overwriting nums
        for(int j = 0; j < 3; j++) {                              // iterate through each color
            while(count[j]--) nums[i++] = j;                      // place color j count times
        }
    }
};


// 2b. Counting sort (Same as 2a but longer | My original solution) - Ignore this

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int count0 = 0, count1 = 0, count2 = 0;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] == 0) count0++;
            else if(nums[i] == 1) count1++;
            else count2++;
        }
        for(int i = 0; i < nums.size(); i++) {
            if(count0-- > 0) {
                nums[i] = 0;
                continue;
            }
            if(count1-- > 0) {
                nums[i] = 1;
                continue;
            }
            if(count2-- > 0) {
                nums[i] = 2;
                continue;
            }
        }
    }
};

/*
### Approach 3: Dutch National Flag Three Pointer Technique (Prefer this)
1. Use three pointers named low, mid, and high to divide the array into three regions.
2. Left region contains zeros, middle region contains ones, and right region contains twos.
3. Traverse array using mid pointer until it crosses the high pointer. [#IMP]
4. If current element is zero, swap it with low pointer element and increment both.
5. If current element is one, simply move mid pointer forward.
6. If current element is two, swap it with high pointer element and decrement high.
7. This single pass rearranges array in-place using constant extra space.
*/


// 3. Three pointers (l, m, h) | Tricky but easy
// Time Complexity: O(n) | Single pass only
// Space Complexity: O(1) 

class Solution {
public:
    void sortColors(vector<int>& nums) {                                // function to sort colors in-place
        int n = nums.size(), low = 0, mid = 0, high = n-1;              // initialize three pointers, and note that mid starts from 0 
        while(mid <= high) {                                            // process elements until pointers cross
            if(nums[mid] == 0) swap(nums[low++], nums[mid++]);          // move zero to left partition
            else if(nums[mid] == 1) mid++;                              // keep one in middle partition
            else if(nums[mid] == 2) swap(nums[mid], nums[high--]);      // move two to right partition
        }
    }
};
