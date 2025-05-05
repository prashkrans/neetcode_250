/* LC#2707. Extra Characters in a String
*/

// 1. Rec without memo
// Works correctly but gets TLE 171/2028

class Solution {
    int rec(int left, int right, string &s, unordered_set<string> &wordSet) {
        if(right == s.size()) return 0;
        int skip = INT_MAX;
        int take = INT_MAX;
        skip = rec(right+1, right+1, s, wordSet);
        if(skip != INT_MAX) skip++;
        string substr;
        while(right < s.size()) {                        // Iterate through all substrings starting at `left`
            substr += s[right];
            if(wordSet.find(substr) != wordSet.end()) {  // Check if the substring exists in the dictionary
                take = rec(right + 1, right + 1, s, wordSet); // Recurse for the remaining string
            }
            right++;
        }
        return min(skip, take);
    }
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        unordered_set<string> wordSet(dictionary.begin(), dictionary.end()); // Convert wordDict to a set for O(1) lookups
        return rec(0, 0, s, wordSet);                 // Start the recursion         
    }
};