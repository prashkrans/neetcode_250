/*  LC#473. Matchsticks to Square

Special case of LC#698. Partition to K Equal Sum Subsets where k = 4, so refer to that problem for more details.

Three ways to solve this problem:
1.  Skip or take the current matchstick, we form a subset if current sum == target and then k is reduced by 1. 
    Continue to do this until k == 0. If k == 0, ans is true else false. [TODO]
2.  A polygon of k sides where all sides are equal and all the elements of the array are used
3.  DP with bit masking. [TODO]

### Hints:
1. For every matchstick, we have to try out each of the 4 options i.e. which side it can belong to. 
We can make use of recursion for this.

2. We don't really need to keep track of which matchsticks belong to a particular side during recursion. 
We just need to keep track of the length of each of the 4 sides.

3. When all matchsticks have been used we simply need to see the length of all 4 sides. 
If they're equal, we have a square on our hands!


### Approach 1: Backtracking with Pruning: A polygon of k = 4 side
1. Use a recursive function `rec` to try placing each matchstick on one of the 4 sides of the square.
2. Base cases:
   - If any side exceeds the target length, return false (prune invalid states).
   - If all matchsticks are used, check if all 4 sides are equal.
3. Recursive steps:
   - Try placing the current matchstick on each of the 4 sides and recurse.
   - If any placement leads to a valid solution, return true.
4. Optimization:
   - Sort the matchsticks in descending order to try larger matchsticks first, which helps prune invalid states earlier.

### Complexity:
- **Time Complexity**: O(4^n)
  - At each step, we have 4 choices to place the current matchstick.
- **Space Complexity**: O(n)
  - The recursion stack can go as deep as the number of matchsticks.

### Notes:
- Sorting the matchsticks in descending order improves performance by reducing unnecessary recursive calls.
- This approach ensures that all possible combinations are explored to form a square.
*/

// 1a. Backtracking without pruning or optimization
// Gets TLE at 10/195 for [1,2,3,4,5,6,7,8,9,10,5,4,3,2,1]

class Solution {
public:
    bool rec(int i, vector<int>& matchsticks, int side1, int side2, int side3, int side4) {
        if(i == matchsticks.size()) {
            return (side1 == side2 && side2 == side3 && side3 == side4);
        }
        return rec(i+1, matchsticks, side1 + matchsticks[i], side2, side3, side4)
            || rec(i+1, matchsticks, side1, side2 + matchsticks[i], side3, side4)
            || rec(i+1, matchsticks, side1, side2, side3 + matchsticks[i], side4)
            || rec(i+1, matchsticks, side1, side2, side3, side4 + matchsticks[i]); 
    }
    bool makesquare(vector<int>& matchsticks) {
        return rec(0, matchsticks, 0, 0, 0, 0);
    }
};

// 1b. Backtracking with one pruning or optimization
// Gets TLE at 177/195 for [1,2,3,4,5,6,7,8,9,10,5,4,3,2,1]

class Solution {
public:
    bool rec(int i, vector<int>& matchsticks, int side1, int side2, int side3, int side4, int targetSide) {
        if(side1 > targetSide || side2 > targetSide || side3 > targetSide || side4 > targetSide) return false;
        if(i == matchsticks.size()) {
            return (side1 == side2 && side2 == side3 && side3 == side4);
        }
        if (rec(i+1, matchsticks, side1 + matchsticks[i], side2, side3, side4, targetSide)) return true;
        if (rec(i+1, matchsticks, side1, side2 + matchsticks[i], side3, side4, targetSide)) return true;
        if (rec(i+1, matchsticks, side1, side2, side3 + matchsticks[i], side4, targetSide)) return true;
        if (rec(i+1, matchsticks, side1, side2, side3, side4 + matchsticks[i], targetSide)) return true;
        return false;
    }
    bool makesquare(vector<int>& matchsticks) {
        int sumOfAllSides = 0;
        for(int i=0; i<matchsticks.size(); i++) sumOfAllSides += matchsticks[i];
        if(sumOfAllSides % 4 != 0) return false;
        int targetSide = sumOfAllSides / 4;
        return rec(0, matchsticks, 0, 0, 0, 0, targetSide);
    }
};


// 1c. Backtracking with two pruning or optimization
// Passes all the test cases

class Solution {
public:
    bool rec(int i, vector<int>& matchsticks, int side1, int side2, int side3, int side4, int targetSide) {
        if(side1 > targetSide || side2 > targetSide || side3 > targetSide || side4 > targetSide) return false; // first optimization or path pruning
        if(i == matchsticks.size()) {
            return (side1 == side2 && side2 == side3 && side3 == side4);
        }
        if (rec(i+1, matchsticks, side1 + matchsticks[i], side2, side3, side4, targetSide)) return true;
        if (rec(i+1, matchsticks, side1, side2 + matchsticks[i], side3, side4, targetSide)) return true;
        if (rec(i+1, matchsticks, side1, side2, side3 + matchsticks[i], side4, targetSide)) return true;
        if (rec(i+1, matchsticks, side1, side2, side3, side4 + matchsticks[i], targetSide)) return true;
        return false;
    }
    bool makesquare(vector<int>& matchsticks) {
        int sumOfAllSides = 0;
        for(int i=0; i<matchsticks.size(); i++) sumOfAllSides += matchsticks[i];
        if(sumOfAllSides % 4 != 0) return false;
        int targetSide = sumOfAllSides / 4;     // first optimization or path pruning
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());   // second optimization or path pruning
        return rec(0, matchsticks, 0, 0, 0, 0, targetSide);
    }
};

// same as above but using a vector of size 4 to store the sides

// Time Complexity: O(4^n)
// - At each step, we have 4 choices to place the current matchstick on one of the 4 sides.
// - This results in a time complexity of O(4^n), where n is the number of matchsticks.

// Space Complexity: O(n)
// - The recursion stack can go as deep as the number of matchsticks, which is O(n).

class Solution {
public:
    bool rec(int i, vector<int>& matchsticks, vector<int> &sides, int targetSide) {
        for(int j = 0; j < 4; j++) {                     // Prune invalid states where any side exceeds the target length
            if(sides[j] > targetSide) return false;
        }
        if(i == matchsticks.size()) {                   // Base case: all matchsticks are used
            return (sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3]); // Check if all sides are equal
        }
        for(int j = 0; j < 4; j++) {                    // Try placing the current matchstick on each side
            sides[j] += matchsticks[i];                 // Add the current matchstick to side j
            if(rec(i + 1, matchsticks, sides, targetSide)) return true; // Recurse for the next matchstick
            sides[j] -= matchsticks[i];                 // Backtrack: remove the matchstick from side j
        }
        return false;                                   // If no valid placement is found, return false
    }

    bool makesquare(vector<int>& matchsticks) {
        int sumOfAllSides = 0;
        for(int i = 0; i < matchsticks.size(); i++) 
            sumOfAllSides += matchsticks[i];            // Calculate the total length of all matchsticks
        if(sumOfAllSides % 4 != 0) return false;        // If the total length is not divisible by 4, return false
        int targetSide = sumOfAllSides / 4;             // Calculate the target length for each side
        sort(matchsticks.begin(), matchsticks.end(), greater<int>()); // Sort matchsticks in descending order for optimization
        vector<int> sides(4, 0);                        // Initialize 4 sides with length 0
        return rec(0, matchsticks, sides, targetSide);  // Start the recursion
    }
};



class Solution {
public:
    bool rec(int i, vector<int>& matchsticks, vector<int> &sides, int targetSide) {
        for(int j=0; j<4; j++) if(sides[j] > targetSide) return false;
        if(i == matchsticks.size()) {
            for(int j=0; j<4; j++) if(sides[j] != targetSide) return false;
            return true;
        }
        for(int j=0; j<4; j++) {
            while(j>0 && sides[j] == sides[j-1]) continue;
            sides[j] += matchsticks[i];
            if(rec(i+1, matchsticks, sides, targetSide)) return true;
            sides[j] -= matchsticks[i];
        }
        return false;
    }
    bool makesquare(vector<int>& matchsticks) {
        int sumOfAllSides = 0;
        for(int i=0; i<matchsticks.size(); i++) sumOfAllSides += matchsticks[i];
        if(sumOfAllSides % 4 != 0) return false;

        int targetSide = sumOfAllSides / 4;
        for(int i=0; i<matchsticks.size(); i++) {
            if(matchsticks[i] > targetSide) return false;
        }

        sort(matchsticks.begin(), matchsticks.end(), greater<int>());
        vector<int> sides(4, 0);
        return rec(0, matchsticks, sides, targetSide);
    }
};