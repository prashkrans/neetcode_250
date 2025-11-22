/* LC#463. Island Perimeter

### Approach: Iterative Grid Traversal
1. Iterate through all cells in the grid.
2. For each land cell (`grid[i][j] == 1`):
   - Check its 4 neighbors (up, down, left, right).
   - Count the number of neighboring land cells (`indegree`).
   - Add `(4 - indegree)` to the perimeter, as each land cell contributes 4 sides minus the shared sides with neighbors.
3. Return the total perimeter.

### Notes:
- This approach ensures that each land cell's contribution to the perimeter is calculated efficiently.
- The use of a `dirs` vector simplifies the neighbor-checking logic.
*/

// 1. Iterative Grid Traversal (My custom code)
// Time Complexity: O(n * m)
// - We iterate through all cells in the grid, and for each cell, we check its 4 neighbors.
// - This results in O(n * m) complexity, where n is the number of rows and m is the number of columns.

// Space Complexity: O(1)
// - No additional space is used apart from a few variables.

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;                              // Initialize the perimeter
        int n = grid.size(), m = grid[0].size();        // Get the dimensions of the grid
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Directions for neighbors
        for(int i = 0; i < n; i++) {                    // Iterate through all rows
            for(int j = 0; j < m; j++) {                // Iterate through all columns
                if(grid[i][j] == 1) {                   // If the cell is land
                    int indegree = 0;                   // Count the number of neighboring land cells
                    for(int k = 0; k < 4; k++) {        // Check all 4 neighbors
                        int vi = i + dirs[k][0];        // Neighbor row
                        int vj = j + dirs[k][1];        // Neighbor column
                        if(vi >= 0 && vi < n && vj >= 0 && vj < m && grid[vi][vj] == 1) 
                            indegree++;                 // Increment indegree if the neighbor is land
                    }
                    perimeter += (4 - indegree);        // Add the contribution of this cell to the perimeter
                }
            }
        }
        return perimeter;                               // Return the total perimeter
    }
};

// or, same as above but without comments

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(grid[i][j] == 1) {
                    int indegree = 0;
                    for(int k=0; k<4; k++) {
                        int vi = i + dirs[k][0];
                        int vj = j + dirs[k][1];
                        if(vi >= 0 && vi < n && vj >= 0 && vj < m && grid[vi][vj] == 1) indegree++;
                    }
                    perimeter += (4 - indegree);
                }
            }
        }
        return perimeter;
    }
};