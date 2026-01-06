/* LC#901. Online Stock Span
/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

 /*
/*
### Approach 1: Monotonic Decreasing Stack for Stock Span Calculation (Best Approach)
1. Maintain a monotonic decreasing stack storing pairs of stock price and its computed span.
2. Each stack entry represents a price and the number of consecutive days it dominates.
3. For each new price, initialize span as one for current day.
4. While stack is not empty and top price is less than or equal to current price, pop stack entries.
5. Add each popped entry span values to current span to merge consecutive dominated days.
6. Push current price and its accumulated span onto stack.
7. Each price is pushed and popped at most once, resulting in amortized constant time per operation.
*/


// Time Complexity: next -> amortized O(1) but overall O(n) | 30ms, beats 60.54%
// Space Complexity: O(n)
// where n is the number of calls to next()

class StockSpanner {
    stack<pair<int, int>> st;                                       // monotonic stack storing price and span
public:
    StockSpanner() {}                                               // constructor initializes empty stack
    
    int next(int price) {                                           // Note: No need to check for empty stack separately
        int span = 1;                                               // initial span includes current day
        while(!st.empty() && st.top().first <= price) {             // pop while previous prices are smaller
            span += st.top().second;                                // accumulate span of popped prices
            st.pop();                                               // remove processed entry
        }
        st.push({price, span});                                     // push current price with its span
        return span // or return st.top().second;                   // return calculated span
    }
};


class StockSpanner {
    stack<pair<int, int>> st;
public:
    StockSpanner() {}
    
    int next(int price) {
        int span = 1;
        while(!st.empty() && st.top().first <= price) {
            span += st.top().second;
            st.pop();
        }
        st.push({price, span});
        return st.top().second;
    }
};

// Same as above with minor variation that shows explicit handling of empty stack

class StockSpanner {
    stack<pair<int, int>> st;
public:
    StockSpanner() {}
    
    int next(int price) {
        int span = 1;
        if(st.empty()) {        // this gets implicitly handled by while loop below, but kept for clarity
            st.push({price, span});
        }
        else {
            while(!st.empty() && st.top().first <= price) {
                span += st.top().second;
                st.pop();
            }
            st.push({price, span});
        }
        return st.top().second;
    }
};


/*
### Approach 2: Brute Force Backward Scan for Stock Span
1. Maintain a vector to store all previously seen stock prices in chronological order.
2. For each new price, initialize span as one representing the current trading day.
3. Traverse the stored prices backward starting from the most recent previous day.
4. Increment span for every consecutive price that is less than or equal to the current price.
5. Stop traversal immediately when a higher price is encountered, since span condition breaks.
6. Append the current price to the history vector for use in future span calculations.
7. This direct comparison approach computes span correctly but may take linear time per query.
*/


// Method 2: My brute force approach using vector to store historical prices (Not an optimal solution, 17 minutes)
// Time Complexity: next -> O(n) but overall O(n^2) | 520ms, beats 5.09%
// Space Complexity: O(n)
// where n is the number of calls to next()

class StockSpanner {
    vector<int> hist;                                             // stores historical stock prices
public:
    StockSpanner() {}                                              // constructor initializes empty history
    
    int next(int price) {
        int span = 1;                                              // minimum span includes current day
        for(int i = hist.size() - 1; i >= 0; i--) {                // iterate backwards through history
            if(hist[i] <= price) span++;                           // extend span while prices are smaller
            else break;                                            // stop when higher price is found
        }
        hist.push_back(price);                                     // store current price in history
        return span;                                               // return calculated stock span
    }
};

