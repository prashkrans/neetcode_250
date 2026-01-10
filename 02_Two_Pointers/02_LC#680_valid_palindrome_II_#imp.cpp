/* LC#680. Valid Palindrome II
*/


// Took a hint
// O(n)
// O(1)
class Solution {
    bool isPalindrome(string s) {
        int l = 0, r = s.size() - 1;
        while(l < r) {
            if(s[l] != s[r]) return false;
            l++;
            r--;
        }
        return true;
    }
    
public:
    bool validPalindrome(string s) {
        int l = 0, r = s.size() - 1;
        while(l < r) {
            if(s[l] != s[r]) { // At first mismatch, if either s[l+1, r] or s[l, r-1] is a palindrome its a valid palindrome
                return isPalindrome(s.substr(l + 1,  r - l)) || isPalindrome(s.substr(l, r - l));
            }            
            l++; 
            r--;
        }
        return true;
    }
};