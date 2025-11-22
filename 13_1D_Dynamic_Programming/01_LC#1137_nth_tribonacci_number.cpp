/* LC#1137. N-th Tribonacci Number

The Tribonacci sequence Tn is defined as follows: 
T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.
Given n, return the value of Tn.
*/

// 1. Bottom up DP with optimized space

// Time Complexity: O(n)
// - The loop runs from 3 to n, resulting in O(n) iterations.

// Space Complexity: O(1)
// - The solution uses a constant amount of space for variables `n0`, `n1`, `n2`, and `ans`.

class Solution {
public:
    int tribonacci(int n) {
        if(n == 0) return 0;                           // Base case: T(0) = 0
        if(n == 1 || n == 2) return 1;                 // Base cases: T(1) = T(2) = 1
        int n0 = 0, n1 = 1, n2 = 1;                    // Initialize the first three tribonacci numbers
        int ans = 0;                                   // Variable to store the current tribonacci number
        for(int i = 3; i <= n; i++) {                  // Iterate from 3 to n
            ans = n0 + n1 + n2;                        // Calculate the current tribonacci number
            n0 = n1;                                   // Update n0 to the previous n1
            n1 = n2;                                   // Update n1 to the previous n2
            n2 = ans;                                  // Update n2 to the current tribonacci number
        }
        return ans;                                    // Return the nth tribonacci number
    }
};

// or, same as above but without comments

class Solution {
public:
    int tribonacci(int n) {
        if(n == 0) return 0;
        if(n == 1 || n == 2) return 1;
        int n0 = 0, n1 = 1, n2 = 1;
        int ans = 0;
        for(int i=3; i<=n; i++) {
            ans = n0 + n1 + n2;
            n0 = n1;
            n1 = n2;
            n2 = ans;
        }
        return ans;
    }
};