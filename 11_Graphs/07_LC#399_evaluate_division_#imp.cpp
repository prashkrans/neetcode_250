/* LC#399. Evaluate Division

Approach:
1. Form the directed and weighted graph from equations and values
2. Use modified Dijkstra's algo

Simple modification of Dijkstra's algo:
    1. dist[src] = 1 (not 0)
    2. dist[v] > wt * dist[u] (not dist[v] > wt + dist[u])
    3. Using double instead of int for edge weights so, INT_MAX is replaced by DBL_MAX

*/

/*
### Approach 1: Graph Representation and Modified Dijkstra's Algorithm
1. Represent the equations as a directed and weighted graph:
   - Each variable is a node.
   - Each equation (u / v = w) is represented as a directed edge u -> v with weight w
and v -> u with weight 1 / w.
2. Build the adjacency list:
   - For each equation, add both directed edges to the adjacency list.
3. Use a modified Dijkstra's algorithm to find the shortest path:
   - Initialize the distance to the source node as 1 (not 0).
   - Use a min-heap (set) to store nodes by their distance.
   - For each node, relax its neighbors:
     - Update the distance to the neighbor if the current path is shorter.
     - Use multiplication instead of addition for edge weights.
4. Process each query:
   - Check if both the source and destination nodes exist in the graph.
   - If either node is missing, return -1.0 for that query.
   - Otherwise, use the modified Dijkstra's algorithm to compute the result.
5. Return the results for all queries as a vector of doubles.

### Complexity:

Time Complexity:
- Let n = number of unique variables (nodes in the graph)
- Let m = number of equations (edges in the graph)
- Let q = number of queries

Building the graph: O(m)
- We iterate through all m equations once and add two edges for each equation

For each query:
- Checking if nodes exist: O(n) in worst case
- Modified Dijkstra's algorithm:
  - Each node can be inserted into the set at most once: O(n)
  - Each extraction from set: O(log n)
  - Each edge is examined once: O(m)
  - Total Dijkstra's complexity: O((n+m) log n)

Overall time complexity: O(q * (n + (n+m) log n)) = O(q * (n+m) log n) ~ O(q * m log n) or O(Q * E log V) when m >= n

Space Complexity:
- Adjacency list: O(n+m) - stores all vertices and edges
- Distance map: O(n) - stores distance for each node
- Set (min-heap): O(n) - at most all nodes can be in the set
- Result array: O(q)

Overall space complexity: O(n + m + q)
*/

// 1. Form a Directed Graph and use Modified Dijkstra's Algorithm
// O(q * m log n) time | 0ms beats 100%
// O(n + m + q) space

class Solution {
    double modifiedDijkstrasAlgo(string src, string dest, unordered_map<string, vector<pair<string, double>>> &adjL) {
        set<pair<double, string>> st;                                   // Min-heap to store nodes by distance
        unordered_map<string, double> dist;                             // Distance map to store shortest path weights
        for(auto i: adjL) {                                             // Initialize distances to all nodes as infinity
            string u = i.first;
            dist[u] = DBL_MAX;
        }
        dist[src] = 1;                                                  // Distance to the source is set to 1 (not 0)
        st.insert({dist[src], src});                                    // Insert the source into the min-heap
        while(!st.empty()) {
            string u = st.begin()->second;                              // Extract the node with the smallest distance
            st.erase(st.begin());
            for(auto i: adjL[u]) {                                      // Traverse all neighbors of the current node
                string v = i.first;                                     // Neighbor node
                double wt = i.second;                                   // Weight of the edge
                if(dist[u] != DBL_MAX && dist[v] > wt * dist[u]) {      // Relaxation condition
                    auto it = st.find({dist[v], v});                    // Check if the neighbor is in the heap
                    if(it != st.end()) st.erase(it);                    // Remove the outdated distance
                    dist[v] = wt * dist[u];                             // Update the distance to the neighbor
                    st.insert({dist[v], v});                            // Insert the updated distance into the heap
                }
            }
        }
        return dist[dest] != DBL_MAX ? dist[dest] : -1.0;               // Return the distance to the destination or -1 if unreachable
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int q = queries.size();                                         // Number of queries
        vector<double> ans(q, -1.0);                                    // Initialize the result vector with -1.0
        unordered_map<string, vector<pair<string, double>>> adjL;       // Adjacency list to represent the graph
        int m = equations.size();                                       // Number of edges (equations)
        for(int i = 0; i < m; i++) {                                    // Build the graph
            string u = equations[i][0];                                 // Start node
            string v = equations[i][1];                                 // End node
            double wt = values[i];                                      // Weight of the edge
            adjL[u].push_back({v, wt});                                 // Add directed edge u -> v
            adjL[v].push_back({u, 1 / wt});                             // Add directed edge v -> u with reciprocal weight
        }
        for(int i = 0; i < q; i++) {                                    // Process each query
            string src = queries[i][0];                                 // Source node
            string dest = queries[i][1];                                // Destination node
            bool foundSrc = false, foundDest = false;                   // Flags to check if nodes exist in the graph
            for(auto i: adjL) {                                         // Check if both nodes exist in the graph
                string u = i.first;
                if(u == src) foundSrc = true;
                if(u == dest) foundDest = true;
                if(foundSrc && foundDest) break;                        // Break early if both nodes are found
            }
            if(foundSrc && foundDest)                                   // If both nodes exist
                ans[i] = modifiedDijkstrasAlgo(src, dest, adjL);        // Run modified Dijkstra's algorithm
            else ans[i] = -1.0;                                         // If either node is missing, return -1.0
        }
        return ans;                                                     // Return the results for all queries
    }
};


// or, same as above but without the comments

class Solution {
    double modifiedDijkstrasAlgo(string src, string dest, unordered_map<string, vector<pair<string, double>>> &adjL) {
        set<pair<double, string>> st;
        unordered_map<string, double> dist;
        for(auto i: adjL) {
            string u = i.first;
            dist[u] = DBL_MAX;
        }
        dist[src] = 1; // not 0
        st.insert({dist[src], src});
        while(!st.empty()) {
            string u = st.begin()->second;
            st.erase(st.begin());
            for(auto i: adjL[u]) {
                string v = i.first;
                double wt = i.second;
                if(dist[u] != DBL_MAX && dist[v] > wt * dist[u]) {
                    auto it = st.find({dist[v], v});
                    if(it != st.end()) st.erase(it);
                    dist[v] = wt * dist[u];
                    st.insert({dist[v], v});
                }
            }
        }
        // for(auto i: dist) cout<<i.first<<" -> "<<i.second<<endl;
        // cout<<"####################################"<<endl;
        return dist[dest] != DBL_MAX ? dist[dest] : -1.0;
        
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int q = queries.size();
        vector<double> ans(q, -1.0);
        unordered_map<string, vector<pair<string, double>>> adjL;
        int m = equations.size(); // m = no. of edges
        for(int i=0; i<m; i++) {
            string u = equations[i][0];
            string v = equations[i][1];
            double wt = values[i];
            adjL[u].push_back({v, wt}); // directed graph since edge wts are diff
            adjL[v].push_back({u, 1/wt});
        }
        for(int i=0; i<q; i++) {
            string src = queries[i][0];
            string dest = queries[i][1];
            bool foundSrc = false, foundDest = false;
            for(auto i: adjL) {
                string u = i.first;
                if(u == src) foundSrc = true;
                if(u == dest) foundDest = true;
                if(foundSrc && foundDest) break;
            }
            if(foundSrc && foundDest)
                ans[i] = modifiedDijkstrasAlgo(src, dest, adjL);
            else ans[i] = -1.0; // redundant
        }
        return ans;
    }
};