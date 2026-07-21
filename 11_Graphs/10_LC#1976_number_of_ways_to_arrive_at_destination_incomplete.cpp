/* LC# 1976. Number of Ways to Arrive at Destination
*/

// ### Approach: Dijkstra Shortest Path Followed by DFS Counting (Still Not Optimal)
// 1. Build an undirected weighted graph using an adjacency list representation.
// 2. Apply Dijkstra’s algorithm from node zero to compute shortest distance to destination.
// 3. Use a set based priority queue to always expand minimum distance node efficiently.
// 4. After shortest distance computation, perform DFS from source to destination.
// 5. Pass remaining shortest distance value and subtract edge weights during traversal.
// 6. Count paths that exactly consume the shortest distance when reaching destination.
// 7. Use memoization with state defined by node and remaining distance to avoid recomputation.
// 8. Apply visited array to prevent cycles during DFS traversal.


// 1. Djikstra's Algo + Recursion without memoization
// Gets TLE, passes 3/57 TCs

class Solution {
    int djikstrasAlgo(int n, vector<vector<pair<int, int>>>& adjL) {
        set<pair<int, int>> setPq;
        vector<int> dist(n, INT_MAX);
        int src = 0, dst = n - 1;
        dist[src] = 0;
        setPq.insert({dist[src], src});
        while(!setPq.empty()) {
            int u = setPq.begin()->second;
            setPq.erase(setPq.begin());
            for(auto i: adjL[u]) {
                int v = i.first, wt_uToV = i.second;
                if(dist[u] != INT_MAX && dist[v] > dist[u] + wt_uToV) {
                    auto it = setPq.find({dist[v], v});
                    if(it != setPq.end()) setPq.erase(it);
                    dist[v] = dist[u] + wt_uToV;
                    setPq.insert({dist[v], v});
                }
            }
        }
        return dist[dst];
    }

    int dfs(int u, int n, vector<vector<pair<int, int>>>& adjL, vector<int> &visited, int sssp) {
        if(u == n - 1) return (sssp == 0) ? 1 : 0;
        visited[u] = 1;
        int sum = 0;
        for(auto i: adjL[u]) {
            int v = i.first;
            int wt_uToV = i.second;
            if(!visited[v]) sum += dfs(v, n, adjL, visited, sssp - wt_uToV);
        }
        visited[u] = 0;
        return sum;
    }

public:
    int countPaths(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> adjL(n, vector<pair<int, int>>());
        for(int i = 0; i < roads.size(); i++) {
            int u = roads[i][0], v = roads[i][1], wt = roads[i][2];
            adjL[u].push_back({v, wt});
            adjL[v].push_back({u, wt});
        }
        vector<int> visited(n, 0);
        int sssp = djikstrasAlgo(n, adjL);
        // cout<<"sssp = "<<sssp<<endl;
        int ans = dfs(0, n, adjL, visited, sssp);
        return ans;
    }
};  

// 2. Djikstra's Algo + Recursion without memoization
// Gets TLE, passes 15/57 TCs
// Time Complexity: O((n + m) * log n + n * sssp)
// Space Complexity: O(n + m + n * sssp)

class Solution {                                                                           // Defines the Solution class
    int djikstrasAlgo(int n, vector<vector<pair<int, int>>>& adjL) {                       // Computes shortest path from source to destination
        set<pair<int, int>> setPq;                                                         // Acts as priority queue storing distance and node
        vector<int> dist(n, INT_MAX);                                                      // Stores shortest distances from source
        int src = 0, dst = n - 1;                                                          // Source and destination nodes
        dist[src] = 0;                                                                     // Distance to source is zero
        setPq.insert({dist[src], src});                                                    // Insert source into set
        while(!setPq.empty()) {                                                           // Process until all reachable nodes handled
            int u = setPq.begin()->second;                                                 // Node with minimum distance
            setPq.erase(setPq.begin());                                                    // Remove processed node
            for(auto i: adjL[u]) {                                                         // Traverse all adjacent edges
                int v = i.first, wt_uToV = i.second;                                       // Neighbor node and edge weight
                if(dist[u] != INT_MAX && dist[v] > dist[u] + wt_uToV) {                    // Relaxation condition
                    auto it = setPq.find({dist[v], v});                                   // Check if neighbor exists in set
                    if(it != setPq.end()) setPq.erase(it);                                 // Remove outdated distance entry
                    dist[v] = dist[u] + wt_uToV;                                           // Update shortest distance
                    setPq.insert({dist[v], v});                                            // Insert updated distance
                }
            }
        }
        return dist[dst];                                                                  // Return shortest distance to destination
    }

    int dfs(int u, int n, vector<vector<pair<int, int>>>& adjL, vector<int> &visited,
            int sssp, map<pair<int, int>, int> & dp) {                                    // DFS to count valid shortest paths
        if(dp.count({u, sssp})) return dp[{u, sssp}];                                      // Return memoized result
        if(u == n - 1) return dp[{u, sssp}] = (sssp == 0) ? 1 : 0;                          // Destination reached check
        visited[u] = 1;                                                                   // Mark node as visited
        int sum = 0;                                                                      // Accumulates number of paths
        for(auto i: adjL[u]) {                                                            // Explore all neighbors
            int v = i.first;                                                              // Neighbor node
            int wt_uToV = i.second;                                                        // Edge weight
            if(!visited[v]) sum += dfs(v, n, adjL, visited, sssp - wt_uToV, dp);           // Recurse with reduced distance
        }
        visited[u] = 0;                                                                   // Backtrack visited state
        return dp[{u, sssp}] = sum;                                                        // Store and return computed paths
    }

public:                                                                                    // Public access specifier
    int countPaths(int n, vector<vector<int>>& roads) {                                   // Counts number of shortest paths
        vector<vector<pair<int, int>>> adjL(n, vector<pair<int, int>>());                 // Adjacency list representation
        for(int i = 0; i < roads.size(); i++) {                                           // Build graph from edge list
            int u = roads[i][0], v = roads[i][1], wt = roads[i][2];                       // Extract edge endpoints and weight
            adjL[u].push_back({v, wt});                                                   // Add edge u to v
            adjL[v].push_back({u, wt});                                                   // Add edge v to u
        }
        vector<int> visited(n, 0);                                                        // Tracks visited nodes in DFS
        map<pair<int, int>, int> dp;                                                      // Memoization map for DFS states
        int sssp = djikstrasAlgo(n, adjL);                                                // Compute shortest path distance
        int ans = dfs(0, n, adjL, visited, sssp, dp);                                     // Count paths matching shortest distance
        return ans;                                                                       // Return total number of shortest paths
    }
};


// Same as above but using MOD_VAL twice and one additional pruning if(sssp < 0) return 0;
// Gets TLE, passes 40/57 TCs

#define MOD_VAL 1000000007

class Solution {
    int djikstrasAlgo(int n, vector<vector<pair<int, int>>>& adjL) {
        set<pair<int, int>> setPq;
        vector<int> dist(n, INT_MAX);
        int src = 0, dst = n - 1;
        dist[src] = 0;
        setPq.insert({dist[src], src});
        while(!setPq.empty()) {
            int u = setPq.begin()->second;
            setPq.erase(setPq.begin());
            for(auto i: adjL[u]) {
                int v = i.first, wt_uToV = i.second;
                if(dist[u] != INT_MAX && dist[v] > dist[u] + wt_uToV) {
                    auto it = setPq.find({dist[v], v});
                    if(it != setPq.end()) setPq.erase(it);
                    dist[v] = dist[u] + wt_uToV;
                    setPq.insert({dist[v], v});
                }
            }
        }
        return dist[dst];
    }

    int dfs(int u, int n, vector<vector<pair<int, int>>>& adjL, vector<int> &visited, int sssp, map<pair<int, int>, int> & dp) {
        if(sssp < 0) return 0;
        if(dp.count({u, sssp})) return dp[{u, sssp}];
        if(u == n - 1) return dp[{u, sssp}] = (sssp == 0) ? 1 : 0;
        visited[u] = 1;
        int sum = 0;
        for(auto i: adjL[u]) {
            int v = i.first;
            int wt_uToV = i.second;
            if(!visited[v]) sum = (sum + dfs(v, n, adjL, visited, sssp - wt_uToV, dp)) % MOD_VAL;
        }
        visited[u] = 0;
        return dp[{u, sssp}] = sum % MOD_VAL;
    }

public:
    int countPaths(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> adjL(n, vector<pair<int, int>>());
        for(int i = 0; i < roads.size(); i++) {
            int u = roads[i][0], v = roads[i][1], wt = roads[i][2];
            adjL[u].push_back({v, wt});
            adjL[v].push_back({u, wt});
        }
        vector<int> visited(n, 0);
        map<pair<int, int>, int> dp;
        int sssp = djikstrasAlgo(n, adjL);
        int ans = dfs(0, n, adjL, visited, sssp, dp);
        return ans;
    }
};