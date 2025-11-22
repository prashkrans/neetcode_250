/* LC#201. Bitwise AND of Numbers Range

Approach: 
To get the result, you need to find the common prefix [#IMP] of left and right in their binary representation. 

Example 1:
Input: left = 5, right = 7
Output: 4
0000 0000 0000 0000 0000 0000 0000 0101 (5)
0000 0000 0000 0000 0000 0000 0000 0111 (7)
prefix = 0000 0000 0000 0000 0000 0000 0000 0100 (4)

### Approach: Common Bit Prefix Detection
1. The goal is to compute the result of applying bitwise AND to all integers
from `left` to `right`.
2. Any differing bit between `left` and `right` at a certain position implies
a toggle in that bit within the range.
3. We traverse from the most significant bit (31st) down to the least significant
bit (0th) to detect common prefix bits.
4. If the current bit in `left` and `right` is the same and set to 1, we
include it in the result.
5. The first position where the bits differ marks the start of variation
in the range, so we break the loop.
6. All bits beyond the first mismatch can flip due to the inclusive range,
and must be set to 0 in the result.
7. This results in the final answer only containing the common prefix bits
between `left` and `right`, which are preserved.
*/

// Common Bit Prefix Detection (Prefer this method over 2)
// time complexity: O(26) ~ O(1)                                        // Fixed 32-bit loop independent of input size
// space complexity: O(1)                                               // Constant space used for a few integer variables

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int ans = 0;                                                    // Store the result of bitwise AND in range
        for(int i=31; i>=0; i--) {                                      // Traverse from the highest to lowest bit
            int currLeftBit = left & (1 << i);                          // Extract bit at position i from left
            int currRightBit = right & (1 << i);                        // Extract bit at position i from right
            if(currLeftBit != currRightBit) break;                      // Break if bits differ — they will toggle in range
            if(currLeftBit) ans += (1 << i);                            // If both bits are 1, include in result
        }        
        return ans;                                                     // Return the AND result of the full range
    }
};

// or, same as above but without comments

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int ans = 0;
        for(int i=31; i>=0; i--) {
            int currLeftBit = left & (1 << i);
            int currRightBit = right & (1 << i);
            if(currLeftBit != currRightBit) break;
            if(currLeftBit) ans += (1 << i);
        }        
        return ans;
    }
};


/*
### Approach 2: Bit Shift to Find Common Prefix
1. To find the bitwise AND of numbers in the range [left, right], observe
that changing bits make AND zero.
2. The key insight is that only the common left-side bit prefix remains
unchanged throughout the range.
3. We repeatedly shift both `left` and `right` to the right until they become
equal, removing differing least significant bits.
4. Each right shift discards a differing bit position that will result in
zero in final AND due to toggle.
5. The number of shifts is recorded so we can restore the bits to their
original positions by left shifting later.
6. Once both values are equal, they share a common prefix that does not
change across the range.
7. Finally, left shifting that value back by the shift count restores the
common bits in correct position.
*/

// 2. Bit Shift to Find Common Prefix
// Time complexity: O(log(right - left))                             // Number of right shifts until left equals right
// Space complexity: O(1)                                            // Constant space for shift counter and modified inputs

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int shift = 0;                                               // Counter for how many bits we shift

        while (left < right) {                                       // Continue while left and right differ
            left >>= 1;                                              // Right shift left by 1 to discard differing LSB
            right >>= 1;                                             // Right shift right by 1 to match prefix
            shift++;                                                 // Increment shift count
        }

        return left << shift;                                        // Left shift back to restore common prefix position
    }
};
