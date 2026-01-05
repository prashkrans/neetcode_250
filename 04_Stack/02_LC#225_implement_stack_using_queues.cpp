/*  LC#225. Implement Stack using Queues
There are two methods:
1. Using two queues
2. Using one queue
*/
/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

/*
### Approach 1: Implement Stack Using Two Queues (Easier to Understand)
1. Maintain two queues (primary - q1 and helper - q2) where one queue always
stores elements in stack order, ensuring top element remains at the front.
2. During push operation
    a.  insert new element into helper queue first,
        then move all elements from primary queue into helper queue.
    b.  This rearrangement guarantees the newest element is always placed
        at the front, simulating stack behavior.
    c.  Swap the primary and helper queues after rearranging to reset
        state for next operations.
3. Pop operation removes the front element of the primary queue,
which represents the stack top.
4. Top operation simply returns the front element without removal.
5. Empty operation checks whether the primary queue has zero elements.
*/


// Method 1: Using two queues
// Time Complexity: push -> O(n), pop -> O(1), top -> O(1), empty -> O(1) | 0ms (100.00%)
// Space Complexity: O(2n) ~ O(n) due to usage of two queues

class MyStack {
    queue<int> q1;                                                // primary queue storing stack order
    queue<int> q2;                                                // helper queue for reordering
public:
    MyStack() {}                                                  // constructor initializes empty stack
    
    void push(int x) {
        q2.push(x);                                               // push new element into helper queue
        while(!q1.empty()) {                                      // move all existing elements
            q2.push(q1.front());                                  // push front of q1 into q2
            q1.pop();                                             // remove front element from q1
        }
        queue<int> temp = q1;                                     // temporary queue for swapping
        q1 = q2;                                                  // assign reordered queue to q1
        q2 = temp;                                                // reset q2 for next operation
    }
    
    int pop() {
        int topVal = q1.front();                                  // store top element
        q1.pop();                                                 // remove top element
        return topVal;                                            // return popped value
    }
    
    int top() {
        int topVal = q1.front();                                  // access top element
        return topVal;                                            // return top value without removal
    }
    
    bool empty() {
        return q1.empty();                                        // check if stack is empty
    }
};

/*
### Approach 2: Stack Simulation Using Single Queue Rotation
CLASS StackUsingOneQueue:
    INITIALIZE queue

    PROCEDURE Push(element): (If 2. before 1. then repeat n-1 times only)
        1. Get current size of queue as 'n' before adding the element
        2. Enqueue 'element' into the queue
        3. REPEAT 'n' times:
            a. Dequeue front element
            b. Enqueue that same element back into the queue
        
    PROCEDURE Pop():
        1. IF queue is empty:
            RETURN error (Underflow)
        2. Dequeue and return front element

    PROCEDURE Top():
        1. IF queue is empty:
            RETURN error
        2. Return front element without removing it

    PROCEDURE IsEmpty():
        1. Return True if queue size is 0, else False
*/


// Method 2: Using a single queue
// Time Complexity: push -> O(n), pop -> O(1), top -> O(1), empty -> O(1) | 0ms, beats 100% 
// Space Complexity: O(n)

class MyStack {
    queue<int> q;                                                  // single queue to simulate stack
public:
    MyStack() {}                                                   // constructor initializes empty stack

    void push(int x) {
        q.push(x);                                                 // insert new element into queue
        for(int i=0; i<q.size()-1; i++) {                          // rotate previous elements | Note: We enqueue-dequeue n-1 times (not n times)
            int frontVal = q.front();                              // store front element
            q.pop();                                               // dequeue front element
            q.push(frontVal);                                      // enequeue stored element to back
        }
    }

    int pop() {
        int topVal = q.front();                                    // store top stack element
        q.pop();                                                   // remove top element
        return topVal;                                             // return popped value
    }

    int top() {
        return q.front();                                          // return top element without removal
    }

    bool empty() {
        return q.empty();                                          // check whether stack is empty
    } 

};

/* Explanation:
Step-by-Step: 
Pushing Element 'C'
1. Get Current SizeThe queue currently has 2 elements ($n = 2$).
2. Enqueue New ElementAdd C to the rear of the queue.Queue: [B, A, C] (C is at the back, but for a stack, it needs to be at the front).
3. Rotate Previous Elements ($n$ times)Since $n = 2$, we perform the dequeue-enqueue cycle twice:
    Rotation 1: Dequeue B from the front and Enqueue it to the rear.Queue becomes: [A, C, B]
    Rotation 2: Dequeue A from the front and Enqueue it to the rear.Queue becomes: [C, B, A]
*/