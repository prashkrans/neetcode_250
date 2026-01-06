/* LC#735. Asteroid Collision
Various methods: 
1. Stack STL
2. Vector STL as stack (push_back, pop_back, back)
*/

/*
### Approach 1: Stack-Based Asteroid Collision Simulation
1. Use a stack to simulate asteroid movement and collisions
while processing asteroids sequentially from left to right.
2. Push all right moving asteroids directly since they cannot
collide immediately with previous asteroids.
3. When a left moving asteroid appears, repeatedly compare it
with stack top if the top is moving right.
4. Pop smaller right moving asteroids until a larger one appears
or the stack becomes empty.
5. If both asteroids have equal absolute size, destroy both by
popping stack and discarding current asteroid.
6. If a larger right moving asteroid exists, discard current
asteroid and continue processing.
7. Otherwise, push the left moving asteroid as it survives.
8. Finally, reverse stack contents to restore correct order.
*/


// Method 1: My approach using stack to simulate asteroid collisions (26 minutes)
// Time Complexity: O(3n) ~ O(n) due to triple traversal | 0ms, beats 100%
// Space Complexity: O(n) extra space due to stack usage
// where n is the number of asteroids

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {       // function to resolve asteroid collisions
        vector<int> ans;                                          // stores final surviving asteroids
        stack<int> st;                                            // stack to simulate asteroid movement
        for(auto i: asteroids) {                                  // iterate through each asteroid
            if(st.empty()) st.push(i);                            // push if stack is empty
            else if(i > 0) st.push(i);                             // push right moving asteroid
            else if(i < 0) {                                      // handle left moving asteroid
                while(!st.empty() && abs(i) > st.top() && st.top() > 0) {
                    st.pop();                                     // destroy smaller right moving asteroids
                }
                if(!st.empty() && st.top() == abs(i)) st.pop();  // destroy both asteroids if equal size
                else if(!st.empty() && st.top() >= abs(i)) continue; // current left moving asteroid destroyed
                else st.push(i);                                  // push current left moving asteroid
            }
        }
        while(!st.empty()) {                                      // collect remaining asteroids
            ans.push_back(st.top());                              // add asteroid to result
            st.pop();                                             // remove from stack
        }
        reverse(ans.begin(), ans.end());                          // restore original order
        return ans;                                               // return final asteroid states
    }
};
