/* LC#990. Satisfiability of Equality Equations
Directed graph and not a simple cycle check but a grouping check

### Approach: Disjoint Set Union with Path Compression (Union Find Algo - Union by Rank or Height)
1. Treat each variable as a node and equality relations as edges forming connected components.
2. Initialize disjoint set union structure storing parent and rank for each variable.
3. Process all equality equations first and union their corresponding variable sets.
4. Use path compression during find operation to flatten tree structure for efficiency.
5. Use union by rank to keep trees shallow during merge operations.
6. After unions, process inequality equations and verify variables belong to different sets.
7. If any inequality connects variables in same set, return false immediately.
8. Otherwise, return true indicating all equations are logically consistent.
*/

// 1a. Disjoint Set Union + Path compression (Union Find Algo - Union by rank) 
// Time Complexity: O(n * α(n)) | Oms, beats 100%
// Space Complexity: O(n)
// where, n = number of equations (or distinct variables involved).
// α(n) = inverse Ackermann function.

class Solution {
    char findSet(char u, unordered_map<char, pair<char, int>>& parent) {
        char currParent = parent[u].first;
        if(currParent == u) return u;
        return parent[u].first = findSet(currParent, parent); // [#IMP]
    }

    void unionOfSets(char u, char v, unordered_map<char, pair<char, int>>& parent) { // union by rank
        char rootU = findSet(u, parent), rootV = findSet(v, parent);
        int rankU = parent[u].second, rankV = parent[v].second;
        int mergedRank = rankU + rankV;
        if(rankU < rankV) {
            parent[rootU] = {rootV, mergedRank};    // Update parent[rootU&V] not parent[u&v]
            parent[rootV] = {rootV, mergedRank};
        } else {
            parent[rootU] = {rootU, mergedRank};
            parent[rootV] = {rootU, mergedRank};
        }
    }

public:
    bool equationsPossible(vector<string>& equations) {
        // unordered_map<char, vector<char>> adjL;
        unordered_map<char, pair<char, int>> parent;
        int countInequalities = 0;
        for(int i = 0; i < equations.size(); i++) {
            char u = equations[i][0], v = equations[i][3];
            parent[u] = {u, 1};                     // Union by rank: {u, 1} while Union by height: {u, 0}
            parent[v] = {v, 1};
        }
        for(int i = 0; i < equations.size(); i++) {
            char u = equations[i][0], v = equations[i][3];
            char edge = equations[i][1];
            // if(edge == '=') adjL[u].push_back(v); // There is no need of an adjacency list
            if(edge == '=') {
                if(findSet(u, parent) != findSet(v, parent)) {
                    unionOfSets(u, v, parent);
                }
            }
        }
        for(int i = 0; i < equations.size(); i++) {
            char u = equations[i][0], v = equations[i][3];
            char edge = equations[i][1];
            if(edge == '!') {
                if(findSet(u, parent) == findSet(v, parent)) return false;
            }
        }
        return true;        
    }
};



// 1b. Disjoint Set Union + Path compression (Union Find Algo - Union by height) 
// Time Complexity: O(n * α(n)) | Oms, beats 100%
// Space Complexity: O(n)
// where, n = number of equations (or distinct variables involved).
// α(n) = inverse Ackermann function.

class Solution {                                                                           
    char findSet(char u, unordered_map<char, pair<char, int>>& parent) {                    // Finds set representative with path compression
        char currParent = parent[u].first;                                                  // Get current parent
        if(currParent == u) return u;                                                       // Root found
        return parent[u].first = findSet(currParent, parent);                               // [#IMP] Compress path recursively
    }

    void unionOfSets(char u, char v, unordered_map<char, pair<char, int>>& parent) {        // Union by height strategy
        char rootU = findSet(u, parent), rootV = findSet(v, parent);                        // Find roots of both sets
        int heightU = parent[u].second, heightV = parent[v].second;                         // Retrieve tree heights
        if(heightU < heightV) {                                                             // Attach shorter tree under taller
            parent[rootU] = {rootV, heightV};                                               // Update rootU parent
        } else if (heightU > heightV){                                                      // Opposite height comparison
            parent[rootV] = {rootU, heightU};                                               // Update rootV parent
        } else {                                                                            // Heights equal, increase height
            heightU++;                                                                      // Increment resulting tree height
            parent[rootU] = {rootU, heightU};                                               // Update rootU height
            parent[rootV] = {rootU, heightU};                                               // Attach rootV under rootU
        }
    }

public:                                                                                   
    bool equationsPossible(vector<string>& equations) {                                     // Checks satisfiability of equations
        unordered_map<char, pair<char, int>> parent;                                        // DSU parent and height map
        int countInequalities = 0;                                                          // Reserved variable, not required
        for(int i = 0; i < equations.size(); i++) {                                         // Initialize DSU entries
            char u = equations[i][0], v = equations[i][3];                                  // Extract variables
            parent[u] = {u, 0};                                                             // Initialize parent and height
            parent[v] = {v, 0};                                                             // Initialize parent and height
        }
        for(int i = 0; i < equations.size(); i++) {                                         // Process equality relations
            char u = equations[i][0], v = equations[i][3];                                  // Extract variables
            char edge = equations[i][1];                                                    // Operator character
            if(edge == '=') {                                                               // Equality condition
                if(findSet(u, parent) != findSet(v, parent)) {                              // Different sets check
                    unionOfSets(u, v, parent);                                              // Merge sets
                }
            }
        }
        for(int i = 0; i < equations.size(); i++) {                                         // Process inequality relations
            char u = equations[i][0], v = equations[i][3];                                  // Extract variables
            char edge = equations[i][1];                                                    // Operator character
            if(edge == '!') {                                                               // Inequality condition
                if(findSet(u, parent) == findSet(v, parent)) return false;                  // Conflict detected
            }
        }
        return true;                                                                        // All equations satisfied
    }
};
 
