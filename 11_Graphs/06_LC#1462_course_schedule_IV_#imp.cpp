/* LC#1462. Course Schedule IV

### Approaches:
1. Floyd-Warshall Algo with O(n^2 + q) time
2. DFS/BFS for each query O(n^2 * q) time and not O(n^3 + q) [not verified]

### Approach: Floyd-Warshall Algorithm for Transitive Closure
1. Represent the courses as a directed graph where each course is a node, and a directed
edge exists from course u to course v if u is a prerequisite for v.
2. Use a 2D matrix `transitiveMatrix` to store reachability information, where
`transitiveMatrix[i][j]` is true if course i is a prerequisite for course j.
3. Initialize the matrix:
   - For each prerequisite pair (u, v), set `transitiveMatrix[u][v] = true` to indicate
that course u is a direct prerequisite for course v.
4. Use the Floyd-Warshall algorithm to compute the transitive closure of the graph:
   - Iterate over all intermediate courses k.
   - For each pair of courses (i, j), check if course i can reach course j through
course k.
   - If `transitiveMatrix[i][k]` and `transitiveMatrix[k][j]` are both true, set
`transitiveMatrix[i][j] = true`.
5. Answer each query:
   - For each query (u, v), check the value of `transitiveMatrix[u][v]`.
   - If true, course u is a prerequisite for course v; otherwise, it is not.
6. Return the results for all queries as a vector of booleans.
7. Time Complexity:
   - Building the transitive matrix using Floyd-Warshall takes O(numCourses^3).
   - Answering all queries takes O(queries.size()).
   - Overall complexity is O(numCourses^3 + queries.size()).
8. Space Complexity:
   - The transitive matrix uses O(numCourses^2) space to store reachability information.
*/

//  1. Floyd-Warshall Algorithm for Transitive Closure
//  O(n^3 + q) ~ O(n^3)
//  O(n^2)

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<bool> ans;                                   // Stores the result for each query
        vector<vector<bool>> transitiveMatrix(numCourses, vector<bool>(numCourses, false)); // Transitive closure matrix
        for(int i = 0; i < prerequisites.size(); i++) {     // Initialize the matrix with direct prerequisites
            int u = prerequisites[i][0];                    // Course u
            int v = prerequisites[i][1];                    // Course v
            transitiveMatrix[u][v] = true;                  // Mark u -> v as reachable
        }
        
        for(int k = 0; k < numCourses; k++) {               // Floyd-Warshall algorithm to compute transitive closure
            for(int i = 0; i < numCourses; i++) {           // Iterate over all pairs of courses
                for(int j = 0; j < numCourses; j++) {       // Check if i -> k and k -> j implies i -> j
                    if(transitiveMatrix[i][k] && transitiveMatrix[k][j]) 
                        transitiveMatrix[i][j] = true;      // Update reachability
                }
            }
        }
        
        for(int i = 0; i < queries.size(); i++) {           // Answer each query
            int u = queries[i][0];                          // Query course u
            int v = queries[i][1];                          // Query course v
            ans.push_back(transitiveMatrix[u][v]);          // Check if u -> v is reachable
        }
        return ans;                                         // Return the results for all queries
    }
};

// or, same as above but without comments

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<bool> ans;
        vector<vector<bool>> transitiveMatrix(numCourses, vector<bool>(numCourses, false));
        for(int i=0; i<prerequisites.size(); i++) {
            int u = prerequisites[i][0];
            int v = prerequisites[i][1];
            transitiveMatrix[u][v] = true;
        }
        for(int k=0; k<numCourses; k++) {
            for(int i=0; i<numCourses; i++) {
                for(int j=0; j<numCourses; j++) {
                    if(transitiveMatrix[i][k] && transitiveMatrix[k][j]) 
                        transitiveMatrix[i][j] = true;
                }
            }
        }
        for(int i=0; i<queries.size(); i++) {
            int u = queries[i][0];
            int v = queries[i][1];
            ans.push_back(transitiveMatrix[u][v]);
        }
        return ans;
    }
};



// ################################################
// Topological Sort wont work here, tho the code is correct


class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<bool> ans;
        vector<vector<int>> adjL(numCourses, vector<int>());
        queue<int> q;
        vector<int> indegree(numCourses, 0);
        for(int i=0; i<prerequisites.size(); i++) {
            int u = prerequisites[i][0];
            int v = prerequisites[i][1];
            adjL[u].push_back(v);
            indegree[v]++;
        }
        vector<int> topoSort;
        for(int u=0; u<numCourses; u++) {
            if(indegree[u] == 0) {
                q.push(u);
                topoSort.push_back(u);
            }
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto v: adjL[u]) {
                indegree[v]--;
                if(indegree[v] == 0) {
                    q.push(v);
                    topoSort.push_back(v);
                }
            }
        }
        cout<<"count: "<<topoSort.size()<<" == "<<"numCourses: "<<numCourses<<endl; // count is always == to numCourses since the graph is guaranteed to be a DAG.
        for(auto i: topoSort) cout<<i<<" "; cout<<endl;
        return ans;
    }
};