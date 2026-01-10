/* LC#374. Guess Number Higher or Lower
Three ways:
1. Linear search O(n)
2. Binary search O(log2n)
3. Ternary search O(log3n)
*/

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

// 2. Binary Search
// O(log2n) | 0ms, beats 100%
// O(1) 

class Solution {
public:
    int guessNumber(int n) {
        int l = 1, r = n, mid = 0;
        while(l <= r) {
            mid = l + (r - l) / 2; // Using mid = (l + r) / 2 gives integer overflow here
            if(guess(mid) == 0) break;
            else if(guess(mid) == -1) r = mid - 1;
            else l = mid + 1;
        }
        return mid;
    }
};