/* LC#860. Lemonade Change

Got it right the first try (use pen and paper)

### Approach: Greedy Counting of Bills with 3 Main Cases and Subcases
1. Maintain counters for $5 and $10 bills, as only these are used for change; we never give back $20 bills.
2. Process each customer's bill by classifying it into one of the three main cases:
3. Case 1: Customer pays with $5
   a. No change needed; simply increment the count of $5 bills.
4. Case 2: Customer pays with $10
   a. Subcase 1: If at least one $5 bill is available, give one $5 as change.
   b. Subcase 2: If no $5 bill is available, return false (cannot give correct change).
5. Case 3: Customer pays with $20
   a. Subcase 1: Prefer to give one $10 and one $5 as change (optimal strategy to save $5s).
   b. Subcase 2: If no $10 but at least three $5 bills are available, give three $5s.
   c. Subcase 3: If neither combination is possible, return false (cannot give correct change).
6. This greedy approach always chooses the optimal path to preserve small denomination bills for future change.
7. The function returns true if all customers are served successfully; otherwise, it returns false as soon as change fails.
8. The algorithm runs in O(n) time and uses O(1) space, where n is the number of customers.
*/

// 1. Greedy Counting of Bills
// Time Complexity: O(n)                                                 // Traverse the bills array once
// Space Complexity: O(1)                                                // Only uses a fixed amount of extra space for counters

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int numOfFives = 0, numOfTens = 0;                               // Counters for $5 and $10 bills
        for(int i=0; i<bills.size(); i++) {
            if(bills[i] == 5) numOfFives++;                              // Collect $5 bill, no change needed
            else if(bills[i] == 10) {
                if(numOfFives > 0) {                                     // Can give $5 as change
                    numOfFives--;                                       // Use one $5 bill
                    numOfTens++;                                        // Collect one $10 bill
                }
                else return false;                                      // No $5 bill available for change
            }
            else if(bills[i] == 20) {
                if(numOfTens > 0) {                                      // Prefer to give one $10 and one $5 as change
                    numOfTens--;                                        // Use one $10 bill
                    if(numOfFives > 0) numOfFives --;                   // Use one $5 bill if available
                    else return false;                                  // No $5 bill to pair with $10
                }
                else {
                    if(numOfFives > 2) numOfFives -= 3;                 // Use three $5 bills if no $10 bill
                    else return false;                                  // Not enough $5 bills for $15 change
                }
            }
        }
        return true;                                                    // All customers received correct change
    }
};

// or, same as above but without comments

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int numOfFives = 0, numOfTens = 0;
        for(int i=0; i<bills.size(); i++) {
            if(bills[i] == 5) numOfFives++;
            else if(bills[i] == 10) {
                if(numOfFives > 0) {
                    numOfFives--;
                    numOfTens++;
                }
                else return false;
            }
            else if(bills[i] == 20) {
                if(numOfTens > 0) {
                    numOfTens--;
                    if(numOfFives > 0) numOfFives --;
                    else return false;
                }
                else {
                    if(numOfFives > 2) numOfFives -= 3;
                    else return false;
                }
            }
        }
        return true;
    }
};