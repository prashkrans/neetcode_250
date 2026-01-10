/* LC#122. Best Time to Buy and Sell Stock II

Multiple approaches:
1. Recursion: O(2^n) 
2. DP (Top down): O(n) | TODO
3. DP (Bottom up): O(n)
4. DP (Space optimized): O(n)
5. Greedy: O(n) 
*/

/*
### Approach: Recursive Brute Force Exploration of Buy Sell Choices
1. Use recursion to explore every possible decision of buying, selling, or skipping on each day.
2. At each index, maintain whether buying is allowed and the current accumulated profit.
3. When buying is allowed, either buy the stock or skip the current day.
4. When holding a stock, either sell it or continue holding without selling.
5. Update maximum profit when all days have been processed.
6. This approach evaluates all possible transaction sequences without using memoization.
7. Exponential time complexity arises due to two choices at each day.
*/

// 1. Recursion (My original solution)
// Time Complexity: O(2^n) as we have two choices at each index 
// (buy or not buy if buying OR sell or not sell if not selling) | Gets TLE, 198/202 TCs passed
// Space Complexity: O(n) due to the recursion stack
// where n = prices.size();

class Solution {
    void rec(int i, vector<int> &prices, bool buying, int currProfit, int &maxProfit) {  // recursive helper to explore all choices
        if(i == prices.size()) {                                            // base case when all days are processed
            maxProfit = max(maxProfit, currProfit);                         // update maximum profit
            return;                                                         // terminate recursion
        }
        if(buying) {                                                        // decision when allowed to buy
            rec(i + 1, prices, false, currProfit - prices[i], maxProfit);   // choose to buy on current day
            rec(i + 1, prices, true, currProfit, maxProfit);                // skip buying on current day
        } else {                                                            // decision when holding stock
            rec(i + 1, prices, true, currProfit + prices[i], maxProfit);    // choose to sell on current day
            rec(i + 1, prices, false, currProfit, maxProfit);               // skip selling on current day
        }
    }

public:
    int maxProfit(vector<int>& prices) {                                    // function to compute maximum profit
        int currProfit = 0, maxProfit = 0;                                  // initialize profit trackers
        bool buying = true;                                                 // initially allowed to buy
        rec(0, prices, buying, currProfit, maxProfit);                      // start recursion from day zero
        return maxProfit;                                                   // return computed maximum profit
    }
};


/*
### Approach 5: Greedy Accumulation of Positive Differences
1. Traverse the price array once while comparing each consecutive pair of prices.
2. Compute the difference between next day price and current day price.
3. If the difference is positive, add it to the total profit since it represents a profitable transaction.
4. Ignore negative or zero differences because they do not contribute to profit.
5. This greedy strategy captures all increasing segments and sums their gains.
6. Multiple transactions are implicitly allowed without overlapping constraints.
7. Final accumulated sum represents the maximum profit achievable under given rules.
*/


// 5. Greedy Approach - This is the shortest code but to come up with this solution is tricky
// Time Complexity: O(n)
// Space Complexity: O(1)
// where n = prices.size()
// Hint: Since you can perform as many transactions as you like and even buy/sell on the same day, 
// you don't actually need to find the 'lowest valley' and 'highest peak' across the whole array. 
// You just need to capture every single upward price movement.


class Solution {
public:
    int maxProfit(vector<int>& prices) {                            // function to calculate maximum profit
        int res = 0;                                                // stores total accumulated profit
        for(int i = 0; i < prices.size() - 1; i++) {                // iterate through price list
            int currProfit = prices[i + 1] - prices[i];             // calculate daily profit
            if(currProfit > 0) res += currProfit;                   // add positive profit only
        }
        return res;                                                 // return maximum achievable profit
    }
};
