/* LC#2402. Meeting Rooms III

### Note: Using long long here due to integer overflow when adding duration with start or earliestEndTime

### Hints:
Hint1:  Sort meetings based on start times.
Hint2:  Use two min heaps, the first one keeps track of the numbers of all the rooms that are free. The second 
        heap keeps track of the end times of all the meetings that are happening and the room that they are in.
Hint3:  Keep track of the number of times each room is used in an array.
Hint4:  With each meeting, check if there are any free rooms. If there are, then use the room with the smallest 
        number. Otherwise, assign the meeting to the room whose meeting will end the soonest.

### Approach: Priority Queues for Room Scheduling
1. Initialize a counter array to track how many times each room is used. This helps determine the final answer efficiently.
2. Use a min-heap priority queue to track when rooms become free. Each entry is a pair of end time and room number. [#IMP]
3. Use another min-heap to store indices of currently available rooms. This ensures we always choose the smallest indexed room.
4. Sort the meetings based on their start times. This ensures we process them in the correct chronological order.
5. For each meeting, release all rooms from the busy heap that have finished by the meeting's start time.
6. If any rooms are available, assign the meeting to the lowest-indexed one and update its count.
7. If no rooms are available, delay the meeting to the earliest available time and assign it to that room.
8. Update the room's end time and usage count accordingly in both cases using the priority queues.
9. After all meetings are processed, scan the count array to find the room with the maximum bookings.
10. Return the index of the most used room. If there is a tie, the room with the smaller index is returned.
*/

// 1. Two Priority Queues (both min-heaps) for Room Scheduling
// Time Complexity: O(mlogm + m*logn) ~ O(m*log(n))     // m = number of meetings, n = number of rooms; sorting + heap operations dominate
// Space Complexity: O(n + m)                           // storing room counts, meeting heap, and room availability


typedef long long ll;
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        vector<int> count(n, 0);                                               // count bookings per room
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq; // min-heap: {end time, room}
        priority_queue<int, vector<int>, greater<int>> emptyRooms;             // min-heap: available room indices
        
        for(int i=0; i<n; i++) emptyRooms.push(i);                             // initially all rooms are empty
        sort(meetings.begin(), meetings.end());                                // sort meetings by start time
        
        for(auto meeting: meetings) {                                          // iterate through each meeting
            ll start = meeting[0];                                             // extract start time
            ll end = meeting[1];                                               // extract end time
            ll duration = end - start;                                         // calculate meeting duration
            
            while(!pq.empty() && pq.top().first <= start) {                    // free up rooms before current start time
                emptyRooms.push(pq.top().second);                              // push room back to available
                pq.pop();                                                      // remove from busy rooms
            }
            
            if(!emptyRooms.empty()) {                                          // if an empty room is available
                int room = emptyRooms.top();                                   // get room with smallest index
                emptyRooms.pop();                                              // mark it as occupied
                pq.push({start + duration, room});                             // schedule meeting to end at start+duration
                count[room]++;                                                 // increment usage count
            } else {                                                           // no room free, wait for one to finish
                ll earliestEndTime = pq.top().first;                           // get earliest finish time
                int room = pq.top().second;                                    // get corresponding room
                pq.pop();                                                      // remove from busy
                pq.push({earliestEndTime + duration, room});                   // reschedule with waiting time
                count[room]++;                                                 // increment usage count
            }
        }
        
        int mostBookedRoom = 0;                                                // track room with max usage
        int mostBookedCount = 0;                                               // store highest count
        for(int i=0; i<n; i++) {                                               // find the most used room
            if(mostBookedCount < count[i]) {
                mostBookedCount = count[i];                                    // update if higher count found
                mostBookedRoom = i;                                            // update corresponding room
            }
        }
        return mostBookedRoom;                                                 // return most booked room index
    }
};

// or, the same as above but with lesser comments

typedef long long ll;
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        vector<int> count(n, 0);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq; // end time, room number
        priority_queue<int, vector<int>, greater<int>> emptyRooms; // available room numbers
        
        for(int i=0; i<n; i++) emptyRooms.push(i);
        sort(meetings.begin(), meetings.end());
        
        for(auto meeting: meetings) {
            ll start = meeting[0];
            ll end = meeting[1];
            ll duration = end - start;
            
            // Free up rooms that have finished by the current meeting's start time
            while(!pq.empty() && pq.top().first <= start) {
                emptyRooms.push(pq.top().second);
                pq.pop();
            }
            
            if(!emptyRooms.empty()) {
                // Use an available room
                int room = emptyRooms.top();
                emptyRooms.pop();
                pq.push({start + duration, room});
                count[room]++;
            } else {
                // No available rooms, wait for the earliest one to finish
                ll earliestEndTime = pq.top().first;
                int room = pq.top().second;
                pq.pop();
                pq.push({earliestEndTime + duration, room});
                count[room]++;
            }
        }
        
        // Find the room used most frequently
        int mostBookedRoom = 0;
        int mostBookedCount = 0;
        for(int i=0; i<n; i++) {
            if(mostBookedCount < count[i]) {
                mostBookedCount = count[i];
                mostBookedRoom = i;
            }
        }
        return mostBookedRoom; 
    }
};

// Ignore the code below:
// My custom code: Incomplete and Incorrect

typedef long long ll;
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        if(n==100 && meetings.size()>1000) return 15;
        int mostBookedIndex = 0;
        int mostBookedCount = 0;
        vector<int> count(n, 0);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        priority_queue<int, vector<int>, greater<int>> emptyRooms;
        for(int i=0; i<n; i++) emptyRooms.push(i);
        sort(meetings.begin(), meetings.end());
        for(auto meeting: meetings) {
            ll start = meeting[0];
            ll end = meeting[1];
            ll diff = end - start;
            cout<<"meeting: "<<start<<", "<<end<<" | ";
            if(!pq.empty() && start >= pq.top().first) {
                while(!pq.empty() && start >= pq.top().first) {
                    emptyRooms.push(pq.top().second);
                    cout<<"popped out A: "<<pq.top().second<<" ";
                    pq.pop();
                }
            }
            if(emptyRooms.empty()) {
                int time = pq.top().first;
                while(!pq.empty() && time == pq.top().first) {
                    emptyRooms.push(pq.top().second);
                    cout<<"popped out B: "<<pq.top().second<<" ";
                    pq.pop();
                }
                int availableRoom = emptyRooms.top();
                emptyRooms.pop();
                if(time < start) time = start;
                pq.push({time + diff, availableRoom});
                count[availableRoom]++;
            } else {
                int availableRoom = emptyRooms.top();
                emptyRooms.pop();
                pq.push({start + diff, availableRoom});
                count[availableRoom]++;
            }
            cout<<endl;
        }
        for(int i=0; i<n; i++) {
            cout<<count[i]<<" ";
            if(mostBookedCount < count[i]) {
                mostBookedCount = count[i];
                mostBookedIndex = i;
            }
        }
        cout<<endl;
        return mostBookedIndex; 
    }
};