/* LC#1863. Sum of All Subset XOR Totals

Two approaches:
1. Recursion with skip-take (A. Void type rec and B. Int type rec TODO):
   - Use a recursive function to explore all subsets of the input array.
   - For each subset, calculate the XOR sum and add it to the total.
   - This approach has exponential time complexity due to the nature of subsets.

2. Iterative bit manipulation:
   - Use bit manipulation to calculate the XOR sum of all subsets.
   - This approach is more efficient and has linear time complexity.
   - It leverages the properties of XOR and the number of subsets.

*/
// 1a1. Using void type skip-take recursion without subset vector (Prefer this method)
// Time Complexity: O(2^n) not (O(2^n * n)) | 0ms beats 100%
// Space Complexity: O(n) due to recursion stack

class Solution {
    void rec(int i, vector<int> &nums, int currXORSum, int &subsetXORSum) {
        if(i==nums.size()) {
            subsetXORSum += currXORSum;
            return;
        }
        rec(i+1, nums, currXORSum ^ nums[i], subsetXORSum);
        rec(i+1, nums, currXORSum, subsetXORSum);
    }
public:
    int subsetXORSum(vector<int>& nums) {
        int subsetXORSum = 0;
        rec(0, nums, 0, subsetXORSum);
        return subsetXORSum;
    }
};

// 1a2. Using void type skip-take recursion and subset vector
// Time Complexity: O(2^n * n) | 0ms beats 100%
// - There are 2^n subsets for an array of size n.
// - For each subset, calculating the XOR sum takes O(n) in the worst case.
// - Overall complexity is O(2^n * n).

// Space Complexity: O(n)
// - The recursion stack can go as deep as n, where n is the size of the input array.
// - Additional space is used for the `subset` vector, which can also grow up to size n.

class Solution {
    void rec(int i, vector<int> &nums, vector<int> &subset, int &subsetXORSum) {
        if(i == nums.size()) {                           // Base case: reached the end of the array
            int currXORSum = 0;                          // Calculate XOR sum of the current subset
            for(int j = 0; j < subset.size(); j++) {
                currXORSum ^= subset[j];
            }
            subsetXORSum += currXORSum;                  // Add the XOR sum to the total
            return;
        }
        subset.push_back(nums[i]);                       // Include the current element in the subset
        rec(i + 1, nums, subset, subsetXORSum);          // Recurse with the current element included
        subset.pop_back();                               // Backtrack: remove the current element
        rec(i + 1, nums, subset, subsetXORSum);          // Recurse without the current element
    }
public:
    int subsetXORSum(vector<int>& nums) {
        int subsetXORSum = 0;                            // Initialize the total XOR sum
        vector<int> subset;                              // Temporary vector to store the current subset
        rec(0, nums, subset, subsetXORSum);              // Start the recursion
        return subsetXORSum;                             // Return the total XOR sum
    }
};

/*
### Approach: Iterative Bit Manipulation
1. Use bit manipulation to iterate through all subsets of the input array.
2. For each subset:
   - Use a bitmask `mask` to represent the subset.
   - If the i-th bit of `mask` is set, include the i-th element of the array in the subset.
   - Calculate the XOR of all elements in the subset.
   - Add the XOR value to the total sum.
3. Return the total XOR sum of all subsets.

### Notes:
- This approach explicitly generates all subsets using bit manipulation.
- It is less efficient than optimized recursive methods but is straightforward to implement.
*/

// 2. Using iterative bit manipulation
// Time Complexity: O(2^n * n)
// - There are 2^n subsets for an array of size n.
// - For each subset, calculating the XOR sum takes O(n) in the worst case.
// - Overall complexity is O(2^n * n).

// Space Complexity: O(1)
// - No additional space is used apart from a few variables.

class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int n = nums.size();                             // Size of the input array
        int xorVal = 0;                                  // Temporary variable to store XOR of a subset
        int sum = 0;                                     // Total XOR sum of all subsets
        for(int mask = 0; mask < (1 << n); mask++) {     // Iterate through all possible subsets (2^n)
            xorVal = 0;                                  // Reset XOR value for the current subset
            for(int i = 0; i < n; i++) {                 // Iterate through all elements in the array
                if(mask & (1 << i)) {                    // Check if the i-th element is included in the subset
                    xorVal ^= nums[i];                   // Add the element to the XOR of the current subset
                }
            }
            sum += xorVal;                               // Add the XOR of the current subset to the total sum
        }
        return sum;                                      // Return the total XOR sum of all subsets
    }
};