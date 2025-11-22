/* LC#997. Find the Town Judge

### Approach: Graph Representation with Indegree and Outdegree
1. Use an adjacency list `adjL` to store outgoing edges for each person.
2. Use an `indegree` array to count the number of people who trust each person.
3. Iterate through the `trust` array:
   - For each pair `(u, v)`, add `v` to the adjacency list of `u` and increment the indegree of `v`.
4. Check for the town judge:
   - The town judge should have an indegree of `n-1` (trusted by everyone except themselves).
   - The town judge should have no outgoing edges (does not trust anyone).
5. Return the town judge's index (1-based) or -1 if no judge is found.

### Notes:
- This approach efficiently identifies the town judge by leveraging graph properties.
- The adjacency list is used to track outgoing edges, while the indegree array tracks incoming edges.
*/

// Time Complexity: O(n + m)
// - Building the adjacency list and indegree array takes O(m), where m is the size of the `trust` array.
// - Checking for the town judge takes O(n), where n is the number of people.
// - Overall complexity is O(n + m).

// Space Complexity: O(n + m)
// - The adjacency list uses O(m) space to store the trust relationships.
// - The indegree array uses O(n) space.

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<vector<int>> adjL(n, vector<int>());         // Adjacency list to store outgoing edges
        vector<int> indegree(n, 0);                         // Array to store indegree of each person
        for(int i = 0; i < trust.size(); i++) {             // Build the graph
            int u = trust[i][0] - 1;                        // Convert 1-based index to 0-based
            int v = trust[i][1] - 1;
            adjL[u].push_back(v);                           // Add outgoing edge from u to v
            indegree[v]++;                                  // Increment indegree of v
        }
        int townJudge = -1;
        for(int i = 0; i < n; i++) {                        // Check for the town judge
            if(indegree[i] == n - 1 && adjL[i].empty())     // Judge has indegree n-1 and no outgoing edges
                townJudge = i + 1;                          // Convert 0-based index back to 1-based
        }
        return townJudge;                                   // Return the town judge or -1 if none found
    }
};

// or, same as above but without comments

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<vector<int>> adjL(n, vector<int>());
        vector<int> indegree(n, 0);
        for(int i=0; i<trust.size(); i++) {
            int u = trust[i][0] - 1;
            int v = trust[i][1] - 1;
            adjL[u].push_back(v);
            indegree[v]++;
        }
        int townJudge = -1;
        for(int i=0; i<n; i++) {
            if(indegree[i] == n-1 && adjL[i].empty()) townJudge = i + 1;
        }
        return townJudge;
    }
};