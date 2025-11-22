/* All Jump Game Problems (I to VII) Solution with BFS 

Not all Jump Game Problems could be solved using BFS but all could be solve using DP
For a few problems even DP soluton gives TLE/MLE even though its correct since it needs further optimizations like
using deque or a max head along with DP

BFS Template:
    - Convert the given array and the jump constraint into an undirected and unweighted graph
    - source = 0th index (generally)
    - dest = last index i.e n-1 (generally)
    - queue<int> to store indices
    - vector<int> visited(n, 0) to mark indices as visited
    - relation that defines v where v is a neighbour of u [#IMP]
    - either return reachability i.e. bool or return distance i.e. int
    - when returning dist use for loop inside the BFS while loop where int qSize = q.size() and i varies from 0 to qSize - 1
      [#IMP] i varies from 0 to qSize not q.size() which keeps changing

Example template structure: source is usually 0 and dest is usually n-1 

// For reachability check:
bool canReach(vector<int>& arr) {
    int n = arr.size();
    queue<int> q;
    vector<int> visited(n, 0);
    
    q.push(source);
    visited[source] = 1;
    
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        
        // Check if destination reached
        if(u == dest) return true;
        
        // Find all neighbors of u according to problem constraints
        for(each neighbor v of u) {
            if(!visited[v]) {
                visited[v] = 1;
                q.push(v);
            }
        }
    }
    return false;
}

// For distance calculation:
int minDistance(vector<int>& arr) {
    int n = arr.size();
    queue<int> q;
    vector<int> visited(n, 0);
    
    q.push(source);
    visited[source] = 1;
    int dist = 0;
    
    while(!q.empty()) {
        int qSize = q.size();
        for(int i = 0; i < qSize; i++) {
            int u = q.front();
            q.pop();
            
            // Check if destination reached
            if(u == dest) return dist;
            
            // Find all neighbors of u according to problem constraints
            for(each neighbor v of u) {
                if(!visited[v]) {
                    visited[v] = 1;
                    q.push(v);
                }
            }
        }
        dist++;
    }
    return -1; // If destination cannot be reached
}


Note:
- Important to use visited array else would get MLE
- Important to use path pruning (farthest) in some cases to avoid TLE
- If initializing dist = 0, return dist after popping n-1 else if initializing dist = 1, 
  return dist after marking n-1 as visited (Prefer the latter)
- return -1 at last: although its usually guaranteed that an ans always exist

*/



/* 01. LC#55. Jump Game
*/
// BFS
// O(n) as each index is visited at most once.
// O(n) due to the queue and visited array

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return true; // Given n > 0 and nums[i] >= 0
        queue<int> q;
        vector<int> visited(n, 0);
        q.push(0);
        visited[0] = 1;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            if(nums[u] > 0) {
                for(int v=u+1; v<=u+nums[u] && v<n; v++) {
                    if(!visited[v]) {
                        q.push(v);
                        visited[v] = 1;
                        if(v == n-1) return true;
                    }
                }
            }
        }
        return false;
    }
};

/* 02. LC#45. Jump Game II
*/
// BFS
// O(n) as each index is visited at most once.
// O(n) due to the queue and visited array

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return 0; // Given n > 0 and nums[i] >= 0
        queue<int> q;
        vector<int> visited(n, 0);
        int dist = 1;
        q.push(0);
        visited[0] = 1;
        while(!q.empty()) {
            int qSize = q.size();
            for(int i=0; i<qSize; i++) {
                int u = q.front();
                q.pop();
                if(nums[u] > 0) {
                    for(int v=u+1; v<=u+nums[u] && v<n; v++) {
                        if(!visited[v]) {
                            q.push(v);
                            visited[v] = 1;
                            if(v == n-1) return dist;
                        }
                    }
                }
            }
            dist++;
        }
        return -1;
    }
};

/* 03. LC#1306. Jump Game III
*/
// BFS
// O(n) as each index is visited at most once.
// O(n) due to the queue and visited array

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        if(arr[start] == 0) return true;
        vector<int> visited(n, 0);
        queue<int> q;
        q.push(start);
        visited[start] = 1;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            vector<int> dirs = {arr[u], -arr[u]};
            for(int i=0; i<2; i++) {
                int v = u + dirs[i];
                if(v>=0 && v<n && !visited[v]) {
                    q.push(v);
                    visited[v] = true;
                    if(arr[v] == 0) return true;
                }
            }
        }
        return false;
    }
};

/* 04. 1345. Jump Game IV

### Approach: Breadth-First Search with Value Bucketing
1. Build a map from each value to all its indices to enable O(1) lookup for same-value jumps, a key optimization.
2. Use a breadth-first search (BFS) to explore the array starting from index 0, tracking visited indices to avoid cycles.
3. At each step, enqueue the left neighbor, right neighbor, and all same-value indices that haven't been visited.
4. Same-value connections are removed from the map once used, to reduce redundant future lookups and improve performance.
5. Each BFS level corresponds to one jump; the first time we reach the last index, we return the current level as result.
6. This ensures minimal jumps are found due to level-wise traversal, with O(n) time guaranteed by single-use of edges.
*/

// BFS without path pruning
// Correct Solution but gives Time Limit Exceeded at 21/33


class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if(n == 1) return 0;
        queue<int> q;
        vector<int> visited(n, 0);
        q.push(0);
        visited[0] = 1;
        int dist = 1;
        while(!q.empty()) {
            int qSize = q.size();
            for(int i=0; i<qSize; i++) {
                int u = q.front();
                q.pop();
                unordered_set<int> nbrs;
                int v = u - 1;
                if(v >=0 && !visited[v]) nbrs.insert(v);
                v = u + 1;
                if(v < n && !visited[v]) nbrs.insert(v);
                for(v = 0; v < n; v++) {
                    if(v != u && arr[u] == arr[v] && !visited[v]) nbrs.insert(v);
                }
                for(auto v: nbrs) {
                    q.push(v);
                    visited[v];
                    if(v == n-1) return dist;
                }
            }
            dist++;
        }
        return -1;
    }
};

// BFS without path pruning
// Same as above but reducing look up time from O(n) to O(max no. of times a value is repeated) ~ O(n) in the worst case
// Correct Solution but gives Time Limit Exceeded at 21/33
class Solution {
    public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if(n == 1) return 0;
        unordered_map<int, vector<int>> sameValueIndices;
        for(int i=0; i<n; i++) sameValueIndices[arr[i]].push_back(i);

        queue<int> q;
        vector<int> visited(n, 0);
        q.push(0);
        visited[0] = 1;
        int dist = 1;
        while(!q.empty()) {
            int qSize = q.size();
            for(int i=0; i<qSize; i++) {
                int u = q.front();
                q.pop();
                unordered_set<int> unvisitedNbrs;
                int v = u - 1;
                if(v >=0 && !visited[v]) unvisitedNbrs.insert(v);
                v = u + 1;
                if(v < n && !visited[v]) unvisitedNbrs.insert(v);
                if(sameValueIndices.count(arr[u])) {
                    for(auto v: sameValueIndices[arr[u]]) {
                        if(v != u && !visited[v]) unvisitedNbrs.insert(v);
                    }
                }
                for(auto v: unvisitedNbrs) {
                    q.push(v);
                    visited[v]=1;
                    if(v == n-1) return dist;
                }
            }
            dist++;
        }
        return -1;
    }
};

// BFS with path pruning or optimizatin (Prefer this method)
// same as above but using key optimization i.e. erasing the duplicate indices list for a value if done visiting it
// passes all the test cases
// Time Complexity: O(n) where n is the length of the input array
// Space Complexity: O(n) for visited array, hashmap, and queue

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();                                         // Get the size of the array
        if(n == 1) return 0;                                        // No jump needed if array has only one element
        unordered_map<int, vector<int>> sameValueIndices;           // Map value to all its indices
        for(int i=0; i<n; i++) sameValueIndices[arr[i]].push_back(i);  // Store all indices for each unique value

        queue<int> q;                                               // Queue for BFS traversal
        vector<int> visited(n, 0);                                  // To track visited indices
        q.push(0);                                                  // Start from index 0
        visited[0] = 1;                                             // Mark index 0 as visited
        int dist = 0;                                               // Initialize jump count

        while(!q.empty()) {                                         // BFS loop
            int qSize = q.size();                                   // Number of elements at current level
            for(int i=0; i<qSize; i++) {
                int u = q.front();                                  // Current index being explored
                q.pop();
                if(u == n-1) return dist;                           // If reached end, return current distance
                
                unordered_set<int> unvisitedNbrs;                   // To collect unvisited neighbors    
                int v = u - 1;                                      // Check left neighbor
                if(v >=0 && !visited[v]) unvisitedNbrs.insert(v);   // Add if not visited

                v = u + 1;                                          // Check right neighbor
                if(v < n && !visited[v]) unvisitedNbrs.insert(v);   // Add if not visited

                if(sameValueIndices.count(arr[u])) {                // Check same-value jump possibilities
                    for(auto v: sameValueIndices[arr[u]]) {         // Traverse indices with same value
                        if(v != u && !visited[v]) unvisitedNbrs.insert(v); // Avoid self-loop and add unvisited
                    }
                    sameValueIndices.erase(arr[u]);                 // [#IMP] Key optimization to prevent revisiting
                }

                for(auto v: unvisitedNbrs) {                        // Enqueue all valid unvisited neighbors
                    q.push(v);
                    visited[v] = 1;                                 // Mark as visited
                }
            }
            dist++;                                                 // Increase jump count after each level
        }
        return -1;                                                  // If unreachable, return -1
    }
};
    
/* 08. LC#1340. Jump Game V
Not Optimal to solve this using BFS since its DAG
Use DP

Note: res = 1 not 0 as min value could be 1 not 0

### Approach: Depth-First Search with Bounded Monotonic Jumps
1. The algorithm performs a recursive depth-first search (DFS) from each index in the array to explore valid jump paths.
2. A jump from index i to j is valid only if arr[j] < arr[i] and j is within distance d from i either to left or right.
3. For each valid jump, the function rec is called recursively, calculating the longest path starting at the destination.
4. The maximum result from all possible directions is tracked using a local variable and compared via max().
5. The search breaks early in each direction once an element is found that is greater than or equal to the current one.
6. This ensures only strictly decreasing sequences are considered, which is key to the correctness of the approach.
7. Final result is the max value over all starting points, giving the longest possible valid jump sequence in the array.
*/

// Rec without memo:
// O(n*(2d)^n)
// O(n) since recursion stack depth could be atmost n

// Time Complexity: O(n*(2d)^n) worst case
// - We start from each of the n indices, so O(n) starting points
// - At each step, we can make up to 2d jumps (d to the left + d to the right)
// - The recursion depth can go up to n in worst case
// - This gives us O(n*(2d)^n) as the overall complexity
// - Without memoization, we might recompute the same subproblems multiple times
// - This can be improved to O(n * d) with memoization

// Space Complexity: O(n)
// - Recursion stack depth could be at most n in the worst case
// - This happens when we have a strictly decreasing array and each recursive call leads to another call
// - Each recursive call uses O(1) extra space, leading to O(n) total space from the call stack

class Solution {
    int rec(int i, vector<int> &arr, int d) {
        const int n = arr.size();                                // Get size of array
        if(i < 0 || i >= n) return 0;                            // Base case: out of bounds
        int res = 1;                                             // Minimum jump length from this index is 1 (itself)
        for(int j=i+1; j<=i+d && j<n; j++) {                     // Explore right within max distance d
            if(arr[j] >= arr[i]) break;                          // Can't jump to higher or equal value
            res = max(res, 1 + rec(j, arr, d));                  // Recursive jump and update max
        }
        for(int j=i-1; j>=i-d && j>=0; j--) {                    // Explore left within max distance d
            if(arr[j] >= arr[i]) break;                          // Stop if not strictly decreasing
            res = max(res, 1 + rec(j, arr, d));                  // Update max jump length
        }
        return res;                                              // Return max reachable jump length from index i
    }
public:
    int maxJumps(vector<int>& arr, int d) {
        int ans = 1; // since arr.size() >0                      // Initialize answer to at least 1
        for(int i=0; i<arr.size(); i++) {                        // Try jumping from every index
            ans = max(ans, rec(i, arr, d));                      // Update max result
        }
        return ans;                                              // Return maximum of all start points
    }
};


// Rec with memo: (Prefer this method)
// O(n*n*d) = O(n^2*d)
// O(n) due to the dp array and recursion stack depth

class Solution {
    int rec(int i, vector<int> &arr, int d, vector<int> &dp) {
        const int n = arr.size();
        if(i < 0 || i >= n) return 0;
        if(dp[i] != -1) return dp[i];
        int res = 1;
        for(int j=i+1; j<=i+d && j<n; j++) {
            if(arr[j] >= arr[i]) break;
            res = max(res, 1 + rec(j, arr, d, dp));
        }
        for(int j=i-1; j>=i-d && j>=0; j--) {
            if(arr[j] >= arr[i]) break;
            res = max(res, 1 + rec(j, arr, d, dp));
        }
        return dp[i] = res;
    }
public:
    int maxJumps(vector<int>& arr, int d) {
        const int n = arr.size();
        int ans = 0;
        vector<int> dp(n, -1);
        for(int i=0; i<arr.size(); i++) {
            ans = max(ans, rec(i, arr, d, dp));
        }
        return ans;
    }
};

// Bottom up DP (in order of increasing height) (Yet to understand fully)
class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        const int n = arr.size();
        
        // Pair of (height, index)
        vector<pair<int, int>> heightIndex;
        for (int i = 0; i < n; i++) {
            heightIndex.push_back({arr[i], i});
        }
        
        // Sort by height
        sort(heightIndex.begin(), heightIndex.end());
        
        // DP array: dp[i] represents max jumps starting from index i
        vector<int> dp(n, 1); // default value of 1 not 0
        
        // Process in order of increasing height
        for (auto [height, i] : heightIndex) {
            // Check right jumps
            for (int j = i + 1; j <= min(i + d, n - 1); j++) {
                if (arr[j] >= height) break;
                dp[i] = max(dp[i], 1 + dp[j]);
            }
            
            // Check left jumps
            for (int j = i - 1; j >= max(0, i - d); j--) {
                if (arr[j] >= height) break;
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};

/* 06. LC# Jump Game VI
Note: Rec without memo, rec with memo, reversed Dijkstra's algo, get TLE here since k can be as large as 10^5
Acceptable solutions:
1. Using a pq and DP (Prefer this method)
2. Using a deque and DP
*/

// 1. Rec without memo
// Gets TLE at 58/73
class Solution {
    int rec(int i, vector<int> &nums, int k) {
        int n = nums.size();
        if(i==n-1) return nums[n-1]; // Base case of if(i==n) return 0; is incorrect
        int res = INT_MIN;
        for(int j=i+1; j<=min(i+k, n-1); j++) {
            res = max(res, rec(j, nums, k));
        }
        return (res == INT_MIN) ? INT_MIN : nums[i] + res;
    }
public:
    int maxResult(vector<int>& nums, int k) {
        return rec(0, nums, k);
    }
};

// 2. Rec with memo:
// Gets TLE at 58/73 | Since k can be as large as 10^5 we are iterating j = i + 1 to j = min(i + k, n - 1) for each i

class Solution {
    int rec(int i, vector<int> &nums, int k, vector<int> &dp) {
        int n = nums.size();
        if(i==n-1) return dp[n-1] = nums[n-1]; // Base case of if(i==n) return 0; is incorrect
        if(dp[i] != -1) return dp[i];
        int res = INT_MIN;
        for(int j=i+1; j<=min(i+k, n-1); j++) {
            res = max(res, rec(j, nums, k, dp));
        }
        return dp[i] = (res == INT_MIN) ? INT_MIN : nums[i] + res;
    }
public:
    int maxResult(vector<int>& nums, int k) {
        vector<int> dp(nums.size(), -1);
        return rec(0, nums, k, dp);
    }
};

// Rec with memo:
// Gets Memory Limit Exceeded at 58/73 (not TLE) | Since k can be as large as 10^5

class Solution {
    int rec(int i, vector<int> &nums, int k,  vector<vector<int>> &dp) {
        int n = nums.size();
        if(i==n-1) return dp[n-1][k] = nums[n-1]; // Base case of if(i==n) return 0; is incorrect
        if(dp[i][k] != -1) return dp[i][k];
        int res = INT_MIN;
        for(int j=i+1; j<=min(i+k, n-1); j++) {
            res = max(res, rec(j, nums, k, dp));
            dp[i][j-i] = res;
        }
        return dp[i][k] = (res == INT_MIN) ? INT_MIN : nums[i] + res;
    }
public:
    int maxResult(vector<int>& nums, int k) {
        vector<vector<int>> dp(nums.size(), vector<int>(k+1, -1));
        return rec(0, nums, k, dp);
    }
};

// Rec with memo (space optimized using a heap):
// dist is dp array which needs to be maximized
// Reverse Dijktra's algo
// Gets TLE at 5/73

class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<pair<int, int>> pq; // maxHeap i.e. Reversed Dijkstra's Algo
        vector<int> dist(n, INT_MIN);

        dist[0] = nums[0];
        pq.push({dist[0], 0});

        while(!pq.empty()) {
            pair<int, int> p = pq.top();
            pq.pop();
            int u = p.second;
            int wt = p.first;

            for(int v=u+1; v<n && v<=u+k; v++) {
                if(dist[v] < nums[v] + dist[u]) {
                    dist[v] = nums[v] + dist[u];
                    pq.push({dist[v], v});
                }
            }
        }
        return dist[n-1];
    }
};

/*
### Approach: Dynamic Programming with Sliding Window Maximum (Prefer this method as its acceptable as well as easy to understand)
1. Use dynamic programming (DP) where dp[i] stores the maximum score from index i to the end of the array.
2. To calculate dp[i], we look at the maximum dp value from indices i+1 to i+k, since jumps are allowed up to k steps.
3. Maintain a max-heap (priority queue) to efficiently retrieve the maximum dp[j] for valid j in [i+1, i+k].
4. As we iterate backward, we ensure all elements in the heap are within the jumpable window by popping those that are not.
5. dp[i] is then computed by adding arr[i] to the top element's dp value in the heap, giving the best next jump score.
6. The heap always contains candidate indices for future dp[i-1] to consider, maintaining correctness with O(log k) updates.
7. The final answer is dp[0], the maximum score starting at the beginning of the array using at most k-step jumps.
*/


// Dynamic Programming with Sliding Window Maximum (Prefer this method)
// Time Complexity: O(n * log k), where n is the length of the array and log k from priority queue operations
// Space Complexity: O(n) for the dp array and priority queue

class Solution {
public:
    int maxResult(vector<int>& arr, int k) {
        priority_queue<pair<int,int>> pq;                       // Max-heap to store {dp value, index}
        int n = arr.size();                                     // Get the size of input array
        vector<int> dp(n, 0);                                   // DP array to store max score from i to end
        dp[n-1] = arr[n-1];                                     // Base case: last index value itself
        pq.push({arr[n-1], n-1});                               // Push base case into priority queue
        for (int i = n - 2; i >= 0; i--) {                      // Iterate backwards (right to left) through the array
            while (pq.top().second > i + k) pq.pop();           // Remove out-of-window elements
            dp[i] = arr[i] + pq.top().first;                    // Add current value to max dp within k steps
            pq.push({dp[i], i});                                // Push current dp value into the queue
        }
        return dp[0];                                           // Return max score starting from index 0
    }
};
    


// Using DP and a deque/list (Doubly Linked List)

class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> dq; // stores indices
        vector<int> dp(n);
        dp[0] = nums[0];
        dq.push_back(0);

        for(int i = 1; i < n; ++i) {
            // Remove indices from the front that are out of window
            while (!dq.empty() && dq.front() < i - k)
                dq.pop_front();

            // Max value in window is at front of deque
            dp[i] = nums[i] + dp[dq.front()];

            // Maintain decreasing order in deque
            while (!dq.empty() && dp[i] >= dp[dq.back()])
                dq.pop_back();

            dq.push_back(i);
        }
        return dp[n - 1];
    }
};

// Dry run for nums = [1, -1, -2, 4, -7, 3], k = 2

// Initialization:
// dp[0] = 1
// dq = [0]

// i = 1
// dq.front() = 0 (valid, in window [i-k, i-1] = [-1, 0])
// dp[1] = nums[1] + dp[0] = -1 + 1 = 0
// dp = [1, 0, _, _, _, _]
// dq back = 0, dp[1] < dp[0], so no pop
// dq = [0, 1]

// i = 2
// dq.front() = 0 (still valid)
// dp[2] = nums[2] + dp[0] = -2 + 1 = -1
// dp = [1, 0, -1, _, _, _]
// dq back = 1, dp[2] < dp[1], so no pop
// dq = [0, 1, 2]

// i = 3
// dq.front() = 0 (still valid)
// dp[3] = nums[3] + dp[0] = 4 + 1 = 5
// dp = [1, 0, -1, 5, _, _]
// dq: remove back while dp[i] >= dp[dq.back()]
// pop 2 (dp[2] = -1), pop 1 (dp[1] = 0), pop 0 (dp[0] = 1)
// dq = [3]

// i = 4
// dq.front() = 3 (valid)
// dp[4] = nums[4] + dp[3] = -7 + 5 = -2
// dp = [1, 0, -1, 5, -2, _]
// dq = [3, 4]

// i = 5
// dq.front() = 3 (still valid)
// dp[5] = nums[5] + dp[3] = 3 + 5 = 8
// dp = [1, 0, -1, 5, -2, 8]
// dq: pop 4 (dp[4] = -2), pop 3 (dp[3] = 5)
// dq = [5]

// Final dp = [1, 0, -1, 5, -2, 8]
// Answer = dp[5] = 8



/* 07. LC#1871. Jump Game VII
*/

// Correct Solution but gives Time Limit Exceeded at 119/142
// Time Complexity: O(n × maxJump) in worst case
// Without pruning, for each position, we might check up to maxJump destinations
// This can lead to excessive computation when maxJump is large
// Space Complexity: O(n)
// Same as the optimized version, but might fill up the queue more rapidly

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        if(s[0] == '1' || s[n-1] == '1') return false;
        queue<int> q;
        vector<int> visited(n, 0);
        q.push(0);
        visited[0] = 1;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int v=u+minJump; v<=min(u+maxJump, n-1); v++) {
                if(s[v] == '0' && !visited[v]) {
                    q.push(v);
                    visited[v] = 1;
                }
                if(v == n-1) return true;
            }
        }
        return false;
    }
};

// Same BFS as above with path pruning
// Time Complexity: O(n)
// In the worst case, we might add each position to the queue at most once
// For each position, we evaluate potential jump destinations from minJump to maxJump, but with pruning
// The pruning ensures we don't repeatedly check the same destinations
// Overall, we process O(n) positions with O(1) work per position

// Space Complexity: O(n)
// We maintain a visited array of size n
// The queue can contain at most n positions
// No other significant space requirements

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        if (s[n-1] == '1') return false;
        
        vector<bool> visited(n, false);
        queue<int> q;
        
        q.push(0);
        visited[0] = true;
        int farthest = 0; // Track the farthest position we've checked
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            // Start from max(curr + minJump, farthest + 1) to avoid redundant checks
            int start = max(curr + minJump, farthest + 1);
            for (int next = start; next <= min(curr + maxJump, n - 1); next++) {
                if (s[next] == '0' && !visited[next]) {
                    if (next == n - 1) return true;
                    visited[next] = true;
                    q.push(next);
                }
            }
            farthest = max(farthest, curr + maxJump);
        }
        
        return false;
    }
};
    