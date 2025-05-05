/* LC#1631. Path With Minimum Effort

Approaches: (Prefer either but 2. is more efficient) - Both my custom codes
1. DFS or BFS + Binary Search (Scroll down a lot)
2. Modified Dijkstra's Algorithm 

/*
### Approach 2: Modified Dijkstra's Algorithm for Minimum Effort Path
1. Represent the grid as a weighted graph:
   - Each cell is a node.
   - The weight of an edge between two adjacent cells is the absolute difference in
     their heights.
2. Use a priority queue (min-heap) to process cells in increasing order of effort:
   - Start from the top-left cell with an initial effort of 0.
   - For each cell, relax its neighbors:
        - Update the effort to reach the neighbor as the maximum of the current effort and
          the edge weight.
        - If the new effort is smaller than the previously recorded effort for the
          neighbor, update it and push the neighbor into the priority queue.
3. Stop when the bottom-right cell is processed:
   - The effort recorded for this cell is the minimum effort required to traverse the
     grid.

### Complexity:
A. Time Complexity:
   - The priority queue processes each cell at most once, and each operation (push/pop) takes O(log(n * m)).
   - The total number of cells is n * m, so the overall complexity is O(n * m * log(n * m)).

   B. Space Complexity:
   - The `dist` matrix requires O(n * m) space to store the minimum effort for each cell.
   - The priority queue can store up to O(n * m) elements.
*/

//  1. Modified Dijkstra's Algorithm for Minimum Effort Path

class Solution {
    struct triple {
        int wt;                                                         // Weight (effort) to reach this cell
        int i;                                                          // Row index of the cell
        int j;                                                          // Column index of the cell
        triple(int _wt, int _i, int _j): wt(_wt), i(_i), j(_j) {}       // Constructor
    };
    struct cmp {                                                        // Remember: greater<int> is for minHeap
        bool operator() (triple *a, triple *b) const {                  // Comparator for priority queue
            return a->wt > b->wt;                                       // Min-heap based on weight (effort)
            // Note: it should not be (a->wt < b->wt) because pq is ulta logic and we need greater for minHeap
        }
    };
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();                                         // Number of rows
        int m = heights[0].size();                                      // Number of columns
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};  // Directions for neighbors
        priority_queue<triple*, vector<triple*>, cmp> pq;               // Min-heap to process cells by minimum effort
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));           // Distance matrix to store minimum effort
        dist[0][0] = 0;                                                 // Start cell has 0 effort
        pq.push(new triple(dist[0][0], 0, 0));                          // Push the start cell into the priority queue
        while(!pq.empty()) {
            triple* u = pq.top();                                       // Get the cell with the minimum effort
            pq.pop();
            int ui = u->i, uj = u->j;                                   // Current cell's row and column indices
            for(auto dir: dirs) {                                       // Traverse all 4 possible neighbors
                int vi = ui + dir[0];                                   // Neighbor's row index
                int vj = uj + dir[1];                                   // Neighbor's column index
                if(vi >= 0 && vi < n && vj >= 0 && vj < m) {            // Check if the neighbor is within bounds
                    int wtUtoV = abs(heights[vi][vj] - heights[ui][uj]); // Effort to move to the neighbor
                    if(dist[ui][uj] != INT_MAX) wtUtoV = max(wtUtoV, dist[ui][uj]); // Update effort to the neighbor
                    if(dist[vi][vj] > wtUtoV) {                         // If a smaller effort is found
                        dist[vi][vj] = wtUtoV;                          // Update the effort for the neighbor
                        pq.push(new triple(dist[vi][vj], vi, vj));      // Push the neighbor into the priority queue
                    }    
                }
            }
        }
        return dist[n-1][m-1];                                          // Return the minimum effort to reach the bottom-right cell
    }
};

// or, same as above but without comments and using a vector<int> to store a triple

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        dist[0][0] = 0;
        pq.push({dist[0][0], 0, 0});
        while(!pq.empty()) {
            vector<int> u = pq.top();
            pq.pop();
            int ui = u[1], uj = u[2];
            for(auto dir: dirs) {
                int vi = ui + dir[0];
                int vj = uj + dir[1];
                if(vi >=0 && vi < n && vj >= 0 && vj < m) {
                    int wtUtoV = abs(heights[vi][vj] - heights[ui][uj]);
                    if(dist[ui][uj] != INT_MAX) wtUtoV = max(wtUtoV, dist[ui][uj]);
                    if(dist[vi][vj] > wtUtoV) {
                        dist[vi][vj] = wtUtoV;
                        pq.push({dist[vi][vj], vi, vj});
                    }    
                }
            }
        }
        return dist[n-1][m-1];
    }
};

// or, same as above but without comments and using typedef pair<int, pair<int, int>> triple; for a triple

typedef pair<int, pair<int, int>> triple;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        priority_queue<triple, vector<triple>, greater<triple>> pq;
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        dist[0][0] = 0;
        pq.push({dist[0][0], {0, 0}});
        while(!pq.empty()) {
            triple u = pq.top();
            pq.pop();
            int ui = u.second.first, uj = u.second.second;
            for(auto dir: dirs) {
                int vi = ui + dir[0];
                int vj = uj + dir[1];
                if(vi >=0 && vi < n && vj >= 0 && vj < m) {
                    int wtUtoV = abs(heights[vi][vj] - heights[ui][uj]);
                    if(dist[ui][uj] != INT_MAX) wtUtoV = max(wtUtoV, dist[ui][uj]);
                    if(dist[vi][vj] > wtUtoV) {
                        dist[vi][vj] = wtUtoV;
                        pq.push({dist[vi][vj], {vi, vj}});
                    }    
                }
            }
        }
        return dist[n-1][m-1];
    }
};

// or, same as above but using a set for minHeap instead of priority queue

typedef pair<int, pair<int, int>> triple;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        set<triple> st;
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        dist[0][0] = 0;
        st.insert({dist[0][0], {0, 0}});
        while(!st.empty()) {
            triple u = *st.begin();
            st.erase(st.begin());
            int ui = u.second.first, uj = u.second.second;
            for(auto dir: dirs) {
                int vi = ui + dir[0];
                int vj = uj + dir[1];
                if(vi >=0 && vi < n && vj >= 0 && vj < m) {
                    int wtUtoV = abs(heights[vi][vj] - heights[ui][uj]);
                    if(dist[ui][uj] != INT_MAX) wtUtoV = max(wtUtoV, dist[ui][uj]);
                    if(dist[vi][vj] > wtUtoV) {
                        auto it = st.find({dist[vi][vj], {vi, vj}});
                        if(it != st.end()) st.erase(it);
                        dist[vi][vj] = wtUtoV;
                        st.insert({dist[vi][vj], {vi, vj}});
                    }    
                }
            }
        }
        return dist[n-1][m-1];
    }
};

// ###############################################################################################



// 2a. DFS

// Time Complexity: O((n * m) * log(maxHeight))
// - The binary search runs for log(maxHeight) iterations, where maxHeight is the maximum height difference in the grid.
// - For each iteration, the DFS traversal visits all cells in the grid, which takes O(n * m).
// - Overall complexity is O((n * m) * log(maxHeight)).

// Space Complexity: O(n * m)
// - The `visited` matrix requires O(n * m) space to track visited cells during DFS.
// - The recursion stack for DFS can go as deep as O(n * m) in the worst case.

class Solution {
    bool dfs(int i, int j, int n, int m, int cost, vector<vector<int>> &heights, vector<vector<int>> &visited) {
        if(i == n-1 && j == m-1) return true;           // If we reach the bottom-right cell, return true
        visited[i][j] = 1;                              // Mark the current cell as visited
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Directions for neighbors
        for(int k = 0; k < 4; k++) {                    // Traverse all 4 possible neighbors
            int vi = i + dirs[k][0];                    // Neighbor's row index
            int vj = j + dirs[k][1];                    // Neighbor's column index
            if(vi >= 0 && vi < n && vj >= 0 && vj < m && !visited[vi][vj]) { // Check if the neighbor is within bounds and not visited
                int currCost = abs(heights[vi][vj] - heights[i][j]); // Effort to move to the neighbor
                if(currCost <= cost && dfs(vi, vj, n, m, cost, heights, visited)) // If effort is within the limit and path exists
                    return true;                        // Return true
            }
        }   
        return false;                                   // Return false if no valid path is found
    }

public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();                         // Number of rows
        int m = heights[0].size();                      // Number of columns
        vector<vector<int>> visited(n, vector<int>(m, 0)); // Matrix to track visited cells
        int l = 0;                                      // Minimum possible effort
        int r = 0;                                      // Maximum possible effort
        for(int i = 0; i < n; i++) {                    // Find the maximum height in the grid
            for(int j = 0; j < m; j++) {
                r = max(r, heights[i][j]);
            }
        }
        while(l < r) {                                  // Binary search for the minimum effort
            int mid = l + (r - l) / 2;                  // Midpoint of the current range
            if(dfs(0, 0, n, m, mid, heights, visited))  // Check if a path exists with the current effort
                r = mid;                                // If yes, reduce the upper bound
            else 
                l = mid + 1;                            // If no, increase the lower bound
            visited = vector<vector<int>>(n, vector<int>(m, 0)); // Reset the visited matrix for the next iteration
        }
        return l;                                       // Return the minimum effort
    }
};

// 2b. BFS

class Solution {
    bool bfs(int cost, vector<vector<int>> heights) {
        int n = heights.size();
        int m = heights[0].size();
        queue<pair<int, int>> q;
        vector<vector<int>> visited(n, vector<int>(m, 0));
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        q.push({0, 0});
        visited[0][0] = 1;
        while(!q.empty()) {
            pair<int, int> u = q.front();
            q.pop();
            for(auto dir: dirs) {
                int vi = u.first + dir[0];
                int vj = u.second + dir[1];
                if(vi >= 0 && vi < n && vj >= 0 && vj < m && !visited[vi][vj]) {
                    int currCost = abs(heights[vi][vj] - heights[u.first][u.second]);
                    if(currCost <= cost) {
                        q.push({vi, vj});
                        visited[vi][vj] = 1;
                        if(vi == n - 1 && vj == m - 1) return true;
                    }
                }
            }
        }
        return false;
    }
    
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        if(n == 1 && m == 1) return 0;
        int l = 0;
        int r = 0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                r = max(r, heights[i][j]);
            }
        }
        while(l < r) {
            int mid = l + (r - l) / 2;
            if(bfs(mid, heights)) r = mid;
            else l = mid + 1;
        }
        return l;
    }
};