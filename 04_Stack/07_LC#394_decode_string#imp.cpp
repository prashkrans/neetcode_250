/* LC#394. NCST8. Decode String

Approaches:
1. Using two stacks (Prefer this method)
2. Using recursion with a global variable i as the index

Note:
1. Notice the difference between '[' and "["
2. Using if(isdigit(s[i])) which is the same as if(s[i] >= '0' && s[i] <= '9') | Note: its isdigit() not isDigit()
3. Carefully increment i as per the different branches
4. s[i] is a char while stringStack is a stack of strings not chars so, stringStack.push("") with double quotes or 
using string concat operator i.e. +
5. There are four cases: 
    a. s[i] is a digit
    b. s[i] is '['
    c. s[i] is ']'
    d. s[i] is a lowercase alphabet (a to z) i.e. the else part
6. Note the way currString is getting formed differently for diff branches:
    a. currString = stringStack.top() + currString; (Not currString += stringStack.top();)
    b. currString += s[i];
    c. ans = stringStack.top() + ans; (not ans += stringStack.top();)
7. numStack would always be empty when we come out of the while loop but stringStack would not be empty


/*
### Approach: Using Two Stacks for Decoding
1. Use two stacks: `numStack` to store repeat counts and `stringStack` to store
intermediate strings.
2. Traverse the input string character by character (4 cases) [#IMP]:
   a.   If the character is a digit, form the complete number by iterating through
        consecutive digits. Push the number onto `numStack`.
   b.   If the character is '[', push it onto `stringStack` to mark the start of a
        repeated substring.
   c.   If the character is ']', process the substring inside the brackets:
        i.  Pop strings from `stringStack` until '[' is encountered. Concatenate these
            strings to form the substring inside the brackets.
        ii. Pop the repeat count from `numStack` and repeat the substring that many
            times.
        iii. Push the repeated substring back onto `stringStack`.
   d.   If the character is a lowercase letter, collect all consecutive letters to form
        a string and push it onto `stringStack`.
3. After processing the entire string, collect all strings (one or more) from `stringStack` to form
the final decoded string.
4. The algorithm ensures that each character is processed once, resulting in a time
complexity of O(n), where n is the length of the input string.
*/

// 1. Using two stacks: a. numStack b. stringStack
// Time Complexity: O(n + N) | 0ms beats 100%
// - Each character in the string is processed once.
// - n = length of the input string.
// - N = length of the output string

// Space Complexity: O(n + N)
// - Space is used by the two stacks: numStack and stringStack.

class Solution {
public:
    string decodeString(string s) {
        stack<int> numStack;                            // Stack to store repeat counts
        stack<string> stringStack;                      // Stack to store intermediate strings
        int i=0;                                        // Pointer to traverse the string
        while(i < s.size()) {                           // Iterate through the string
            if(isdigit(s[i])) { // or if(s[i] >= '0' && s[i] <= '9') { // If the character is a digit
                int num = 0;                            // Initialize the number
                while(isdigit(s[i])) { // or while(s[i] >= '0' && s[i] <= '9'){ // Form the complete number
                    num = num * 10 + (s[i] - '0');      // Update the number
                    i++;                                // Move to the next character
                }
                numStack.push(num);                     // Push the number onto the stack
            }
            else if(s[i] == '[') {                      // If the character is '['
                stringStack.push("[");                  // Push "[" onto the string stack
                i++;                                    // Move to the next character
            }
            else if(s[i] == ']') {                      // If the character is ']'
                string currString;                      // Initialize the current string
                int currTimes = numStack.top();         // Get the repeat count from numStack
                numStack.pop();                         // Remove the repeat count from the stack
                while(!stringStack.empty() && stringStack.top() != "[") { // Collect the string inside brackets
                    currString = stringStack.top() + currString; // [#IMP] Append st.top() to the start of the current string
                    stringStack.pop();                 // Remove the top string from the stack
                }
                if(!stringStack.empty()) stringStack.pop(); // [#IMP] Remove the "[" from the stack
                string res;                             // Initialize the repeated string
                while(currTimes--) res = res + currString; // Repeat the string currTimes times
                stringStack.push(res);                  // Push the result back onto the stack
                i++;                                    // Move to the next character
            }
            else {                                      // If the character is a lowercase letter
                string currString;                      // Initialize the current string
                while(!s.empty() && s[i] >= 'a' && s[i] <= 'z') { // Collect all consecutive letters
                    currString += s[i];                 // Append the letter to the current string
                    i++;                                // Move to the next character
                }
                stringStack.push(currString);           // Push the current string onto the stack
            }
        }
        string ans;                                     // Initialize the final result
        if(!stringStack.empty()) {                      // If the string stack is not empty
            while(!stringStack.empty()) {               // Collect all strings from the stack
                ans = stringStack.top() + ans;          // Append the top string to the result
                stringStack.pop();                      // Remove the top string from the stack
            }
        }
        return ans;                                     // Return the decoded string
    }
};


// 2. Using recursion with a global variable i as the index
// This is a smaller solution but tricky to come up with.

// Time Complexity: O(n + N)
// - Each character in the string is processed once during the recursion.
// - n = length of the input string.

// Space Complexity: O(n + N)
// - Space is used by the recursion stack, which can go up to the depth of nested brackets.

class Solution {
    string rec(int &i, string s) {
        string ans = "";                                // Initialize the result string
        while(i < s.size() && s[i] != ']') {            // Process until the end of the string or a closing bracket
            if(isdigit(s[i])) {                         // If the character is a digit
                int num = 0;                            // Initialize the repeat count
                while (isdigit(s[i])) {                 // Form the complete number
                    num = num * 10 + (s[i] - '0');      // Update the number
                    i++;                                // Move to the next character
                }
                i++;                                    // Skip the '[' character
                string res = rec(i, s);                 // Recursively decode the substring inside the brackets
                i++;                                    // Skip the ']' character
                while(num--) ans += res;                // Repeat the decoded substring and append to the result
            } else {                                    // If the character is a lowercase letter
                ans += s[i];                            // Append the character to the result
                i++;                                    // Move to the next character
            }
        }
        return ans;                                     // Return the decoded string
    }
  
public:
    string decodeString(string s) {
        int i = 0;                                      // Initialize the index for traversal
        return rec(i, s);                               // Start the recursive decoding
    }
};