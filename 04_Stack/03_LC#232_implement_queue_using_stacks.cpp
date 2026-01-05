/* LC#232. Implement Queue using Stacks

### Approach 1: Queue Implementation Using Two Stacks
1. Use two stacks where primary stack stores elements and helper stack
temporarily reverses order to simulate queue behavior.
2. Push operation inserts elements directly into the primary stack
since order does not matter initially.
3. For pop operation, transfer all elements from primary stack to
helper stack to reverse their order.
4. The top of helper stack represents the front of the queue and
is removed as dequeue operation.
5. Remaining elements are transferred back to primary stack to
restore original ordering.
6. Peek operation follows similar transfer logic but does not remove
the front element.
7. Empty operation checks whether the primary stack contains no elements.
*/


// Method 1: Using two stacks (my method)
// Time Complexity: push -> O(1), pop -> O(2n) ~ O(n), peek -> O(2n) ~ O(n), empty -> O(1) | 0ms, beats 100%
// Space Complexity: O(2n) ~ O(n)

class MyQueue {
    stack<int> s1;                                                // primary stack for push operations
    stack<int> s2;                                                // helper stack for reversing order
public:
    MyQueue() {}                                                   // constructor initializes empty queue
    
    void push(int x) {
        s1.push(x);                                                // push element onto primary stack
    }
    
    int pop() {
        while(!s1.empty()) {                                      // move all elements to helper stack
            s2.push(s1.top());                                    // push top of s1 into s2
            s1.pop();                                             // remove top element from s1
        }
        int frontVal = s2.top();                                  // store front element of queue
        s2.pop();                                                 // remove front element
        while(!s2.empty()) {                                      // move remaining elements back
            s1.push(s2.top());                                    // restore elements to s1
            s2.pop();                                             // remove element from s2
        }
        return frontVal;                                          // return removed front element
    }
    
    int peek() {
        while(!s1.empty()) {                                      // move elements to helper stack
            s2.push(s1.top());                                    // reverse order of elements
            s1.pop();                                             // pop from primary stack
        }
        int frontVal = s2.top();                                  // read front element without removal
        while(!s2.empty()) {                                      // restore original stack order
            s1.push(s2.top());                                    // push elements back to s1
            s2.pop();                                             // clear helper stack
        }
        return frontVal;                                          // return front element
    }
    
    bool empty() {
        return s1.empty();                                        // check if queue has no elements
    }
};

/*
### Approach 2: Amortized Queue Implementation Using Two Stacks
1. Use two stacks where one stack handles enqueue operations and the 
other stack handles dequeue operations instead of primary and helper stacks.
2. Push elements directly into the input stack, allowing
constant time insertion.
3. For pop or peek operations, check if output stack (s2) is empty
before transferring elements.
4. If output stack (s2) is empty, move all elements from input stack (s1)
to output stack (s2), reversing their order.
5. This reversal ensures the oldest element becomes accessible
at the top of output stack (s2).
6. If output stack (s2) already contains elements, directly perform
pop or peek without additional transfers.
7. Each element is transferred at most once between stacks,
resulting in amortized O(1) time per operation.
*/


// Method 2: Using two stacks but amortized O(1) pop and peek

// Time Complexity: push -> O(1), pop -> amortized O(1), peek -> amortized O(1), empty -> O(1) | 0ms, beats 100%
// Space Complexity: O(2n) ~ O(n)

class MyQueue {
    stack<int> s1;                                                // stack used for enqueue operations
    stack<int> s2;                                                // stack used for dequeue operations
public:
    MyQueue() {}                                                   // constructor initializes empty queue
    
    void push(int x) {
        s1.push(x);                                                // push element into input stack
    }
    
    int pop() {
        if(s2.empty()) {                                          // check if output stack is empty
            while(!s1.empty()) {                                  // transfer elements if needed
                s2.push(s1.top());                                // move top element to output stack
                s1.pop();                                         // remove element from input stack
            }
        }
        int frontVal = s2.top();                                  // store front element of queue
        s2.pop();                                                 // remove front element
        return frontVal;                                          // return dequeued value
    }
    
    int peek() {
        if(s2.empty()) {                                          // ensure output stack has elements
            while(!s1.empty()) {                                  // transfer elements if required
                s2.push(s1.top());                                // reverse order using stack
                s1.pop();                                         // pop element from input stack
            }
        }
        return s2.top();                                          // return front element without removal
    }
    
    bool empty() {
        return s1.empty() && s2.empty();                          // check if both stacks are empty
    }
};
