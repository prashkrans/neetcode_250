/* LC#721. Accounts Merge

### Hint:
For every pair of emails in the same account, draw an edge between those emails. 
The problem is about enumerating the connected components of this graph.

### Approaches:
1. BFS (Easiest)
2. DFS - Skip as its same as BFS
3. Union Find Algo (Disjoint Set Union) (TODO - [#IMP])

Note: 
- The name can only be inserted at the beginning after sorting the emails [#IMP]
- In methods 1 and 2, we need to create an adjacency list from the given edges while in method 3 we can directly use the edges

### Approach 1: Graph Representation and BFS for Connected Components
1. Represent the accounts as a graph where each email is a node, and an edge exists
between two emails if they belong to the same account.
2. Use an adjacency list (unordered_map<string, vector<string>>) to store the graph,
where each email points to its connected emails.
3. Traverse the accounts to build the adjacency list:
   - For each account, iterate through its emails.
   - Add edges between consecutive emails in the account.
   - If an account has only one email, initialize an empty adjacency list for it.
4. Use a BFS function to find all connected emails (a connected component) starting
from a given email:
   - Use a queue to explore neighbors and a visited set/map to avoid revisiting emails.
   - Add each visited email to the current connected component.
5. For each unvisited email in the adjacency list:
   - Perform BFS to get all connected emails.
   - Sort the connected emails lexicographically to maintain order.
   - Find the account name using the first email in the connected component.
   - Add the account name at the beginning of the sorted emails and append the result
to the final answer.
6. Return the final merged accounts as a vector of vectors, where each vector contains
the account name followed by its sorted emails.
7. Time Complexity:
   - Building the adjacency list takes O(n * m), where n is the number of accounts and
m is the average number of emails per account.
   - BFS traversal for all connected components takes O(n * m).
   - Sorting the emails for each connected component takes O(m * log(m)).
   - Overall complexity is O(n * m * log(m)).
8. Space Complexity:
   - The adjacency list and visited set/map store all emails, which is O(n * m).
*/

// 1. Graph Representation and BFS for Connected Components

// Time Complexity: O(n * m * log(m))
// - n is the number of accounts, and m is the average number of emails per account.
// - Building the adjacency list takes O(n * m).
// - BFS traversal for all connected components takes O(n * m).
// - Sorting the emails for each connected component takes O(m * log(m)).
// - Overall complexity is O(n * m * log(m)).

// Space Complexity: O(n * m)
// - The adjacency list and visited map store all emails, which is O(n * m).


class Solution {
    vector<string> bfs(string &src, unordered_map<string, vector<string>> &adjL, unordered_map<string, int> &visited) {
        vector<string> path;                            // Stores all emails in the current connected component
        queue<string> q;                                // Queue for BFS traversal
        q.push(src);                                    // Start BFS from the source email
        visited[src] = 1;                               // Mark the source email as visited
        while(!q.empty()) {
            string u = q.front();                       // Get the current email
            q.pop();
            path.push_back(u);                          // Add the email to the current path
            for(auto v: adjL[u]) {                      // Traverse all neighbors of the current email
                if(!visited[v]) {                       // If the neighbor is not visited
                    q.push(v);                          // Add it to the queue
                    visited[v] = 1;                     // Mark it as visited
                }
            } 
        }
        return path;                                    // Return all emails in the connected component
    }
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>> ans;                    // Final result to store merged accounts
        unordered_map<string, string> mp;              // Map to store email -> account name
        for(int i = 0; i < accounts.size(); i++) {
            mp[accounts[i][1]] = accounts[i][0];       // Map the first email of each account to the account name
        }
        unordered_map<string, vector<string>> adjL;    // Adjacency list to represent the graph
        for(int i = 0; i < accounts.size(); i++) {
            if(accounts[i].size() == 2)                // If the account has only one email
                adjL[accounts[i][1]] = vector<string>(); // Initialize an empty adjacency list for the email
            for(int j = 2; j < accounts[i].size(); j++) { // Build the graph for accounts with multiple emails
                string u = accounts[i][j - 1];         // Current email
                string v = accounts[i][j];             // Next email
                adjL[u].push_back(v);                  // Add an edge from u to v
                adjL[v].push_back(u);                  // Add an edge from v to u
            }
        }
        unordered_map<string, int> visited;            // Map to track visited emails
        for(auto i: adjL) {                            // Iterate through all emails in the graph
            string u = i.first;                        // Get the current email
            if(!visited[u]) {                          // If the email is not visited
                vector<string> currAccountEmails = bfs(u, adjL, visited); // Perform BFS to get all connected emails
                sort(currAccountEmails.begin(), currAccountEmails.end()); // Sort the emails lexicographically
                string accName;                        // Variable to store the account name
                for(int i = 0; i < currAccountEmails.size(); i++) {
                    if(mp.count(currAccountEmails[i])) { // Find the account name using the first email
                        accName = mp[currAccountEmails[i]];
                        break;
                    }
                }
                currAccountEmails.insert(currAccountEmails.begin(), accName); // Add the account name at the beginning
                ans.push_back(currAccountEmails);       // Add the merged account to the result
            }
        }
        return ans;                                     // Return the final merged accounts
    }
};

/*
### Approach 3: Disjoint Set Union (Union-Find) with Path Compression
1. Each email is treated as a node and a disjoint set is built using union-find to group
emails belonging to the same user.
2. A map `subset` stores each email's parent and its rank (tree height) to optimize unions
and compress paths during lookups.
3. Another map `emailToNameMap` links each email to its user name for final output purposes
based on the original input.
4. For each account, we initialize its emails in the disjoint set if not already present
and perform union operations between them.
5. Union operations merge connected email nodes, ensuring minimal tree height using rank-based
heuristics for efficient queries.
6. After processing all accounts, we identify unique root nodes representing each group or
connected component of emails.
7. For each root, we collect all emails that share this root and group them under the correct
user name from the mapping.
8. The resulting email list is sorted lexicographically and prepended with the account holder’s
name before being added to the final result.
9. Time complexity is nearly linear due to union-find's amortized inverse Ackermann time,
and space is linear in total number of emails.
*/

// 3. Disjoint Set Union (Union-Find) with Path Compression
// Time Complexity: O(m * α(n) + n log n) = O(m + nlogn)
// - m = total number of email entries across all accounts
// - n = number of unique emails (nodes in disjoint set)
// - α(n) = inverse Ackermann function (nearly constant)
// - m * α(n) for union-find operations
// - n log n for sorting emails in components
//
// Space Complexity: O(n)
// - n space for disjoint-set structure
// - n space for email-to-name mapping
// - n space for result vector

class Solution {
    string findSet(string u, unordered_map<string, pair<string, int>> &subset) {
        string parent = subset[u].first;                                 // Get parent of current node
        if(u == parent) return u;                                        // If node is its own parent, it's a root
        return subset[u].first = findSet(parent, subset);                // Path compression while finding root
    }

    void unionOfSets(string u, string v, unordered_map<string, pair<string, int>> &subset) {
        string uRoot = findSet(u, subset);                               // Find root of first element
        string vRoot = findSet(v, subset);                               // Find root of second element
        int uHeight = subset[uRoot].second;                              // Get rank (height) of u's tree
        int vHeight = subset[vRoot].second;                              // Get rank (height) of v's tree
        if(uHeight < vHeight) subset[uRoot].first = vRoot;              // Attach u's tree under v's tree
        else if(uHeight > vHeight) subset[vRoot].first = uRoot;         // Attach v's tree under u's tree
        else {                                                           // If same height, attach and increase rank
            subset[uRoot].first = vRoot;
            subset[vRoot].second++;
        }
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>> ans;                                      // Final result with merged accounts
        unordered_map<string, pair<string, int>> subset;                 // Disjoint set with parent and rank
        unordered_map<string, string> emailToNameMap;                    // Maps each email to account holder's name

        for(auto account: accounts) {
            emailToNameMap[account[1]] = account[0];                     // Assign name to the first email
        }

        for(auto account: accounts) {
            if(account.size() == 2) {                                    // Account has only one email
                if(!subset.count(account[1]))                            // If not already in set
                    subset[account[1]] = {account[1], 0};                // Make it its own parent
            }
            else {
                for(int i=1; i<account.size()-1; i++) {                  // Union adjacent emails
                    if(!subset.count(account[i]))                        // Initialize if not present
                        subset[account[i]] = {account[i], 0};
                    if(!subset.count(account[i+1]))
                        subset[account[i+1]] = {account[i+1], 0};
                    if(findSet(account[i], subset) != findSet(account[i+1], subset)) // If roots differ, union them
                        unionOfSets(account[i], account[i+1], subset);
                    }
                }
            }
        }

        vector<string> rootNodes;                                        // To store unique connected components
        for(auto i: subset) {
            string u = i.first;
            // string parent = i.second.first; is incorrect as it doesn't update the roots
            string parent = findSet(u, subset);                          // Get root representative of the component
            if (u == parent) rootNodes.push_back(u);                     // Store only the root nodes
        }

        for(auto rootNode: rootNodes) {
            vector<string> curr;
            for(auto i: subset) {
                if(findSet(i.first, subset) == rootNode)                // All nodes in this component
                    curr.push_back(i.first);
            }
            sort(curr.begin(), curr.end());                              // Sort emails lexicographically
            string name;
            for(auto email: curr) {                                      // Find associated name
                if(emailToNameMap.count(email)) {
                    name = emailToNameMap[email];
                    break;
                }
            }
            curr.insert(curr.begin(), name);                             // Insert name at beginning
            ans.push_back(curr);                                         // Add to result
        }
        return ans;                                                      // Return merged account groups
    }
};



// 1. or, same as above but without comments and using an unordered_set instead of an unordered_map for visited

class Solution {
    vector<string> bfs(string src, unordered_map<string, vector<string>> &adjL, unordered_set<string> &visited) {
        vector<string> path;
        queue<string> q;
        q.push(src);
        visited.insert(src);
        while(!q.empty()) {
            string u = q.front();
            q.pop();
            path.push_back(u);
            for(auto v: adjL[u]) {
                if(!visited.count(v)) {
                    q.push(v);
                    visited.insert(v);
                }
            } 
        }
        return path;
    }
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>> ans;
        unordered_map<string, string> mp;
        for(int i=0; i<accounts.size(); i++) {
            mp[accounts[i][1]] = accounts[i][0];
        }
        unordered_map<string, vector<string>> adjL;
        for(int i=0; i<accounts.size(); i++) {
            if(accounts[i].size() == 2) adjL[accounts[i][1]] = vector<string>();
            for(int j=2; j<accounts[i].size(); j++) {
                string u = accounts[i][j-1];
                string v = accounts[i][j];
                adjL[u].push_back(v);
                adjL[v].push_back(u);
            }
        }
        unordered_set<string> visited;
        for(auto i: adjL) {
            string u = i.first;
            if(!visited.count(u)) {
                vector<string> currAccountEmails = bfs(u, adjL, visited);
                sort(currAccountEmails.begin(), currAccountEmails.end());
                string accName;
                for(int i=0; i<currAccountEmails.size(); i++) {
                    if(mp.count(currAccountEmails[i])) {
                        accName = mp[currAccountEmails[i]];
                        break;
                    }
                }
                currAccountEmails.insert(currAccountEmails.begin(), accName);
                ans.push_back(currAccountEmails);
            }
        }
        return ans;
    }
};


// 3. or same as above but without comments

class Solution {
    string findSet(string u, unordered_map<string, pair<string, int>> &subset) {
        string parent = subset[u].first;
        if(u == parent) return u;
        return subset[u].first = findSet(parent, subset);
    }

    void unionOfSets(string u, string v, unordered_map<string, pair<string, int>> &subset) {
        string uRoot = findSet(u, subset);
        string vRoot = findSet(v, subset);
        int uHeight = subset[uRoot].second;
        int vHeight = subset[vRoot].second;
        if(uHeight < vHeight) subset[uRoot].first = vRoot;
        else if(uHeight > vHeight) subset[vRoot].first = uRoot;
        else {
            subset[uRoot].first = vRoot;
            subset[vRoot].second++;
        }
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>> ans;
        unordered_map<string, pair<string, int>> subset;
        unordered_map<string, string> emailToNameMap;
        for(auto account: accounts) {
            emailToNameMap[account[1]] = account[0];
        }
        for(auto account: accounts) {
            if(account.size() == 2) {
                if(!subset.count(account[1])) subset[account[1]] = {account[1], 0};
            }
            else {
                for(int i=1; i<account.size()-1; i++) {
                    if(!subset.count(account[i])) subset[account[i]] = {account[i], 0};
                    if(!subset.count(account[i+1])) subset[account[i+1]] = {account[i+1], 0};
                    if(findSet(account[i], subset) != findSet(account[i+1], subset)) {
                        unionOfSets(account[i], account[i+1], subset);
                    }
                }
            }
        }
        vector<string> rootNodes;
        for(auto i: subset) {
            string u = i.first;
            string parent = findSet(u, subset); // string parent = i.second.first; is incorrect as it doesn't update the roots
            if (u == parent) rootNodes.push_back(u);
        }
        // cout<<"numOfConnComp: "<<rootNodes.size()<<endl;
        for(auto rootNode: rootNodes) {
            vector<string> curr;
            for(auto i: subset) {
                if(i.second.first == rootNode) curr.push_back(i.first);
            }
            sort(curr.begin(), curr.end());
            string name;
            for(auto email: curr) {
                if(emailToNameMap.count(email)) {
                    name = emailToNameMap[email];
                    break;
                }
            }
            curr.insert(curr.begin(), name);
            ans.push_back(curr);
        }
        return ans;
    }
};
