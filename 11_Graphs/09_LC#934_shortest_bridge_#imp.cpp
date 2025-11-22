/* LC#934. Shortest Bridge

### Approach: DFS for Island Marking + BFS for Shortest Bridge (Best approach)
1. Traverse the grid to find the first land cell (value 1), which indicates a part of the first island.
2. Use DFS to visit and mark all connected land cells of this island as 2 to distinguish them from the second island.
3. After painting, scan the grid and enqueue all cells marked as 2. These act as starting points for a BFS.
4. Perform multi-source BFS from these painted cells, expanding outward to find the shortest path to the second island.
5. For every BFS level, increment the distance counter. As soon as an unvisited land cell (value 1) is found,
return the distance since it represents the shortest bridge.
6. DFS takes O(N^2) in worst case, and BFS also explores each cell at most once, resulting in total O(N^2) time.
*/

// 1. DFS then BFS (My Custom Solution)
// Note: It doesn't get any better than this. Make sure to break both the for loops, using one won't break the first loop
// Hence, need isIslandPainted to break both the loops

// Time Complexity: O(n^2) + O(n^2) ~ O(n^2)                               // Full grid traversal and BFS expansion in worst case
// Space Complexity: O(n^2)                                                // For the queue and recursion stack in worst case

class Solution {
    void dfs(int i, int j, vector<vector<int>> &grid) {
        int n = grid.size();                                              // Get the grid size
        if(i<0 || i==n || j<0 || j==n || grid[i][j] == 0 || grid[i][j] == 2) return; // Stop if out-of-bounds or visited
        grid[i][j] = 2;                                                   // Mark the cell as visited (part of first island)
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Directions for 4-way movement
        for(auto dir: dirs) {                                             // Explore all 4 directions
            int vi = i + dir.first;                                       // Compute new row index
            int vj = j + dir.second;                                      // Compute new column index
            dfs(vi, vj, grid);                                            // Recursively call dfs for next cell
        }
    }
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();                                              // Get grid size
        bool isIslandPainted = false;                                     // Flag to stop after first island is found
        for(int i=0; i<n; i++) {                                         
            if(isIslandPainted) break;                                    // Break outer loop if island is found
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 1) {                                     // Found first land cell of the first island
                    dfs(i, j, grid);                                      // Start DFS to mark entire island
                    isIslandPainted = true;                               // Set flag to true
                    break;                                                // Break inner loop
                }
            }
        }
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Directions for BFS expansion
        queue<pair<int, int>> q;                                          // Queue for BFS
        int dist = 0;                                                     // Initialize distance counter
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 2) q.push({i, j});                        // Add all cells of first island to queue
            }
        }
        while(!q.empty()) {
            int qSize = q.size();                                         // Number of nodes at current level
            for(int i=0; i<qSize; i++) {
                int ui = q.front().first, uj = q.front().second;          // Dequeue current cell
                q.pop();
                for(int j=0; j<4; j++) {
                    int vi = ui + dirs[j].first;                          // Compute new row index
                    int vj = uj + dirs[j].second;                         // Compute new column index
                    if(vi >= 0 && vi < n && vj >= 0 && vj < n && grid[vi][vj] != 2) {
                        q.push({vi, vj});                                 // Push new cell to queue
                        if(grid[vi][vj] == 1) return dist;                // Found second island; return distance
                        grid[vi][vj] = 2;                                 // Mark water as visited
                    }
                }
            }
            dist++;                                                       // Increase distance after each BFS level
        }
        return -1;                                                        // Fallback, should never be reached
    }
};

// or, same as above but without comments

class Solution {
    void dfs(int i, int j, vector<vector<int>> &grid) {
        int n = grid.size();
        if(i<0 || i==n || j<0 || j==n || grid[i][j] == 0 || grid[i][j] == 2) return;
        grid[i][j] = 2;
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(auto dir: dirs) {
            int vi = i + dir.first;
            int vj = j + dir.second;
            dfs(vi, vj, grid);
        }
    }
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        bool isIslandPainted = false;        
        for(int i=0; i<n; i++) {
            if(isIslandPainted) break;
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 1) {
                    dfs(i, j, grid);
                    isIslandPainted = true;
                    break;
                }
            }
        }
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        queue<pair<int, int>> q;
        int dist = 0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 2) q.push({i, j});
            }
        }
        while(!q.empty()) {
            int qSize = q.size();
            for(int i=0; i<qSize; i++) {
                int ui = q.front().first, uj = q.front().second;
                q.pop();
                for(int j=0; j<4; j++) {
                    int vi = ui + dirs[j].first;
                    int vj = uj + dirs[j].second;
                    if(vi >= 0 && vi < n && vj >= 0 && vj < n && grid[vi][vj] != 2) {
                        q.push({vi, vj});
                        if(grid[vi][vj] == 1) return dist; // We have to return min steps - 1
                        grid[vi][vj] = 2;
                    }
                }
            }
            dist++;            
        }
        return -1;
    }
};