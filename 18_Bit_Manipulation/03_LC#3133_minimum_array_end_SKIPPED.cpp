/* LC#3133. Minimum Array End

### Approach 1. LeetCode Solutions (Not the most optimal)
1.  Initialize the Array: Start with num = x, since we want the array's bitwise AND result to be x.
2.  Construct Remaining Elements: For each subsequent element:
        a. Increment num by 1 to ensure it’s larger than the previous.
        b. Use the bitwise OR operation (num + 1) | x to keep the new num aligned with x.
        c. This ensures that even as num grows, all bits essential to maintain the AND as x are preserved.
3.  Return the Result: After the loop, num holds the minimum possible value for the last element, meeting both the AND 
    and strictly increasing requirements.
*/

class Solution {
public:
    long long minEnd(int n, int x) {
        long long num = x;

        for(int i = 1; i < n; i++) {
            num = (num + 1) | x;            
        }

        return num;
    }
};