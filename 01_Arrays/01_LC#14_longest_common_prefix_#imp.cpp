/* LC#14. Longest Common Prefix

Multiple ways:
1. Horizontal scanning
2. Vertical scanning
3. Sorting (Easiest)
4. Tries (Cool and important approach)
*/


// 1. Vertical scanning (My original solution)
// O(n * m) | 0ms, beats 100%
// O(1)
// where m = no. of strings and n = size of the shortest string

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string s;
        int minSize = INT_MAX;
        for(int i = 0; i < strs.size(); i++) {
            minSize = min(minSize, (int) strs[i].size());
        }
        for(int j = 0; j < minSize; j++) {
            char curr = strs[0][j];
            for(int i = 1; i < strs.size(); i++) {
                if(strs[i][j] != curr) return s;    
            }    
            s += strs[0][j];
        }
        return s;
    }
};

/* 2. Sorting
When strings are sorted lexicographically, the first and last strings in the sorted order are the most different from each other. 
If these two extremes share a common prefix, then all strings in between must also share that same prefix.
So we only need to compare the first and last strings after sorting.

O(n * mlogm)
O(1) or O(m) depending on queue sort or merge sort
*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {              // function to find longest common prefix
        if (strs.size() == 1) {                                     // single string edge case
            return strs[0];                                         // entire string is the prefix
        }

        sort(strs.begin(), strs.end());                             // sort strings lexicographically
        for (int i = 0; i < min(strs[0].length(), strs.back().length()); i++) {
                                                                    // iterate up to shorter string length
            if (strs[0][i] != strs.back()[i]) {                     // mismatch found
                return strs[0].substr(0, i);                        // return prefix until mismatch
            }
        }
        return strs[0];                                             // first string is the common prefix
    }
};

// 3. Using a trie (My original solution)
// O(n * m) | 0ms, beats 100%
// O(n)

struct node {
    bool isWord;
    node* children[26];
    node () {
        isWord = false;
        for(int i=0; i<26; i++) children[i] = nullptr;
    }
};

class Solution {
    node* root;
public:
    Solution(): root(new node) {}

    void insert(string s) {
        node* curr = root;
        for(int i=0; i<s.size(); i++) {
            int index = s[i] - 'a';
            if(curr -> children[index] == nullptr) curr -> children[index] = new node;
            curr = curr -> children[index];
        }
        curr -> isWord = true;
    }

    int lcp(string s) {
        int count = 0;
        node* curr = root;
        for(int i=0; i<s.size(); i++) {
            int index = s[i] - 'a';
            if(curr->children[index] == nullptr) return count;
            else {
                count++;
                curr = curr -> children[index];
            }
        }
        return count;
    }
    
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==1) return strs[0];
        else {
            insert(strs[0]);
            int minLcpLength = INT_MAX;
            for(int i=1; i<strs.size(); i++) {
                minLcpLength = min(minLcpLength, lcp(strs[i]));
            }
            // cout<<minLcpLength<<" ";
            return strs[0].substr(0, minLcpLength);
        }
    }
};