/* LC#168. Excel Sheet Column Title

### Approach: Base-26 Conversion with Offset
1. The problem is a variation of converting a decimal number to base-26,
but with an offset: the Excel column system starts from 1 not 0. [#IMP]
2. [#IMP] Before each loop, we decrement the column number to convert it to a
0-indexed system. This allows clean mapping of 0 → A, 25 → Z.
3. The remainder of the column number divided by 26 gives the current
rightmost character of the title.
4. The character is obtained by adding the remainder to ASCII value of
'A', which gives characters A–Z correctly.
5. The character is prepended to the resulting string because the least
significant digit comes last in Excel notation.
6. The column number is divided by 26 after each character is extracted,
which reduces the number for the next digit conversion.
7. This continues until the column number becomes zero, building the
correct Excel title from least to most significant character.
*/


// Time Complexity: O(log₍₂₆₎N)                                     // Each division by 26 reduces problem size ⇒ logarithmic steps
// Space Complexity: O(log₍₂₆₎N)                                    // Result string can grow up to log₍₂₆₎N length

class Solution {
public:
    string convertToTitle(int columnNumber) {
        string s;                                                   // Initialize empty string to build column title
        while(columnNumber--) {                                     // Adjust to 0-indexed by decrementing before loop
            int rem = columnNumber % 26;                            // Compute remainder to map to A-Z (0–25)
            char ch = rem + 'A';                                    // Convert 0–25 to ASCII A–Z
            s = ch + s;                                             // Prepend character to result string
            columnNumber /= 26;                                     // Reduce columnNumber by factor of 26
        }
        return s;                                                   // Return the resulting Excel-style column title
    }
};

// or, same as above but without comments

class Solution {
public:
    string convertToTitle(int columnNumber) {
        string s;
        while(columnNumber--) {
            int rem = columnNumber % 26;
            char ch = rem + 'A';
            s = ch + s;
            columnNumber /= 26;
        }
        return s;
    }
};

/*
Note: This is an incorrect code:

class Solution {
public:
    string convertToTitle(int columnNumber) {
        string s;
        while(columnNumber) {
            int rem = (columnNumber % 26) - 1;          // Incorrect
            char ch = rem + 'A';
            s = ch + s;
            columnNumber /= 26;
        }
        return s;
    }
};
*/