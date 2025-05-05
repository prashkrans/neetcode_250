/* LC#2392. Build a Matrix With Conditions

### Approaches: 
1. DFS with recStack | recStack is backtracked, topoSort array is reversed, for loop for all the nodes is used
2. BFS (Kahn's Algo) - Always prefer Kahn's Algo for toposort | Scroll down a lot 

### Approach: Topological Sorting for Row and Column Conditions using DFS and recStack
1. **Graph Representation**:
   - Represent the row and column conditions as directed graphs using adjacency lists.
   - Each condition (u, v) implies a directed edge u -> v.

2. **Topological Sorting**:
   - Perform topological sorting on the row and column graphs using DFS.
   - If a cycle is detected during DFS, return an empty matrix since the conditions are invalid.

3. **Matrix Construction**:
   - Use the topological orders of the rows and columns to construct the matrix.
   - Place each element at the intersection of its row and column positions.

4. **Cycle Detection**:
   - Use a recursion stack during DFS to detect cycles in the graph.
   - If a cycle is detected, return an empty matrix.

5. **Time Complexity**: O(2(k + m)) ~ O(k + m) i.e. O(n + m) since k = n here
   - Building the adjacency list for each condition takes O(m), where m is the number of edges (conditions).
   - Topological sorting using DFS is run twice which takes O(2*(k + m)) ~ O(k + m), where k is the number of nodes.
   - Overall complexity is O(k + m) for each topological sort, and since there are two sorts (row and column), the total is O(k + E).

6. **Space Complexity**: O(k + m) i.e. O(n + m) since k = n here
   - The adjacency list requires O(k + m) space to store the graph.
   - The recursion stack for DFS can go as deep as O(k) in the worst case.
   - The `recStack`, `visited`, and `topoSort` arrays each require O(k) space.
*/

// 1. DFS with recStack

class Solution {
    bool isCyclicDfs(int u, vector<vector<int>> &adjL, vector<int> &recStack, vector<int> &visited, vector<int> &topoSort) {
        recStack[u] = 1;                               // Mark the current node in the recursion stack
        visited[u] = 1;                                // Mark the current node as visited
        for(auto v: adjL[u]) {                         // Traverse all neighbors of the current node
            if(!visited[v]) {                          // If the neighbor is not visited
                if(isCyclicDfs(v, adjL, recStack, visited, topoSort)) return true; // Check for cycles recursively
            }
            else if(recStack[v] == 1) return true;     // If the neighbor is in the recursion stack, a cycle is detected
        }
        recStack[u] = 0;                               // Backtrack: remove the node from the recursion stack
        topoSort.push_back(u + 1);                     // Add the node to the topological sort
        return false;
    }

    vector<int> topoSort(int k, vector<vector<int>>& conditions) {
        vector<vector<int>> adjL(k, vector<int>());    // Adjacency list to represent the graph
        for(int i = 0; i < conditions.size(); i++) {   // Build the graph from the conditions
            int u = conditions[i][0] - 1;             // Convert 1-based index to 0-based
            int v = conditions[i][1] - 1;             // Convert 1-based index to 0-based
            adjL[u].push_back(v);                     // Add a directed edge u -> v
        }
        vector<int> recStack(k, 0);                   // Track nodes in the recursion stack
        vector<int> visited(k, 0);                    // Track visited nodes
        vector<int> topoSort;                         // Store the topological order
        for(int i = 0; i < k; i++) {                  // Perform DFS for all nodes
            if(!visited[i]) {                         // If the node is not visited
                if(isCyclicDfs(i, adjL, recStack, visited, topoSort)) return vector<int>(); // Return empty if a cycle is detected
            }
        }
        reverse(topoSort.begin(), topoSort.end());    // Reverse the topological order
        return topoSort;
    }

public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<vector<int>> ans;                      // Initialize the result matrix
        
        vector<int> rowTopoSort = topoSort(k, rowConditions); // Get the topological sort for row conditions
        if(rowTopoSort.empty()) return ans;           // If a cycle is detected, return an empty matrix
        
        vector<int> colTopoSort = topoSort(k, colConditions); // Get the topological sort for column conditions
        if(colTopoSort.empty()) return ans;           // If a cycle is detected, return an empty matrix

        ans = vector<vector<int>>(k, vector<int>(k, 0)); // Initialize the k x k matrix with 0
        for(int i = 0; i < k; i++) {                  // Fill the matrix based on the topological orders
            for(int j = 0; j < k; j++) {
                if(rowTopoSort[i] == colTopoSort[j]) ans[i][j] = rowTopoSort[i]; // Place the element at the intersection
            }
        }
        return ans;                                   // Return the constructed matrix
    }
};

// or, same as above but without comments

class Solution {
    bool isCyclicDfs(int u, vector<vector<int>> &adjL, vector<int> &recStack, vector<int> &visited, vector<int> &topoSort) {
        recStack[u] = 1;
        visited[u] = 1;
        for(auto v: adjL[u]) {
            if(!visited[v]) {
                if(isCyclicDfs(v, adjL, recStack, visited, topoSort)) return true;
            }
            else if(recStack[v] == 1) return true;
        }
        recStack[u] = 0; // backtrack
        topoSort.push_back(u + 1);
        return false;
    }
    vector<int> topoSort(int k, vector<vector<int>>& conditions) {
        vector<vector<int>> adjL(k, vector<int>());
        for(int i=0; i<conditions.size(); i++) {
            int u = conditions[i][0] - 1;
            int v = conditions[i][1] - 1;
            adjL[u].push_back(v);
        }
        vector<int> recStack(k, 0);
        vector<int> visited(k, 0);
        vector<int> topoSort;
        for(int i=0; i<k; i++) {
            if(!visited[i]) {
                if(isCyclicDfs(i, adjL, recStack, visited, topoSort)) return vector<int>();
            }
        }
        reverse(topoSort.begin(), topoSort.end());
        return topoSort;
    }
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<vector<int>> ans;
        
        vector<int> rowTopoSort = topoSort(k, rowConditions);
        if(rowTopoSort.empty()) return ans;
        // for(auto i: rowTopoSort) cout<<i<<" "; cout<<endl;
        
        vector<int> colTopoSort = topoSort(k, colConditions);
        if(colTopoSort.empty()) return ans;
        // for(auto i: colTopoSort) cout<<i<<" "; cout<<endl;

        ans = vector<vector<int>>(k, vector<int>(k, 0));
        for(int i=0; i<k; i++) {
            for(int j=0; j<k; j++) {
                if(rowTopoSort[i] == colTopoSort[j]) ans[i][j] = rowTopoSort[i];
            }
        }
        return ans;
    }
};

// 2. BFS (Kahn's Algo)

// Time Complexity: O(k + E)
// - Building the adjacency list for each condition takes O(m), where m is the number of edges (conditions).
// - Topological sorting using Kahn's Algorithm takes O(k + m), where k is the number of nodes.
// - Overall complexity is O(k + m) for each topological sort, and since there are two sorts (row and column), the total is O(2 * (k + E)) = O(k + E).

// Space Complexity: O(k + E)
// - The adjacency list requires O(k + m) space to store the graph.
// - The `indegree` array requires O(k) space to track the indegree of each node.
// - The queue used in Kahn's Algorithm requires O(k) space in the worst case.

class Solution {
    vector<int> topoSortKahnsAlgo(int k, vector<vector<int>>& conditions) {
        vector<int> topoSort;                          // Store the topological order
        vector<vector<int>> adjL(k, vector<int>());    // Adjacency list to represent the graph
        vector<int> indegree(k, 0);                    // Array to track the indegree of each node
        for(int i = 0; i < conditions.size(); i++) {   // Build the graph from the conditions
            int u = conditions[i][0] - 1;             // Convert 1-based index to 0-based
            int v = conditions[i][1] - 1;             // Convert 1-based index to 0-based
            adjL[u].push_back(v);                     // Add a directed edge u -> v
            indegree[v]++;                            // Increment the indegree of v
        }
        queue<int> q;                                 // Queue for Kahn's Algorithm
        for(int u = 0; u < k; u++) {                  // Add all nodes with indegree 0 to the queue
            if(indegree[u] == 0) q.push(u);
        }
        while(!q.empty()) {                           // Process nodes in the queue
            int u = q.front();                        // Get the front node
            q.pop();
            topoSort.push_back(u + 1);                // Add the node to the topological order
            for(auto v: adjL[u]) {                    // Traverse all neighbors of the current node
                if(--indegree[v] == 0) q.push(v);     // Decrement the indegree and add to the queue if it becomes 0
            }
        }        
        return (topoSort.size() == k) ? topoSort : vector<int>(); // Return the topological order or empty if cyclic
    }
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<vector<int>> ans;                      // Initialize the result matrix
        
        vector<int> rowTopoSort = topoSortKahnsAlgo(k, rowConditions); // Get the topological sort for row conditions
        if(rowTopoSort.empty()) return ans;           // If a cycle is detected, return an empty matrix
        
        vector<int> colTopoSort = topoSortKahnsAlgo(k, colConditions); // Get the topological sort for column conditions
        if(colTopoSort.empty()) return ans;           // If a cycle is detected, return an empty matrix

        ans = vector<vector<int>>(k, vector<int>(k, 0)); // Initialize the k x k matrix with 0
        for(int i = 0; i < k; i++) {                  // Fill the matrix based on the topological orders
            for(int j = 0; j < k; j++) {
                if(rowTopoSort[i] == colTopoSort[j]) ans[i][j] = rowTopoSort[i]; // Place the element at the intersection
            }
        }
        return ans;                                   // Return the constructed matrix
    }
};

// or, same as above but without comments

class Solution {
    vector<int> topoSortKahnsAlgo(int k, vector<vector<int>>& conditions) {
        vector<int> topoSort;
        vector<vector<int>> adjL(k, vector<int>());
        vector<int> indegree(k, 0);
        for(int i=0; i<conditions.size(); i++) {
            int u = conditions[i][0] - 1;
            int v = conditions[i][1] - 1;
            adjL[u].push_back(v);
            indegree[v]++;
        }
        queue<int> q;
        for(int u=0; u<k; u++) {
            if(indegree[u] == 0) q.push(u);
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            topoSort.push_back(u + 1);
            for(auto v: adjL[u]) {
                if(--indegree[v] == 0) q.push(v);
            }
        }        
        return (topoSort.size() == k) ? topoSort : vector<int>();
    }
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<vector<int>> ans;
        
        vector<int> rowTopoSort = topoSortKahnsAlgo(k, rowConditions);
        if(rowTopoSort.empty()) return ans;
        // for(auto i: rowTopoSort) cout<<i<<" "; cout<<endl;
        
        vector<int> colTopoSort = topoSortKahnsAlgo(k, colConditions);
        if(colTopoSort.empty()) return ans;
        // for(auto i: colTopoSort) cout<<i<<" "; cout<<endl;

        ans = vector<vector<int>>(k, vector<int>(k, 0));
        for(int i=0; i<k; i++) {
            for(int j=0; j<k; j++) {
                if(rowTopoSort[i] == colTopoSort[j]) ans[i][j] = rowTopoSort[i];
            }
        }
        return ans;
    }
};