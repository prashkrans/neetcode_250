/* LC#344. Reverse String
*/

// O(n)
// O(1)

class Solution {
public:
    void reverseString(vector<char>& s) {
        int l = 0, r = s.size() - 1;
        while(l < r) {
            swap(s[l], s[r]);
            l++;
            r--;
        }        
    }
};