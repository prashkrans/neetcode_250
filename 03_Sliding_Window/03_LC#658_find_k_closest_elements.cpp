/* LC#658. Find K Closest Elements

This problem has multiple approaches:
1. Custom comparator
2. Two Pointers
3. Sliding Window (Prefer this method)
4. Binary Search
*/

// 1. Sliding Window (My original solution, 24 min)
// O(3n) ~ O(n) | 0ms, beats 100%
// O(1)
// where n = arr.size()

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res;
        for(auto &i: arr) i = i - x;    // Subtract x from each value
        int minSum = INT_MAX, sum = 0, startIdx = 0;
        for(int i = 0; i < k; i++) {
            sum += abs(arr[i]);         // Note: Use abs value in sum [#IMP]
            minSum = sum;
        }
        for(int i = 1; i <= arr.size() - k; i++) {
            sum = sum - abs(arr[i - 1]) + abs(arr[i + k - 1]);  // Note: Use abs value in sum [#IMP]
            if(sum < minSum) {
                minSum = sum;
                startIdx = i;
            }
        }
        for(int i = startIdx; i < startIdx + k; i++) {  // Add x again to get the acutal arr values
            res.push_back(arr[i] + x);
        }
        return res;
    }
};

// 1b. Sliding Window (My modified solution)
// O(3n)
// O(n) instead of O(1) hence worse

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res, dist;
        for(int i = 0; i < arr.size(); i++) dist.push_back(abs(arr[i] - x));
        int minSum = INT_MAX, sum = 0, startIdx = 0;
        for(int i = 0; i < k; i++) {
            sum += dist[i];
            minSum = sum;
        }
        for(int i = 1; i <= dist.size() - k; i++) {
            sum = sum - dist[i - 1] + dist[i + k - 1];
            if(sum < minSum) {
                minSum = sum;
                startIdx = i;
            }
        }
        for(int i = startIdx; i < startIdx + k; i++) {
            res.push_back(arr[i]);
        }
        return res;
    }
};

// 2a. Custom comparator class
// Time Complexity: O(nlogn + klogk) ~ O(nlogn) due to sorting twice
// Space Complexity: O(1) auxiliary, O(n) total due to sorting

class cmp {
    int x;                                                          // reference value for distance comparison
public:
    cmp(int x) : x(x) {}                                            // constructor initializing reference value
    
    bool operator() (int a, int b) const {
        int diff = abs(a - x) - abs(b - x);                         // compare absolute distances from x
        return diff == 0 ? a < b : diff < 0;                        // tie-break using smaller value
    }
};

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        sort(arr.begin(), arr.end(), cmp(x));                       // sort array by closeness to x
        vector<int> ans = {arr.begin(), arr.begin() + k};           // take first k closest elements
        sort(ans.begin(), ans.end());                               // sort result in ascending order
        return ans;                                                 // return final k elements
    }
};


// 2b. Custom comparator class using lambda function
// O(nlogn + klogk) ~ O(nlogn) due to sorting twice
// O(1) 

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        sort(arr.begin(), arr.end(), [x](int a, int b) { // Using a lambda function
            int diff = abs(a - x) - abs(b - x);
            return diff == 0 ? a < b : diff < 0;
        });
        vector<int> result(arr.begin(), arr.begin() + k);
        sort(result.begin(), result.end());
        return result;
    }
};