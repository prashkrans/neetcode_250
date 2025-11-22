/* LC#1071. Greatest Common Divisor of Strings

### Approach 1: Prefix Iteration and Full String Matching (My custom code)
1. The approach iterates through all prefixes of str1 as potential
gcd candidates, using the substring function from index 0 to i.
2. For each prefix, it checks whether both str1 and str2 are
completely composed of repetitions of this prefix.
3. This is done using the helper function isGcd, which manually
matches the characters of the candidate gcd against the full string.
4. In isGcd, a nested loop compares each character of the candidate
against the full string, looping through the prefix repeatedly.
5. If all characters of s match the repeated pattern of gcd till the
end, it returns true, else false on any mismatch.
6. If both strings match the current prefix, we store it as the
current longest common divisor string found so far.
7. The process continues for all prefixes, and the longest valid
prefix is returned at the end.
*/

// 1: Prefix Iteration and Full String Matching (My custom code) - Left to Right
// Time Complexity: O((n + m) * n)                                      // where n = str1.size() and n = str2.size())
// Space Complexity: O(n)                                               // Maximum prefix string stored in memory is of length n

class Solution {
public:
    bool isGcd(string &gcd, string &s) {
        int i = 0;                                                      // Initialize index for full string
        while(i < s.size()) {                                           // Loop through entire string s
            int j = 0;                                                  // Initialize index for gcd string
            while(j < gcd.size()) {                                     // Loop through entire gcd string
                if(s[i] != gcd[j] || i == s.size()) return false;       // Check mismatch or boundary, return false
                i++;                                                    // Move to next character in s
                j++;                                                    // Move to next character in gcd
            }
        }
        return true;                                                    // Return true if s is entirely divisible by gcd
    }
    string gcdOfStrings(string str1, string str2) {
        string gcd;                                                     // Variable to store the longest common divisor string
        for(int i=0; i<str1.size(); i++) {                              // Iterate over all prefixes of str1
            string currGcd = str1.substr(0, i+1);                       // Take current prefix from index 0 to i
            if(isGcd(currGcd, str1) && isGcd(currGcd, str2))            // Check if current prefix divides both strings
                gcd = currGcd;                                          // Update gcd if both are divisible
        }
        return gcd;                                                     // Return the longest valid common divisor string
    }
};


// or, same as above but without comments and path pruning (right to left)

class Solution {
public:
    bool isGcd(string &gcd, string &s) {
        int i = 0;
        while(i < s.size()) {
            int j = 0;
            while(j < gcd.size()) {
                if(s[i] != gcd[j] || i == s.size()) return false;
                i++;
                j++;
            }
        }
        return true;
    }
    string gcdOfStrings(string str1, string str2) {
        for(int i=str1.size(); i>=0; i--) {
            string currGcd = str1.substr(0, i+1);
            if(isGcd(currGcd, str1) && isGcd(currGcd, str2)) return currGcd;
        }
        return "";
    }
};

/*
### Approach 2: Mathematical GCD and Pattern Verification (Prefer this method)
1. The key insight is that if two strings have a common divisor string,
then their lengths must be divisible by the length of that string.
2. We use the Euclidean Algorithm to compute the greatest common divisor
(GCD) of the lengths of the two strings.
3. The candidate answer is the prefix of str1 of length equal to this
GCD value, since if it divides both strings, it must be repeated.
4. We verify the candidate by checking if every block of size gcd in
str1 is equal to the candidate prefix.
5. The same check is applied to str2 by comparing each block of equal
size with the candidate substring.
6. If any block differs, we return an empty string, indicating no valid
common divisor substring exists.
7. Otherwise, if all blocks in both strings match the candidate, we
return it as the result.
*/

// Time Complexity: O(N + M)                                           // N = str1.size(), M = str2.size(), one pass over each string
// Space Complexity: O(G)                                              // G = gcd(N, M), substring of length G is stored

class Solution {
    int getGcd(int a, int b) {
        if(b == 0) return a;                                           // Base case for Euclidean Algorithm
        return getGcd(b, a % b);                                       // Recursive call with b and remainder of a / b
    }
public:
    string gcdOfStrings(string str1, string str2) {
        string ans;                                                    // Variable to store final GCD string
        int n = str1.size();                                           // Length of first string
        int m = str2.size();                                           // Length of second string
        int gcd = getGcd(n, m);                                        // Compute GCD of lengths using helper
        ans = str1.substr(0, gcd);                                     // Candidate GCD substring from str1
        for(int i=0; i<n/gcd; i++) {                                   // Verify all blocks in str1 match candidate
            if(str1.substr(i*gcd, gcd) != ans) return "";              // Return "" if mismatch found
        }
        for(int i=0; i<m/gcd; i++) {                                   // Verify all blocks in str2 match candidate
            if(str2.substr(i*gcd, gcd) != ans) return "";              // Return "" if mismatch found
        }
        return ans;                                                    // Return the valid common GCD string
    }
};

// or, same as above but without comments

class Solution {
    int getGcd(int a, int b) {
        if(b == 0) return a;
        return getGcd(b, a % b);
    }
public:
    string gcdOfStrings(string str1, string str2) {
        string ans;
        int n = str1.size();
        int m = str2.size();
        int gcd = getGcd(n, m);
        ans = str1.substr(0, gcd);
        for(int i=0; i<n/gcd; i++) {
            if(str1.substr(i*gcd, gcd) != ans) return "";
        }
        for(int i=0; i<m/gcd; i++) {
            if(str2.substr(i*gcd, gcd) != ans) return "";
        }
        return ans;
    }
};