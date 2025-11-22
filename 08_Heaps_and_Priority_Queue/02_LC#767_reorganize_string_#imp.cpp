/* LC#767. Reorganize String

### Hint 1: Alternate placing the most common letters.
### Hint 2: Use prev variable (or ans.back()) to store the previous variable



### Approach 1: Greedy Reorganization Using Max-Heap (My Custom Code - Prefer this method)
1. Count the frequency of each character in the input string using an unordered_map for constant-time access.
2. Use a max-heap (priority_queue) to always pick the character with the highest remaining frequency first.
3. To avoid adjacent duplicates, keep track of the previously used character and avoid placing it immediately again.
4. If the current top character is the same as the previously used one, select the next highest frequency character.
5. After using a different character, reinsert the skipped character back into the heap for future selection.
6. Continue building the result string by greedily selecting non-repeating characters from the heap.
7. If at any point no valid character can be used (heap empty but previous char can't repeat), return an empty string.
8. Push characters back into the heap only if their remaining frequency is greater than zero after use.
9. This approach ensures no two adjacent characters are the same and maximizes use of frequent characters early.
10. Return the final string which meets the reorganization condition, or an empty string if it's not feasible.
*/


/* 
1. Greedy Reorganization Using Max-Heap (My Custom Code - Prefer this method)
Time Complexity: O(n*log(k)) = O(n*log26) ~ O(n) | 0ms beats 100%           // n = length of string, k = unique characters (at most 26)
Space Complexity: O(n + k) = O(n + 26) ~ O(n)                               // n for output string, k for frequency map and heap
*/

class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> freqMap;                                  // stores frequency of each character
        for(auto ch: s) freqMap[ch]++;                                     // count frequencies in the string

        priority_queue<pair<int, char>> pq;                                // max-heap sorted by frequency
        for(auto i: freqMap) pq.push({i.second, i.first});                 // push {frequency, character} into heap

        string ans;                                                        // stores final reorganized string
        char prev = '#';                                                   // tracks previously added character

        while(!pq.empty()) {                                               // process while characters remain in heap
            char ch = pq.top().second;                                     // get character with highest frequency
            int freq = pq.top().first;                                     // get its frequency
            pq.pop();                                                      // remove it from heap

            if(ch == prev) {                                               // check for adjacent duplicates
                pair<int, char> temp = {freq, ch};                         // store current char to reinsert later
                if(!pq.empty()) {                                          // if another char is available
                    ch = pq.top().second;                                  // use next best character
                    freq = pq.top().first;
                    pq.pop();
                    pq.push(temp);                                         // reinsert previous char back to heap
                } 
                else return "";                                            // not possible to reorganize
            }

            freq--;                                                        // decrement frequency
            if(freq > 0) pq.push({freq, ch});                              // reinsert after decreasing frequency by one

            ans += ch;                                                     // add to result
            prev = ch;                                                     // update previous char
        }
        return ans;                                                        // return the reorganized string
    }
};

// or, same as above but without comments

class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> freqMap;
        for(auto ch: s) freqMap[ch]++;
        priority_queue<pair<int, char>> pq;
        for(auto i: freqMap) pq.push({i.second, i.first});
        string ans;
        char prev = '#';                      // using a prev variable
        while(!pq.empty()) {
            char ch = pq.top().second;
            int freq = pq.top().first;
            pq.pop();
            if(ch == prev) {
                pair<int, char> temp = {freq, ch};
                if(!pq.empty()) {
                    ch = pq.top().second;
                    freq = pq.top().first;
                    pq.pop();
                    pq.push(temp);
                } 
                else return "";
            }
            freq--;
            if(freq > 0) pq.push({freq, ch});
            ans += ch;
            prev = ch;
        }
        return ans;
    }
};

// or, same as above but without comments and more compact

class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> freqMap;
        for(auto ch: s) freqMap[ch]++;
        priority_queue<pair<int, char>> pq;
        for(auto i: freqMap) pq.push({i.second, i.first});
        string ans;
        while(!pq.empty()) {
            pair<int, char> first = {pq.top().first, pq.top().second};
            pq.pop();
            if(!ans.empty() && first.second == ans.back()) {
                if(!pq.empty()) {
                    pair<int, char> second = {pq.top().first, pq.top().second};
                    pq.pop();
                    pq.push(first);
                    ans += second.second;
                    second.first--;
                    if(second.first > 0) pq.push(second);
                } 
                else return "";
            }
            else {
                ans += first.second;
                first.first--;
                if(first.first > 0) pq.push(first);
            }
        }
        return ans;
    }
};


// Incorrect code, ignore
struct cmp {
    bool operator() (pair<int, char> &a, pair<int, char> &b) const {
        if(a.first == b.first) return a.second > b.second;
        else return a.first < b.first;
    }
};

class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> freqMap;
        for(auto ch: s) freqMap[ch]++;
        priority_queue<pair<int, char>, vector<pair<int, char>>, cmp> pq;
        for(auto i: freqMap) pq.push({i.second, i.first});
        for(auto i: freqMap) cout<<i.second<<" <- "<<i.first<<endl;
        string ans;
        while(!pq.empty()) {
            char ch = pq.top().second;
            int freq = pq.top().first - 1;
            cout<<ch<<" ==> "<<freq<<endl;
            pq.pop();
            if(freq > 0) pq.push({freq, ch});
            if(!ans.empty() && ans.back() == ch) return "";
            ans += ch;
        }
        return ans;
    }
};