/* LC#13 Roman to Integer

### Approach 1: Right-to-Left Parsing with Value Comparison (My Custom Code)
1. Roman numerals are parsed from right to left because subtractive cases
like IV and IX depend on smaller values preceding larger ones.
2. We store values of Roman numerals in a fixed unordered_map for quick
lookups in constant time.
3. As we iterate the string in reverse, we maintain a variable `prev` to
track the value of the last processed numeral.
4. If the current character’s value is less than `prev`, it indicates a
subtractive pattern, so we subtract it from the result.
5. Otherwise, we add the current value to the result as part of normal
Roman numeral accumulation.
6. The key idea is comparing each numeral with the one processed just
before it to decide whether to add or subtract.
7. After the loop ends, the result contains the correct integer value
equivalent to the Roman numeral string.
*/

// 1. Right-to-Left Parsing with Value Comparison (My Custom Code)
// Time complexity: O(n)                            // Single pass over string of length n
// Space complexity: O(1)                           // Fixed-size hash map and constant variables used

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> mp = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}}; // Roman numeral values
        int n = s.size();                           // Length of the input Roman string
        int ans = 0;                                // Variable to store final integer result
        int prev = INT_MIN;                         // Track value of previously processed numeral
        for(int i=n-1; i>=0; i--) {                 // Traverse string from right to left
            if(mp[s[i]] < prev) ans -= mp[s[i]];    // Subtract if current numeral is smaller than previous
            else ans += mp[s[i]];                   // Otherwise, add it to the result
            prev = mp[s[i]];                        // Update previous numeral value
        }
        return ans;                                 // Return the final converted integer
    }
};

// or, same as above but without comments

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> mp = {
            {'I', 1}, {'V', 5}, {'X', 10}, 
            {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}
        };
        int n = s.size();
        int ans = 0;
        int prev = INT_MIN;
        for(int i=n-1; i>=0; i--) {
            if(mp[s[i]] < prev) ans -= mp[s[i]];
            else ans += mp[s[i]];
            prev = mp[s[i]];
        }
        return ans;
    }
};