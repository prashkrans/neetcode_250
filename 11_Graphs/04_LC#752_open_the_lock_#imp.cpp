/* LC#752. Open the Lock

### Approach: Breadth-First Search (BFS)
1. Use BFS to explore all possible lock combinations starting from "0000".
2. Maintain a `visited` set to avoid revisiting combinations.
3. For each combination:
   - Generate all possible neighbors by moving each wheel up or down.
   - Skip neighbors that are in the `deadends` set or already visited.
   - If the target combination is reached, return the distance.
4. If the BFS completes without finding the target, return -1.

### Complexity:
Time Complexity: O(10^4) i.e. constant time
- The total number of possible lock combinations is 10^4 (0000 to 9999).
- Each combination has 8 neighbors (4 wheels with 2 possible moves each).
- BFS explores each combination at most once, resulting in O(10^4) complexity.

Space Complexity: O(10^4) i.e. constant space
- The `visited` map and the queue can store up to 10^4 combinations.

### Notes:
- This approach ensures that the shortest path to the target is found using BFS.
- The use of modular arithmetic simplifies the wheel movement logic.
*/

// 1a. BFS (My custom code) Same as 1b but using a map instead of math for switching dials
// Prefe this code

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> deadendsSet = {deadends.begin(), deadends.end()};
        if(deadendsSet.find("0000") != deadendsSet.end()) return -1;
        if(target=="0000") return 0;
        unordered_map<char, string> mp;
        mp['0'] = "91";     mp['1'] = "02";
        mp['2'] = "13";     mp['3'] = "24";
        mp['4'] = "35";     mp['5'] = "46";
        mp['6'] = "57";     mp['7'] = "68";
        mp['8'] = "79";     mp['9'] = "80";
        queue<string> q;
        unordered_map<string, int> visited;
        q.push("0000");
        visited["0000"] = 1;
        int dist = 1;
        while(!q.empty()) {
            int qSize = q.size();
            for(int i=0; i<qSize; i++) {
                string u = q.front();
                q.pop();
                for(int i=0; i<4; i++) {
                    for(int j=0; j<2; j++) {
                        string v = u;
                        v[i] = mp[u[i]][j];
                        if(!visited[v] && deadendsSet.find(v) == deadendsSet.end()) {
                            if(v == target) return dist;
                            q.push(v);
                            visited[v] = 1;
                        }
                    }
                }
            }
            dist++;
        }
        return -1;
    }
};

// 1b. BFS 

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> deadendsSet(deadends.begin(), deadends.end());    // Convert deadends to a set for O(1) lookups
        if(deadendsSet.find("0000") != deadendsSet.end()) return -1;            // If the initial state is a deadend, return -1
        if(target == "0000") return 0;                                          // If the target is the initial state, return 0

        queue<string> q;                                                        // BFS queue
        unordered_set<string> visited;                                          // Set to track visited combinations
        q.push("0000");
        visited.insert("0000");
        int dist = 0;                                                           // Distance from the initial state

        while(!q.empty()) {
            int qSize = q.size();
            for(int i = 0; i < qSize; i++) {
                string u = q.front();
                q.pop();
                if(u == target) return dist;                                    // If the target is reached, return the distance
                for(int j = 0; j < 4; j++) {                                    // Iterate through each wheel
                    for(int d = -1; d <= 1; d += 2) {                           // Move the wheel up or down
                        string v = u;
                        v[j] = (v[j] - '0' + d) + '0';                          // Calculate the new digit
                        if(!visited.count(v) && !deadendsSet.count(v)) {        // If not visited and not a deadend
                            q.push(v);
                            visited.insert(v);                                  // Mark as visited
                        }
                    }
                }
            }
            dist++;                                                             // Increment the distance after processing a level
        }
        return -1;                                                              // If the target is not reachable, return -1
    }
};

/*
### Why add 10 before mod 10?

1. **Circular Nature of the Lock:**
   - Each wheel has digits from 0 to 9.
   - Moving down from 0 wraps around to 9, and moving up from 9 wraps around to 0.

2. **Handling Negative Values:**
   - When moving down (e.g., -1), the calculation `(current_digit + d)` can result in a negative value.
   - Example: If `current_digit = 0` and `d = -1`, the result is `-1`, which is invalid.

3. **Adding 10:**
   - Adding 10 ensures the result is always non-negative.
   - Example: `(0 + -1 + 10) % 10 = 9`.

4. **Modulo 10:**
   - After adding 10, the modulo operation ensures the result stays within the range [0, 9].
   - Example: `(9 + 1 + 10) % 10 = 0`.

5. **Final Conversion:**
   - Add `'0'` to convert the numeric result back to a character.
   - Example: `9 -> '9'`.

### Summary:
Adding 10 ensures proper handling of negative values and maintains the circular behavior of the lock's dials.
*/