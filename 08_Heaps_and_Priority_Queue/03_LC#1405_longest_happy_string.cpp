/* 1405. Longest Happy String

### Main logic: Greedy
Two cases:
1. Ans is empty or last two char of ans don't match with current highest freq char
    - Prefer using 2 chars over 1 unless the freq is limited to 1
2. Ans is not empty and last two char of ans match with current highest freq char
    - Look up for the next hightes freq char
        - If pq is not empty add the next highest freq char only once (not twice)
        - If pq is empty, break the loop and return ans


### Approach: Greedy Construction with Max-Heap to Avoid Triple Repeats
1. Use a max-heap to store available characters along with their frequencies, always picking the most frequent one first.
2. At each step, check the last two characters of the result string to ensure no character appears three times consecutively.
3. If the most frequent character would cause a triple repeat, attempt to use the next most frequent character instead.
4. If the next character is used, reduce its frequency and reinsert both the current and skipped characters back to heap.
5. If the most frequent character is safe to use, add it once or twice (whichever is safe), then reduce and reinsert.
6. Continue this greedy approach until no characters remain or no valid moves can be made without breaking constraints.
7. This ensures the longest possible diverse string is formed while respecting the no-three-in-a-row character rule.
8. The loop ends when the heap is empty or only characters that would cause invalid sequences are left.
9. The approach works efficiently since the heap always contains at most 3 characters, and operations are constant time.
10. Return the final string, which is guaranteed to be as long as possible under the problem's constraints.
*/


/*  
1. Greedy Construction with Max-Heap to Avoid Triple Repeats
Time Complexity: O(a + b + c)         // each character is added once per unit of its frequency
Space Complexity: O(3) ~ O(1)         // heap has at most 3 elements, constant space usage
*/

class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> pq;                                // max-heap: {frequency, character}
        if(a > 0) pq.push({a, 'a'});                                       // push 'a' if present
        if(b > 0) pq.push({b, 'b'});                                       // push 'b' if present
        if(c > 0) pq.push({c, 'c'});                                       // push 'c' if present

        string ans;                                                        // stores the resulting string

        while(!pq.empty()) {                                               // process while characters are left
            char ch = pq.top().second;                                     // get the character with highest freq
            int freq = pq.top().first;                                     // and its frequency
            pq.pop();                                                      // remove it from heap

            int len = ans.size();                                          // current length of result string
            if(len >= 2 && ans[len - 1] == ch && ans[len - 2] == ch) {     // avoid three same characters
                if(pq.empty()) break;                                      // if no other char, break
                pair<int, char> temp = {freq, ch};                         // store current char to push later
                ch = pq.top().second;                                      // use next character
                freq = pq.top().first;
                pq.pop();
                ans += ch;                                                 // append it
                pq.push(temp);                                             // push back skipped char
                freq--;                                                    // reduce frequency of used char
                if(freq > 0) pq.push({freq, ch});                          // reinsert if still needed
            } else {
                int use = (freq >= 2) ? 2 : 1;                             // use 2 if safe, else 1
                for(int i = 0; i < use; ++i) ans += ch;                    // append character
                freq -= use;                                               // decrement frequency
                if(freq > 0) pq.push({freq, ch});                          // reinsert if more occurrences
            }
        }
        return ans;                                                        // return the built diverse string
    }
};


// or, same as above but without comments

class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> pq;
        if(a > 0) pq.push({a, 'a'});
        if(b > 0) pq.push({b, 'b'});
        if(c > 0) pq.push({c, 'c'});
        string ans;

        while(!pq.empty()) {
            char ch = pq.top().second;
            int freq = pq.top().first;
            pq.pop();

            int len = ans.size();
            if(len >= 2 && ans[len - 1] == ch && ans[len - 2] == ch) {
                if(pq.empty()) break;
                pair<int, char> temp = {freq, ch};
                ch = pq.top().second;
                freq = pq.top().first;
                pq.pop();
                ans += ch;
                pq.push(temp);
                freq--;
                if(freq > 0) pq.push({freq, ch});
            } else {
                int use = (freq >= 2) ? 2 : 1;
                for(int i = 0; i < use; ++i) ans += ch;
                freq -= use;
                if(freq > 0) pq.push({freq, ch});
            }
        }
        return ans;
    }
};

// or, same as above but without comments and slightly compact

class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> pq;
        if(a > 0) pq.push({a, 'a'});
        if(b > 0) pq.push({b, 'b'});
        if(c > 0) pq.push({c, 'c'});
        string ans;

        while(!pq.empty()) {
            pair<int, char> first = pq.top();
            pq.pop();

            int len = ans.size();
            // Check if last two characters are same as the current one
            if(len >= 2 && ans[len - 1] == first.second && ans[len - 2] == first.second) {
                if(pq.empty()) break;

                pair<int, char> second = pq.top();
                pq.pop();

                ans += second.second;
                second.first--;

                if(second.first > 0) pq.push(second);
                pq.push(first);  // push the skipped character back
            } else {
                int use = (first.first >= 2) ? 2 : 1;
                for(int i = 0; i < use; ++i) ans += first.second;
                first.first -= use;

                if(first.first > 0) pq.push(first);
            }
        }
        return ans;
    }
};


// incomplete code, so ignore

class Solution {
    // bool isValid(string s, int a, int b, int c) {
    //     int countA = 0, countB = 0, countC = 0;
    //     for(int i=0; i<s.size(); i++) {
    //         if(s[i] == 'a') countA++;
    //         else if(s[i] == 'b') countB++;
    //         else if(s[i] == 'c') countC++;
    //     }
    //     if(countA > a || countB > b || countC > c) return false;
    //     return true;
    // }
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> pq;
        if(a > 0) pq.push({a, 'a'});
        if(b > 0) pq.push({b, 'b'});
        if(c > 0) pq.push({c, 'c'});
        string ans;
        char prev = 'z';
        while(!pq.empty()) {
            char ch = pq.top().second;
            int freq = pq.top().first;
            pq.pop();
            if(prev == ch) {
                if(!pq.empty()) {
                    pair<int, char> temp = {freq, ch};
                    ch = pq.top().second;
                    freq = pq.top().first; 
                    pq.pop();
                    pq.push(temp);
                }
                // else return isValid(ans, a, b, c) ? ans : "";                
                else return ans;
            }
            if(freq >= 2) {
                ans = ans + ch + ch;
                freq -= 2;
                prev = ch;
            }
            else {
                ans += ch;
                freq--;
                prev = ch;
            }
            if(freq > 0) pq.push({freq, ch});
        }
        return ans;
    }
};