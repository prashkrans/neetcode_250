/* LC#71. Simplify Path
*/

// Method 1: Using stack (My original solution | 25 minutes)
// Time Complexity: O(3n) ~ O(n) due to single pass + stack operations + reversing
// Space Complexity: O(n) due to stack usage
// where n is the length of the input path string

class Solution {
    stack<string> st;                                               // stack to store valid directory names
public:
    string simplifyPath(string path) {                              // function to simplify Unix path
        string ans;                                                 // stores final simplified path
        string dir;                                                 // temporary directory name holder
        for(int i = 0; i < path.size(); i++) {                      // iterate through each character
            if(path[i] == '/') {                                    // directory separator encountered
                if (dir.empty()) continue;                          // skip consecutive slashes
                else {
                    if(dir == ".." && !st.empty()) st.pop();        // move one directory up
                    else if(dir != "." && dir != "..") st.push(dir);
                                                                    // push valid directory name
                    dir.clear();                                    // reset directory buffer
                }
            }
            else dir += path[i];                                    // build directory name character by character
        }
        if(!dir.empty() && dir != "." && dir != "..") st.push(dir); // push last directory if valid
        else if(dir == ".." && !st.empty()) st.pop();               // handle trailing parent directory
        vector<string> strs;                                        // vector to reverse stack order
        while(!st.empty()) {                                        // pop all stack elements
            strs.push_back(st.top());                               // store directory name
            st.pop();                                               // remove from stack
        }
        reverse(strs.begin(), strs.end());                          // restore correct directory order
        for(auto str: strs) ans += str + "/";                       // build simplified path
        ans = "/" + ans.substr(0, ans.size() - 1);                  // remove trailing slash and prefix root
        return ans;                                                 // return canonical path
    }
};



// Method 2: Same as above but using list or a vector that works as a stack and is compact as path is appened by "\"
// Time Complexity: O(2n) ~ O(n) due to single pass + stack operations using a vector/list | 0ms beats 100%
// Space Complexity: O(n) extra space due to the vector/list strs
// where n is the length of the input path string

class Solution {
    vector<string> strs;    // or list<string> strs;                // stores valid directory components
public:
    string simplifyPath(string path) {                              // function to simplify Unix path
        string ans;                                                 // stores final simplified path
        string dir;                                                 // temporary directory name buffer
        for(char ch: path + "/") {                                  // iterate through each character
            if(ch == '/') {                                         // slash indicates directory boundary
                if (dir.empty()) continue;                          // skip consecutive slashes
                else {
                    if(dir == ".." && !strs.empty()) strs.pop_back(); // move one directory up
                    else if(dir != "." && dir != "..") strs.push_back(dir); // store valid directory name                                     
                    dir.clear();                                    // reset directory buffer
                }
            }
            else dir += ch;                                         // accumulate directory characters
        }
        if(strs.empty()) ans = "/";                                 // root directory case
        else {
            for(auto str: strs) ans += "/" + str;                   // construct canonical path
        }
        return ans;                                                 // return simplified path
    }
};
