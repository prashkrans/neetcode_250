/* LC#69. Sqrt(x)
1. Linear search 1 to sqrt(x) | O(sqrt(n))
2. Binary search | O(log2n) (Best method)
3. Newton's Method | O(log2n)
4. Recursion and bit shifting | O(log2n) 
*/

// 2a. Binary Search (My original solution but took a hint)
// O(log2n)
// O(1)
// long long is important here 

class Solution {
public:
    int mySqrt(int x) {
        int l = 0, r = x, mid;
        while(l <= r) {
            mid = l + (r - l) / 2;
            if ((long long) mid * mid == x) break;
            else if((long long) mid * mid < x) l = mid + 1;
            else r = mid - 1;
        }
        return ((long long) mid * mid == x) ? mid : l - 1;
    }
};

// 2b. Binary search
// O(log2n)
// O(1)
// long long is important here 

class Solution {
public:
    int mySqrt(int x) {
        int l = 0, r = x, res = 0;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if ((long long) m * m > x) {
                r = m - 1;
            } else if ((long long) m * m < x) {
                l = m + 1;
                res = m; // [#IMP - floor value is required]
            } else {
                return m;
            }
        }
        return res;
    }
};