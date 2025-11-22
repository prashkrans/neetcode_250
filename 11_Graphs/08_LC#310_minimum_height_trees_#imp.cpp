/* LC#310. Minimum Height Trees

### Concept:
A graph with n-1 edges can have at most two Minimum Height Trees (MHTs).

1. **Tree Properties**:
   - A tree is an undirected graph with n nodes and exactly n-1 edges.
   - It is connected and acyclic, meaning there is exactly one path between any two nodes.

2. **Height of a Tree**:
   - The height of a tree is the length of the longest path from the root to a leaf.
   - A Minimum Height Tree (MHT) is a tree where the height is minimized.

3. **Center of a Tree**:
   - The center of a tree is the node (or nodes) that minimizes the maximum distance to any other node.
   - A tree can have at most two centers:
     - If the tree's diameter (longest path between any two nodes) is odd, it has one center.
     - If the tree's diameter is even, it has two centers.

4. **Why At Most Two MHTs**:
   - Removing leaf nodes layer by layer reduces the tree size.
   - The process converges to one or two central nodes, which are the roots of the MHTs.
   - These central nodes ensure that the height of the tree is minimized.

5. **Diameter and Centers**:
   - If the diameter is odd, the center is a single node located in the middle of the longest path.
   - If the diameter is even, the center consists of two adjacent nodes in the middle of the longest path.

6. **Practical Implication**:
   - For any tree, the roots of the MHTs can be found by identifying the center(s) of the tree.
   - This ensures that the resulting tree has the smallest possible height.

### Leaf Node Removal Algorithm (undirected graph) and its similarities with Kahn's Algo (DAG): 
1.  Kahn's algorithm for topological sorting processes nodes with in-degree 0, working from the "beginning" 
    of a directed acyclic graph.
2.  In this problem, we're working with an undirected tree, and we're processing nodes with degree 1 (leaves), 
    working from the "outside" of the tree inward toward the center.
3.  Both algorithms share the same core pattern:
    a. Identify nodes that meet a certain condition (in-degree 0 for Kahn's, degree 1 i.e. leaf nodes for this problem)
    b. Process those nodes and remove them
    c. Update the degrees of neighboring nodes (i.e. decrease by 1)
    d. Add any new nodes that now meet the condition to the queue (i.e. in-degree is 0 for Kahn's or 1 for this problem)
    e. Repeat until no nodes remain (or in this case, until only 1-2 central nodes remain)
*/

/*
### Approach: Leaf Node Removal Algoritm or Iterative Leaf Peeling (Outwards Topological Sorting with BFS from leaf to center)
1. Represent the graph as an adjacency list `adjL`, where each node points to its
neighbors.
2. Use an `indegree` array to track the number of edges connected to each node.
3. Build the graph:
   - For each edge (u, v), add u to v's adjacency list and v to u's adjacency list.
   - Increment the indegree of both u and v.
4. Initialize a queue with all leaf nodes (nodes with indegree 1).
5. Perform BFS to remove leaf nodes level by level:
   - For each node in the current level, remove it from the graph by decrementing the
indegree of its neighbors.
   - If a neighbor becomes a leaf node (indegree 1), add it to the queue.
6. Stop when 2 or fewer nodes remain in the graph:
   - These nodes are the roots of the Minimum Height Trees (MHTs).
7. Return the remaining nodes as the result.
*/

// 1. Leaf Removal Algorithm or Iterative Leaf Peeling 

// Time Complexity: O(n + m) = O(n + n - 1) ~ O(2n) ~ O(n) since m = n-1 as the graph is a tree
// - Building the adjacency list and indegree array takes O(n).
// - The BFS traversal processes each node and edge once, resulting in O(n).

// Space Complexity: O(n + m) = O(2n) ~ O(n)
// - The adjacency list, indegree array, queue, and set all require O(n) space.

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 1) return {0};                          // Special case: single node tree
        vector<int> ans;                                // Stores the result (roots of MHTs)
        vector<vector<int>> adjL(n, vector<int>());     // Adjacency list to represent the graph
        vector<int> indegree(n, 0);                     // Array to store the indegree of each node
        for(int i = 0; i < edges.size(); i++) {         // Build the graph
            int u = edges[i][0];                        // Start node of the edge
            int v = edges[i][1];                        // End node of the edge
            adjL[u].push_back(v);                       // Add edge u -> v
            adjL[v].push_back(u);                       // Add edge v -> u
            indegree[v]++;                              // Increment indegree of v
            indegree[u]++;                              // Increment indegree of u
        }
        queue<int> q;                                   // Queue for BFS traversal
        for(int u = 0; u < n; u++) {                    // Initialize the queue with leaf nodes
            if(indegree[u] == 1) q.push(u);             // Leaf nodes have indegree 1
        }
        while(!q.empty()) {
            int qSize = q.size();                       // Number of nodes in the current level
            if(qSize <= 2 && n <= 2) {                  // If 2 or fewer nodes remain, they are the roots
                while(!q.empty()) {                     // Collect the remaining nodes
                    ans.push_back(q.front());
                    q.pop();
                }
                break;                                  // Exit the loop as we found the roots
            }
            for(int i = 0; i < qSize; i++) {            // Process all nodes in the current level
                int u = q.front();                      // Get the current node
                q.pop();
                n--;                                    // Decrement the total number of nodes
                for(auto v: adjL[u]) {                  // Traverse all neighbors of the current node
                    indegree[v]--;                      // Decrement the indegree of the neighbor
                    if(indegree[v] == 1) {              // If the neighbor becomes a leaf node
                        q.push(v);                      // Add it to the queue
                    }
                }
            }
        }
        return ans;                                     // Return the roots of MHTs
    }
};

// or, same as above but using an unordered_set and without the comments

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 1) return {0};
        vector<int> ans;
        vector<vector<int>> adjL(n, vector<int>());
        vector<int> indegree(n, 0);
        for(int i=0; i<edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            adjL[u].push_back(v);
            adjL[v].push_back(u);
            indegree[v]++;
            indegree[u]++;
        }
        unordered_set<int> st;
        queue<int> q;
        for(int u=0; u<n; u++) {
            st.insert(u);
            if(indegree[u] == 1) q.push(u);
        }
        while(!q.empty()) {
            int qSize = q.size();
            if(qSize <=2 && st.size() <=2) {
                ans = {st.begin(), st.end()};
                break;
            }
            for(int i=0; i<qSize; i++) {
                int u = q.front();
                q.pop();
                st.erase(u);
                for(auto v: adjL[u]) {
                    indegree[v]--;
                    if(indegree[v] == 1) {
                        q.push(v);
                    }
                }
            }
        }
        return ans;        
    }
};