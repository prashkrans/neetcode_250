/* LC#2709. Greatest Common Divisor Traversal (Gets TLE 918/929 - TODO)

TODO - the approach is correct but gets TLE so, fix it later

### Approach: Graph Representation and Connected Components
1. **Prime Factorization**:
   - For each number in the array, find its prime factors.
   - Use the Sieve of Eratosthenes to efficiently generate prime numbers up to the maximum number in the array.
   - For each number, connect its prime factors in an undirected graph.

2. **Graph Construction**:
   - Represent the graph using an adjacency list.
   - Each prime factor is a node, and an edge exists between two prime factors if they belong to the same number.
   - For example, if a number has prime factors 2, 3, and 5, the graph will have edges 2-3, 3-5, and 2-5.

3. **DFS for Connected Components**:
   - Perform a DFS traversal to count the number of connected components in the graph.
   - A connected component represents a group of numbers that can be traversed using their prime factors.

4. **Check Connectivity**:
   - If there is exactly one connected component, all numbers in the array can be traversed using their prime factors.
   - Otherwise, return false.

5. **Special Cases**:
   - If the array contains a `1`, return false because `1` has no prime factors.
   - If the array has only one number, return true because it is trivially connected.

6. **Time Complexity**:
   - Calculating prime factors for each number takes O(sqrt(max(nums))) per number.
   - Using the Sieve of Eratosthenes for prime generation takes O(max(nums) * log(log(max(nums)))).
   - DFS traversal takes O(V + E), where V is the number of unique prime factors and E is the number of edges in the graph.
   - Overall complexity is O(n * sqrt(max(nums)) + V + E).

7. **Space Complexity**:
   - The adjacency list requires O(V + E) space to store the graph.
   - The `visited` map requires O(V) space to track visited nodes.
*/

// Time Complexity: O(n * sqrt(max(nums)) + V + E)
// - Calculating prime factors for each number takes O(sqrt(max(nums))) per number, where max(nums) is the largest number in the array.
// - Using the Sieve of Eratosthenes for prime generation takes O(max(nums) * log(log(max(nums)))). However, this is amortized over all numbers.
// - DFS traversal takes O(V + E), where V is the number of unique prime factors and E is the number of edges in the graph.
// - Overall complexity is O(n * sqrt(max(nums)) + V + E).

// Space Complexity: O(V + E)
// - The adjacency list requires O(V + E) space to store the graph.
// - The `visited` map requires O(V) space to track visited nodes.

class Solution {    
    void primeFactors(int n, unordered_map<int, unordered_set<int>> &adjL) {
        vector<bool> isPrime(n+1, true);                // Sieve of Eratosthenes to find prime numbers
        isPrime[0] = false, isPrime[1] = false;         // 0 and 1 are not prime
        for(int i = 2; i * i <= n; i++) {               // Mark non-prime numbers
            if(isPrime[i]) {
                for(int j = i * i; j <= n; j += i) isPrime[j] = false; 
            }
        }
        vector<int> primes;                             // Store prime factors of n
        for(int i = 2; i <= n; i++) {                   // Collect prime factors of n
            if(isPrime[i] && (n % i == 0)) primes.push_back(i);
        }
        for(int i = 0; i < primes.size(); i++) {        // Build adjacency list for prime factors
            if(i == 0) {
                if(adjL.count(primes[i]) == 0) adjL[primes[i]] = unordered_set<int>();
            } else {
                adjL[primes[i]].insert(primes[i - 1]);  // Connect current prime to the previous prime
                adjL[primes[i - 1]].insert(primes[i]);  // Connect previous prime to the current prime
            }
        }
    }
    
    void dfs(int u, unordered_map<int, unordered_set<int>> &adjL, unordered_map<int, int> &visited) {
        visited[u] = 1;                                 // Mark the current node as visited
        for(auto v: adjL[u]) {                          // Traverse all neighbors
            if(!visited[v]) dfs(v, adjL, visited);      // Recursively visit unvisited neighbors
        }
    }

public:
    bool canTraverseAllPairs(vector<int>& nums) {
        if(nums.size() == 0 || nums.size() == 1) return true; // Single element or empty array is trivially connected
        unordered_map<int, unordered_set<int>> adjL;          // Adjacency list for prime factors
        unordered_set<int> seen;                             // Track processed numbers
        for(int i = 0; i < nums.size(); i++) {
            if(seen.find(nums[i]) != seen.end()) continue;    // Skip already processed numbers
            if(nums[i] == 1) return false;                   // If 1 is present, return false
            primeFactors(nums[i], adjL);                     // Add prime factors to the graph
            seen.insert(nums[i]);                            // Mark the number as processed
        }
        unordered_map<int, int> visited;                     // Track visited nodes during DFS
        int numOfConnComp = 0;                               // Count connected components
        for(auto i: adjL) {                                  // Traverse all nodes in the graph
            int u = i.first;
            if(!visited[u]) {                                // If the node is not visited
                dfs(u, adjL, visited);                       // Perform DFS to visit all connected nodes
                numOfConnComp++;                             // Increment the count of connected components
            }
        }
        return (numOfConnComp == 1);                         // Return true if there is exactly one connected component
    }
};


// 1b. Without using the Sieve of Eratosthenes
// Gets TLE at 917/929 
// My custom code
class Solution {
    bool isPrime(int n) {
        for(int i=2; i*i <= n; i++) {
            if(n % i == 0) return false;
        }
        return true;
    }
    void primeFactors(int n, unordered_map<int, unordered_set<int>> &adjL) {
        int prev = -1;
        for(int i=2; i<=n; i++) {   // Don't include 1
            if(isPrime(i) && n % i == 0) {
                if(prev != -1) {
                    adjL[prev].insert(i);
                    adjL[i].insert(prev);
                }
                else {
                    if(adjL.count(i) == 0) adjL[i] = unordered_set<int>();
                }
                prev = i;
            }
        }
    }

    void dfs(int u, unordered_map<int, unordered_set<int>> &adjL, unordered_map<int, int> &visited) {
        visited[u] = 1;
        for(auto v: adjL[u]) {
            if(!visited[v]) dfs(v, adjL, visited);
        }
    }

public:
    bool canTraverseAllPairs(vector<int>& nums) {
        if(nums.size() == 0 || nums.size() == 1) return true;
        unordered_map<int, unordered_set<int>> adjL;
        unordered_set<int> seen;
        for(int i=0; i<nums.size(); i++) {
            if(seen.find(nums[i]) != seen.end()) continue;
            if(nums[i] == 1) return false; // [#IMP] - if even a single 1 is present return false
            primeFactors(nums[i], adjL);
            seen.insert(nums[i]);
        }
        // for(auto i: adjL) {
        //     int u = i.first;
        //     cout<<u<<" -> ";
        //     for(auto v: adjL[u]) cout<<v<<" ";
        //     cout<<endl;
        // }
        unordered_map<int, int> visited;
        int numOfConnComp = 0;
        for(auto i: adjL) {
            int u = i.first;
            if(!visited[u]) {
                dfs(u, adjL, visited);
                numOfConnComp++;
            }
        }
        // cout<<"numOfConnComp: "<<numOfConnComp<<endl;
        return (numOfConnComp == 1);
    }
};