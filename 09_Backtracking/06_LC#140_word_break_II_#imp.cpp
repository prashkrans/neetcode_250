/* LC#140. Word Break II
Exactly same as LC#139 Word Break I (1D or 2D DP) but modified to store all such possible sentences.

Three cases: [#IMP]
1. If the current substring is not found in `wordSet` => simply increment `r` to expand the substring.
2. If the current substring is found in `wordSet`:
    Two choices:
    - Include the substring in the current path and recurse for the remaining string starting at `r + 1`.
    - Skip the current substring and continue expanding `r` to explore longer substrings.
3. If `r` reaches the end of the string:
    - Check if the constructed path covers the entire string.
    - If valid, add the path (without the trailing space) to the result.

### Approach: Backtracking with Sliding Window using Two Pointers
1. Use two pointers `left` and `right` to represent the current substring being checked.
2. Base case:
   - If `right` reaches the end of the string, check if the constructed path covers the entire string.
   - If valid, add the path (without the trailing space) to the result.
3. Recursive steps:
   - Iterate through all substrings starting at `left` and ending at `right`.
   - If the substring exists in the dictionary, recurse for the remaining string starting at `right + 1`.
4. Return the result vector containing all valid sentences.

### Complexity:
- **Time Complexity**: O(2^n)
  - For each starting index, we explore all possible substrings, leading to an exponential number of recursive calls.
- **Space Complexity**: O(n)
  - The recursion stack can go as deep as the length of the string `s`.

### Notes:
- This approach generates all possible valid sentences by exploring all substrings recursively.
- It is not optimized and can be improved using memoization to avoid redundant calculations.
*/

// B1. Backtracking with Sliding Window using Two Pointers (My custom code)
// Time Complexity: O(2^n) | 0ms beats 100%
// - For each starting index, we explore all possible substrings, leading to an 
// exponential number of recursive calls.

// Space Complexity: O(n)
// - The recursion stack can go as deep as the length of the string `s`.

class Solution {
    void rec(int left, int right, string &s, unordered_set<string> &wordSet, string path, vector<string> &ans) {
        if(right == s.size()) {                          // Base case: reached the end of the string
            int pathSize = 0;
            for(int i = 0; i < path.size(); i++) {       // Calculate the size of the path without spaces
                if(path[i] >= 'a' && path[i] <= 'z') pathSize++;
            }
            if(pathSize == s.size())                     // If the path covers the entire string, add it to the result
                ans.push_back(path.substr(0, path.size() - 1)); // Remove the trailing space
            return;
        }
        string substr;
        while(right < s.size()) {                        // Iterate through all substrings starting at `left`
            substr += s[right];
            if(wordSet.find(substr) != wordSet.end()) {  // Check if the substring exists in the dictionary
                rec(right + 1, right + 1, s, wordSet, path + substr + " ", ans); // Recurse for the remaining string
            }
            right++;
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<string> ans;                              // Result vector to store all valid sentences
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end()); // Convert wordDict to a set for O(1) lookups
        rec(0, 0, s, wordSet, "", ans);                 // Start the recursion
        return ans;                                      // Return the result
    }
};

// ##################################################################################
// Refer the code below which is a solution of LC#139 Word Break I
// B1. Backtracking with Sliding Window using Two Pointers (My custom code) (Rec without memo)

// Time Complexity: O(2^n) | Gets TLE 
// - For each starting index `l`, we explore all possible substrings starting at `l`.
// - This results in an exponential time complexity due to redundant calculations.

// Space Complexity: O(n)
// - The recursion stack can go as deep as the length of the string `s`.

class Solution {
    bool rec(int l, int r, string &s, unordered_set<string> &dict) {
        if(r == s.size()) return true;                      // Base case: reached the end of the string
        string substr;
        while(r < s.size()) {                               // Iterate through all substrings starting at `l`
            substr += s[r];
            if(dict.find(substr) != dict.end()) {           // Check if the substring exists in the dictionary
                if(rec(r + 1, r + 1, s, dict)) return true; // Recurse for the remaining string
            }
            r++;
        }
        return false;                                       // If no valid split is found, return false
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end()); // Convert wordDict to a set for O(1) lookups
        return rec(0, 0, s, dict);                          // Start the recursion
    }
};

