/* LC#698. Partition to K Equal Sum Subsets

LC#473. Matchsticks to Square is a special case of this problem where k = 4

Three ways to solve this problem:
1.  Skip or take the current matchstick, we form a subset if current sum == target and then k is reduced by 1. 
    Continue to do this until k == 0. If k == 0, ans is true else false. [TODO]
2.  A polygon of k sides where all sides are equal and all the elements of the array are used
3.  DP with bit masking. [TODO]

TODO 1 and 3

*/

// 2a. A polygon of k sides
// Time Complexity: O(k^n)
// - At each step, we have k choices to place the current number into one of the k subsets.
// - This results in a time complexity of O(k^n), where n is the number of elements in the array.

// Space Complexity: O(k + n) ~ O(n) since n > k
// - The recursion stack can go as deep as n, where n is the size of the input array.
// - Additional space is used for the `sides` vector of size k.

class Solution {
    bool rec(int i, vector<int> &nums, int targetSide, vector<int> &sides) {
        for(int j = 0; j < sides.size(); j++) {                 // Prune invalid states where any side exceeds the target length
            if(sides[j] > targetSide) return false;
        }
        if(i == nums.size()) {                                  // Base case: all numbers are used
            for(int j = 0; j < sides.size(); j++) {             // Check if all sides are equal to the target length
                if(sides[j] != targetSide) return false;
            }
            return true;
        }
        for(int j = 0; j < sides.size(); j++) {                 // Try placing the current number into each subset
            if(j > 0 && sides[j] == sides[j - 1]) continue;     // Skip duplicate states
            sides[j] += nums[i];                                // Add the current number to subset j
            if(rec(i + 1, nums, targetSide, sides)) return true; // Recurse for the next number
            sides[j] -= nums[i];                                // Backtrack: remove the number from subset j
        }
        return false;                                           // If no valid placement is found, return false
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for(int i = 0; i < nums.size(); i++) sum += nums[i];    // Calculate the total sum of the array
        if(sum % k != 0) return false;                          // If the total sum is not divisible by k, return false

        int targetSide = sum / k;                               // Calculate the target sum for each subset
        for(int i = 0; i < nums.size(); i++) {                  // Check if any number is greater than the target sum
            if(nums[i] > targetSide) return false;
        }

        sort(nums.begin(), nums.end(), greater<int>());         // Sort the array in descending order for optimization
        vector<int> sides(k, 0);                                // Initialize k subsets with sum 0
        return rec(0, nums, targetSide, sides);                 // Start the recursion
    }
};

// 2b. A polygon of k sides (same as above but with lesser path pruning)
// The only diff: if(j > 0 && sides[j] == sides[j - 1]) continue; 
// Gets TLE

class Solution {
    bool rec(int i, vector<int> &nums, int targetSide, vector<int> &sides) {
        for(int j=0; j<sides.size(); j++) if(sides[j] > targetSide) return false;
        if(i == nums.size()) {
            for(int j=0; j<sides.size(); j++) {
                if(sides[j] != targetSide) return false;
            }
            return true;
        }
        for(int j=0; j<sides.size(); j++) {
            sides[j] += nums[i];
            if(rec(i+1, nums, targetSide, sides)) return true;
            sides[j] -= nums[i];
        }
        return false;
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for(int i=0; i<nums.size(); i++) sum += nums[i];
        if(sum % k != 0) return false;
        sort(nums.begin(), nums.end(), greater<int>());
        int targetSide = sum / k;
        vector<int> sides(k, 0);
        return rec(0, nums, targetSide, sides);
    }
};






// #########################################################
// Ignore the codes below this line



class Solution {
    void rec(int i, vector<int>&nums, int target, int &k) {
        if(target < 0) return;
        if(i == nums.size()) {
            cout<<"target: "<<target<<" k: "<<k<<endl;
            if(target == 0) k--;
            return;
        }
        rec(i+1, nums, target - nums[i], k);
        rec(i+1, nums, target, k);
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for(int i=0; i<nums.size(); i++) sum += nums[i];
        if(sum % k != 0) return false;
        int target = sum / k;
        cout<<target<<endl;
        rec(0, nums, target, k);
        return (k == 0);
    }
};



class Solution {
    void rec(int i, vector<int>&nums, int target, int &k, vector<int> &path) {
        if(target < 0) return;
        if(i == nums.size()) {
            for(int j=0; j<path.size(); j++) cout<<path[j]<<" ";
            cout<<"target: "<<target<<" k: "<<k<<endl;
            if(target == 0) k--;
            return;
        }
        path.push_back(nums[i]);
        rec(i+1, nums, target - nums[i], k, path);
        path.pop_back();
        // int j = i;
        // while(j<nums.size() && nums[j] == nums[i]) j++;
        rec(j, nums, target, k, path);
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for(int i=0; i<nums.size(); i++) sum += nums[i];
        if(sum % k != 0) return false;
        // sort(nums.begin(), nums.end());
        int target = sum / k;
        cout<<target<<endl;
        vector<int> path;
        rec(0, nums, target, k, path);
        return (k == 0);
    }
};


class Solution {
    unordered_set<int> st;
    bool rec(int i, vector<int>&nums, int subsetSum, int target, int k) {
        if(k==0) return true;
        if(subsetSum > target) return false;
        if(st.size() == nums.size()) return (k==0);
        if(i == nums.size()) {
            cout<<"subsetSum: "<<subsetSum<<" target: "<<target<<endl;
            if(subsetSum == target) {
                return rec(0, nums, 0, target, k-1);
            }
            return false;
        }
        bool take = false;
        bool skip = false;
        if(st.find(i) == st.end()) {
            st.insert(i);
            take = rec(i+1, nums, subsetSum + nums[i], target, k);
            st.erase(i);
        }
        skip = rec(i+1, nums, subsetSum, target, k);
        return skip || take;
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for(int i=0; i<nums.size(); i++) sum += nums[i];
        if(sum % k != 0) return false;
        sort(nums.begin(), nums.end(), greater<int>());
        int target = sum / k;
        cout<<target<<endl;
        return rec(0, nums, 0, target, k);
    }
};