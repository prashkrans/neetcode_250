/* LC#1094. Car Pooling
*/


// 1. Brute force with sorting  
// Time Complexity: O(nlogn + n^2) ~ O(n^2)
// Space Complexity: O(1)
// where n = trips.size();

class Solution {                                                                        // Defines the Solution class
public:                                                                                 // Public access specifier
    bool carPooling(vector<vector<int>>& trips, int capacity) {                         // Checks if car pooling is feasible
        sort(trips.begin(), trips.end(), cmp());                                        // Sort trips using custom comparator
        int n = trips.size();                                                           // Store number of trips
        for(int i = 0; i < n; i++) {                                                    // Iterate over each trip as current
            int currPeople = trips[i][0];                                               // Initialize passengers for current trip
            for(int j = 0; j < i; j++) {                                                // Check all previous trips
                if(trips[j][2] > trips[i][1]) currPeople += trips[j][0];                // Add overlapping passengers
            }
            if(currPeople > capacity) return false;                                     // Capacity exceeded, return false
        }
        return true;                                                                    // All trips fit within capacity
    }
};

/*
### Approach 2: Sorting with Min Heap Passenger Tracking
1. Sort all trips by pickup location so trips are processed in correct chronological spatial order.
2. Use a min heap storing drop location and passenger count to track active ongoing trips efficiently.
3. Before each pickup, remove all trips whose drop location is less than or equal to pickup.
4. Subtract passengers of completed trips from current passenger count using heap removals.
5. Add passengers of the current trip after clearing completed trips from active set.
6. If passenger count exceeds capacity at any step, immediately return false.
7. Sorting ensures order, while heap guarantees efficient overlap management in logarithmic time.
*/

// 2. MinHeap of {drop, passengers} (Prefer this approach as the same concept is repeated in other problems)
// Time Complexity: O(n log n) due to both sorting and minheap operations
// Space Complexity: O(n) due to the minheap
// where n = trips.size();

class cmp {                                                                             // Comparator class for sorting trips
public:                                                                                 // Public access specifier
    bool operator() (vector<int> a, vector<int> b) const {                              // Compare two trips by pickup location
        return a[1] < b[1];                                                             // Sort trips in ascending pickup order
    }
};

class Solution {                                                                        
public:                                                                                 
    bool carPooling(vector<vector<int>>& trips, int capacity) {                         // Determines if pooling is possible
        sort(trips.begin(), trips.end(), cmp());                                        // Sort trips by pickup location
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;      // Min heap storing drop point and passengers

        for(int i = 0; i < trips.size(); i++) {                                         // Iterate over all trips
            minHeap.push({trips[i][2], trips[i][0]});                                   // Push drop location with passenger count
        }

        int currPassengers = 0;                                                         // Tracks passengers currently in the car
        for(int i = 0; i < trips.size(); i++) {                                         // Process trips in pickup order
            int passengers = trips[i][0];                                               // Number of passengers to pick up
            int currPickup = trips[i][1];                                               // Current pickup location
            
            while(!minHeap.empty() && minHeap.top().first <= currPickup) {              // Remove completed trips before pickup
                currPassengers -= minHeap.top().second;                                 // Subtract passengers getting down
                minHeap.pop();                                                          // Remove finished trip from heap
            }

            currPassengers += passengers;                                               // Add passengers from current trip
            if(currPassengers > capacity) return false;                                 // Capacity exceeded, return false
        }
        return true;                                                                    // All trips satisfied within capacity
    }
};

// same as above but slightly compact and uses a lambda comparator

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        sort(trips.begin(), trips.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap; // [end, numPassengers]
        int curPass = 0;

        for (const auto& trip : trips) {
            int numPass = trip[0], start = trip[1], end = trip[2];

            while (!minHeap.empty() && minHeap.top().first <= start) {
                curPass -= minHeap.top().second;
                minHeap.pop();
            }

            curPass += numPass;
            if (curPass > capacity) {
                return false;
            }

            minHeap.emplace(end, numPass);
        }

        return true;
    }
};

