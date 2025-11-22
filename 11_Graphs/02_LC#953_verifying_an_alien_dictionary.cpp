/* LC#953. Verifying an Alien Dictionary

### There are three cases:
1. Characters don't match:
   - Compare the positions of the characters in the alien order using `orderMap`.
   - If the character in the first word comes before the character in the second word, return true.
   - Otherwise, return false.

2. Characters match:
   - Continue comparing the next characters in both words.

3. One word is a prefix of the other (differ in size):
   - If the first word is longer than the second word, return false.
   - Otherwise, return true.

### Approach: Custom Lexicographical Order
1. Create a mapping `orderMap` to store the position of each character in the alien dictionary.
2. Define a helper function `verify` to compare two words based on the alien order:
   - Iterate through the characters of both words up to the length of the shorter word.
   - If characters differ, compare their positions in the alien order.
   - If one word is a prefix of the other, the shorter word should come first.
3. Iterate through the list of words and compare each pair of adjacent words using the `verify` function.
4. If all pairs are in order, return true; otherwise, return false.

### Notes:
- This approach ensures that the words are compared efficiently based on the given alien order.
- The use of a helper function makes the code modular and easier to understand.
*/

// Time Complexity: O(n * m) | 0 ms beats 100%
// - Building the `orderMap` takes O(26) = O(1) since the alphabet size is constant.
// - Comparing two words takes O(m), where m is the average length of the words.
// - Comparing all adjacent words in the list takes O(n * m), where n is the number of words.

// Space Complexity: O(26) ~ O(1) 
// - The `orderMap` uses constant space since it stores at most 26 characters.

class Solution {
    bool verify(string &s1, string &s2, unordered_map<char, int> &orderMap) {
        int n = s1.size(), m = s2.size();
        for(int i = 0; i < min(n, m); i++) {                    // Compare characters of both strings
            if(s1[i] != s2[i])                                  // If characters differ
                return orderMap[s1[i]] < orderMap[s2[i]];       // Return true if s1[i] comes before s2[i] in the alien order
        }
        return n <= m;                                          // If one string is a prefix of the other, the shorter string should come first
    }
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> orderMap;                      // Map to store the alien order of characters
        for(int i = 0; i < order.size(); i++)                   // Populate the map with character positions
            orderMap[order[i]] = i;
        for(int i = 1; i < words.size(); i++) {                 // Compare each pair of adjacent words
            if(!verify(words[i - 1], words[i], orderMap)) 
                return false;                                   // If any pair is not in order, return false
        }
        return true;                                            // All words are in order
    }
};


// or, same as above but without comments

class Solution {
    bool verify(string &s1, string &s2, unordered_map<char, int> &orderMap) {
        int n = s1.size(), m = s2.size();
        for(int i=0; i<min(n, m); i++) {
            if(s1[i] != s2[i]) return orderMap[s1[i]] < orderMap[s2[i]];
        }
        return n <= m;
    }
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> orderMap;
        for(int i=0; i<order.size(); i++) orderMap[order[i]] = i;
        for(int i=1; i<words.size(); i++) {
            if(!verify(words[i-1], words[i], orderMap)) return false;
        }
        return true;
    }
};