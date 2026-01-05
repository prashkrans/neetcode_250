/* LC#682. Baseball Game

### Approach: Stack-Based Score Simulation
1. Initialize a stack to store valid round scores as integers, enabling easy access
to previous scores for mathematical operations.
2. Traverse the operations array once, processing each string based on its meaning
such as addition, cancellation, doubling, or direct numeric insertion.
3. For "+" operation, pop the last score temporarily, peek the next score, restore
the popped value, and push their sum.
4. For "C" operation, remove the most recent score from the stack to invalidate it.
5. For "D" operation, calculate twice the top score and push the result back.
6. For numeric values, convert the string to integer using stoi and push it directly.
7. After processing all operations, iterate through the stack and accumulate all
stored scores to compute the final result.
*/


// Method 1: Using a stack of integers
// Time Complexity: O(2n) ~ O(n) due to double traversal of operations | 0ms (100.00%)
// Space Complexity: O(n) due to stack usage

class Solution {
public:
    int calPoints(vector<string>& operations) {                    // function to calculate final score
        int sum = 0;                                               // stores total sum of valid scores
        stack<int> st;                                             // stack to maintain score history
        for(auto i: operations) {                                  // iterate through each operation
            if(i=="+") {                                           // case when sum of last two scores is needed
                int a = st.top();                                  // store last score
                st.pop();                                          // remove last score temporarily
                int b = st.top();                                  // get second last score
                st.push(a);                                        // restore last score back to stack
                st.push(a+b);                                      // push sum of last two scores
            } else if(i=="C") {                                    // case to invalidate last score
                st.pop();                                          // remove last score from stack
            } else if(i=="D") {                                    // case to double last score
                int res = 2 * st.top();                            // compute double of last score
                st.push(res);                                      // push doubled score
            } else {                                               // case when operation is a number
                st.push(stoi(i));                                  // convert string to integer and push
            }
        }
        while(!st.empty()) {                                       // iterate until stack becomes empty
            sum += st.top();                                       // add top score to sum
            st.pop();                                              // remove top score
        }
        return sum;                                                // return final calculated score
    }
};

// Method 1b: Using a stack of integers (Same as above but without comments)
class Solution {
public:
    int calPoints(vector<string>& operations) {
        int sum = 0;
        stack<int> st;
        for(auto i: operations) {
            if(i=="+") {
                int a = st.top();
                st.pop();
                int b = st.top();
                st.push(a);
                st.push(a+b);
            } else if(i=="C") {
                st.pop();
            } else if(i=="D") {
                int res = 2 * st.top();
                st.push(res);
            } else {
                st.push(stoi(i));
            }
        }
        while(!st.empty()) {
            sum += st.top();
            st.pop();
        }
        return sum;
    }
};