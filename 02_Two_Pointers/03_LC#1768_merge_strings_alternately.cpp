/* LC#1768. Merge Strings Alternately

### Approach 1: Two Pointer Alternating Merge
1. Use two pointers to track current positions in both input strings.
2. Maintain a boolean flag to decide which string contributes next character.
3. Iterate while both strings still have remaining characters.
4. Append character from appropriate string based on current turn.
5. Toggle the turn after each append operation to ensure alternating behavior.
6. After loop, append remaining characters from either string if one is longer.
7. Combined traversal ensures linear time with respect to total string length.
*/

// 1. Two Pointer Alternating Merge (My original solution | 10 min) 
// Time Complexity: O(n + m) | 0ms, beats 100%
// Space Complexity: O(n + m)
// where n = word1.size() and m = word2.size();

class Solution {
public:
    string mergeAlternately(string word1, string word2) {          // function to merge strings alternately
        string res;                                                // stores merged result string
        int i = 0, j = 0, n = word1.size(), m = word2.size();      // indices and lengths of both strings
        bool isWord1Turn = true;                                   // flag to alternate between strings
        while(i < n && j < m) {                                    // loop while both strings have characters
            if(isWord1Turn) {                                      // check if word1 turn
                res += word1[i++];                                 // append character from word1
                isWord1Turn = false;                               // switch turn to word2
            } else {
                res += word2[j++];                                 // append character from word2
                isWord1Turn = true;                                // switch turn to word1
            }
        }
        while(i < n) res += word1[i++];                            // append remaining characters of word1
        while(j < m) res += word2[j++];                            // append remaining characters of word2
        return res;                                                // return merged string
    }
};
