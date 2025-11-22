/* LC#67. Add Binary

### Approach: Binary Addition with Carry Simulation
1. We perform binary addition similar to how we do decimal addition, starting
from the least significant digit (rightmost).
2. Initialize a result string and a carry value, then iterate from the end
of both input strings.
3. For each step, add the digit from `a`, `b`, and the `carry` if they
exist, converting characters to integers.
4. Compute the binary result for that position using modulo 2, and compute
carry using integer division by 2.
5. Append the resulting bit (converted back to a character) to the result
string.
6. Continue the loop until all digits and any remaining carry are processed,
ensuring complete binary sum computation.
7. Finally, reverse the result string to convert it from LSB-to-MSB order
to the correct MSB-to-LSB order.
*/

// 1. Using || condition in the while loop and using % 2 and / 2 makes the code much more compact
// Time complexity: O(max(n, m))                                    // Loop runs until both strings and carry are exhausted
// Space complexity: O(max(n, m))                                   // Result string stores at most max(n, m) + 1 characters

class Solution {
public:
    string addBinary(string a, string b) {
        string c;                                                   // Result string to store binary sum
        int carry = 0;                                              // Variable to hold carry during addition
        int i = a.size() - 1, j = b.size() - 1;                     // [#IMP] Pointers to traverse a and b from the end
        while(i>=0 || j>=0 || carry) {                              // Loop until all bits and carry are processed
            int cVal = 0;                                           // Holds sum of current bits and carry
            if(i >= 0) cVal += a[i--] - '0';                        // Add bit from a if available
            if(j >= 0) cVal += b[j--] - '0';                        // Add bit from b if available
            if(carry) cVal += carry;                                // Add carry if it exists
            int rem = cVal % 2;                                     // Current bit after modulo
            carry = cVal / 2;                                       // Update carry for next iteration
            c += rem + '0';                                         // Append bit (as character) to result
        }
        reverse(c.begin(), c.end());                                // Reverse the result string to get correct order
        return c;                                                   // Return final binary sum
    }
};

// or, same as above but without comments

class Solution {
public:
    string addBinary(string a, string b) {
        string c;
        int carry = 0;
        int i = a.size() - 1, j = b.size() - 1;
        while(i>=0 || j>=0 || carry) {
            int cVal = 0;
            if(i >= 0) cVal += a[i--] - '0';
            if(j >= 0) cVal += b[j--] - '0';
            if(carry) cVal += carry;
            int rem = cVal % 2;
            carry = cVal / 2;
            c += rem + '0';
        }
        reverse(c.begin(), c.end());
        return c;
    }
};

// incomplete code
// using || condition in the while loop and using % 2 and / 2 makes the code much more compact

class Solution {
public:
    string addBinary(string a, string b) {
        int carry = 0;
        string c;
        int n = a.size(), m = b.size();
        while(n-- && m--) {
            if(a[n] == '1' && b[m] == '1') {
                if(carry == 0) s += '0';
                else s += '1';
                carry = 1;
            }
            else if(a[n] == '0' && b[m] == '0') {
                if(carry == 0) s += '0';
                else s += '1';
                carry = 0;
            }
            else {
                if(carry == 0) {
                    s += '1';
                    carry = 0;
                }
                else {
                    s += '0';
                    carry = 1;
                }
            }
        }
        if(n > 0) {
            
        }
        if(m > 0) {

        }

    }
};