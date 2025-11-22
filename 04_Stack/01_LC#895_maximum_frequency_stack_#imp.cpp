/* LC#895. Maximum Frequency Stack

Three components:
1. map of elements and their frequencies
2. map of frequencies and stacks
3. max frequency variable that may or may not increase(or, decrease) with each push(or, pop)

Note:
- stacks could either be an unordered_map of stacks or a vector of stacks
- incase of a vector of stacks, index of stack = freq - 1 not freq
*/

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */

/*
### Approach: Hash Maps with Frequency-Based Stacks
1. Use a frequency map to keep count of how many times each number has been pushed into
the stack, allowing fast updates.
2. Use another map that maps each frequency to a stack that holds all numbers with that
exact frequency, preserving order.
3. When pushing, increment the value’s frequency and push it onto the corresponding stack
based on updated frequency.
4. Track the current highest frequency so we can always access the most frequent element
in constant time during popping.
5. When popping, retrieve the top element from the stack corresponding to max frequency,
decrement its frequency, and return it.
6. If a stack at max frequency becomes empty, reduce maxFreq to the next available frequency
that has elements.
7. This setup ensures both push and pop operations happen in O(1) time and use O(N) space
for the underlying structures.
*/

// 1. Using a map of stacks
// Time Complexity (push): O(1)                                         // Each push is done in constant time with direct updates
// Time Complexity (pop):  O(1)                                         // Each pop is constant due to hash map and stack usage
// Space Complexity:      O(N)                                          // Space used for storing frequency map and grouped stacks

class FreqStack {
    unordered_map<int, int> freqMap;                                    // Maps each value to its frequency count
    unordered_map<int, stack<int>> stacks;                              // Maps frequency to stack of values with that frequency
    int maxFreq = 0;                                                    // Tracks the current highest frequency
public:
    FreqStack() {}                                                      // Constructor: No special initialization needed
    
    void push(int val) {
        freqMap[val]++;                                                 // Increase the frequency of val
        int currFreq = freqMap[val];                                    // Store the current frequency of val
        stacks[currFreq].push(val);                                     // Push val into the stack for this frequency
        maxFreq = max(maxFreq, currFreq);                               // Update maxFreq if current frequency is highest
    }
    
    int pop() {
        int maxFreqVal = stacks[maxFreq].top();                         // Get top value from the stack with max frequency
        stacks[maxFreq].pop();                                          // Remove the top value from that stack
        freqMap[maxFreqVal]--;                                          // Decrease the frequency of that value
        if(stacks[maxFreq].empty()) maxFreq--;                          // If stack is empty, decrease maxFreq
        return maxFreqVal;                                              // Return the value popped
    }
};

// 2. Using a vector of stacks
// Time Complexity (push): O(1)                                         // Constant time due to direct map and stack operations
// Time Complexity (pop):  O(1)                                         // Constant time due to access at maxFreq-1 index
// Space Complexity:      O(N)                                          // O(N) space to hold frequency map and value stacks

class FreqStack {
    unordered_map<int, int> freqMap;                                    // Maps each value to its current frequency
    vector<stack<int>> stacks;                                          // Vector of stacks indexed by frequency - 1
    int maxFreq = 0;                                                    // Keeps track of the highest frequency
public:
    FreqStack() {}                                                      // Constructor: initializes an empty structure
    
    void push(int val) {
        freqMap[val]++;                                                 // Increment the frequency count of the value
        if(stacks.size()<freqMap[val]) stacks.push_back(stack<int>());  // Ensure stack exists for this frequency
        stacks[freqMap[val]-1].push(val);                               // Push value into its frequency stack
        maxFreq = max(maxFreq, freqMap[val]);                           // Update maxFreq to reflect highest frequency
    }
    
    int pop() {
        int maxFreqVal = stacks[maxFreq-1].top();                       // Get top value from max frequency stack
        stacks[maxFreq-1].pop();                                        // Remove that value from the stack
        freqMap[maxFreqVal]--;                                          // Decrease its frequency count
        if(stacks[maxFreq-1].empty()) maxFreq--;                        // Reduce maxFreq if no elements left at that freq
        return maxFreqVal;                                              // Return the most frequent and recent value
    }
};


// or, same as above but without comments

class FreqStack {
    unordered_map<int, int> freqMap;
    vector<stack<int>> stacks;
    int maxFreq = 0;
public:
    FreqStack() {}
    
    void push(int val) {
        int currFreq = ++freqMap[val];
        if(stacks.size()<currFreq) stacks.push_back(stack<int>());
        stacks[currFreq-1].push(val);        
        maxFreq = max(maxFreq, currFreq);
    }
    
    int pop() {
        int maxFreqVal = stacks[maxFreq-1].top();
        stacks[maxFreq-1].pop();
        freqMap[maxFreqVal]--;
        if(stacks[maxFreq-1].empty()) maxFreq--;
        return maxFreqVal;
    }
};

