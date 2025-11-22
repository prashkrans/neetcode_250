/* LC#1834. Single-Threaded CPU

### Note:
[#IMP] Edge case: CPU can become idle in between i.e. no element in pq while traversing => start > lastExecutionTime

### TODO:
1. Replace triple with a vector of size 3 simply push_back to tasks itself
2. Understand and learn the easier solution

/*
### Approach 1: Task Scheduling Using Min-Heap (Easier to understand than mine but slightly slower tho same running time) - Prefer this
1. Attach each task's original index to preserve execution order after sorting, since result must reflect that.
2. Sort all tasks based on their enqueue times to simulate arrival of tasks in real-world time order.
3. Use a min-heap (priority queue) that prioritizes by processing time and breaks ties by original index.
4. Start time from the enqueue time of the first task, which ensures we do not skip any initial task arrivals.
5. In each loop, push all tasks that have arrived by the current time into the min-heap for scheduling.
6. If the heap is empty, fast-forward time to the next task’s enqueue time to avoid idle waiting unnecessarily.
7. If the heap has tasks, pop the one with shortest processing time, and simulate its execution by updating time.
8. Append the executed task's index to the result vector to track the final order of task execution.
9. Repeat the loop until all tasks are processed and heap becomes empty, ensuring complete task scheduling.
10. Return the collected result vector that contains the indices of tasks in the order they are scheduled.
*/

/*
Approach 1: Task Scheduling Using Min-Heap (Easier to understand than mine but slightly slower tho same running time) - Prefer this
Time Complexity: O(n*log(n))   // sorting + heap operations for n tasks
Space Complexity: O(n)         // for heap and output result array
*/

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();                                               // total number of tasks
        for (int i = 0; i < n; ++i) {                                       // append original index to each task
            tasks[i].push_back(i);                                          // tasks[i] = {enqueueTime, processingTime, index}
        }

        sort(tasks.begin(), tasks.end());                                   // sort tasks by enqueue time

        vector<int> ans;                                                    // result to store execution order
        priority_queue<vector<int>, vector<vector<int>>, greater<>> minHeap; // min-heap: {processingTime, index}

        int i = 0;                                                           // pointer to iterate over sorted tasks
        long long time = tasks[0][0];                                       // initialize current simulation time

        while (!minHeap.empty() || i < n) {                                 // continue until all tasks are processed
            while (i < n && time >= tasks[i][0]) {                          // add all tasks that have arrived by now
                minHeap.push({tasks[i][1], tasks[i][2]});                   // push {processingTime, index} to heap
                i++;
            }

            if (minHeap.empty()) {                                          // if no tasks are available now
                time = tasks[i][0];                                         // jump time to next task's enqueue time
            } else {
                vector<int> top = minHeap.top();                            // get task with least processing time
                minHeap.pop();                                              // remove task from heap
                int procTime = top[0];                                      // extract processing time
                int index = top[1];                                         // extract original index
                time += procTime;                                           // simulate task execution
                ans.push_back(index);                                       // add task index to result
            }
        }
        return ans;                                                         // return execution order
    }
};

// or, same as above but without comments

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        for (int i = 0; i < n; ++i) {
            tasks[i].push_back(i);
        }
        sort(tasks.begin(), tasks.end());

        vector<int> res;
        priority_queue<vector<int>, vector<vector<int>>, greater<>> minHeap;

        int i = 0;
        long long time = tasks[0][0];
        while (!minHeap.empty() || i < n) {
            while (i < n && time >= tasks[i][0]) {
                minHeap.push({tasks[i][1], tasks[i][2]});
                i++;
            }
            if (minHeap.empty()) {
                time = tasks[i][0];
            } else {
                vector<int> top = minHeap.top();
                int procTime = top[0];
                int index = top[1];
                minHeap.pop();
                time += procTime;
                res.push_back(index);
            }
        }
        return res;
    }
};

// or same as above but modified my custom code (faster solution tho same running time of O(nlogn)):

typedef long long ll;                          // Using long long due to integer overflow when adding to get nextStartTime
typedef pair<int, pair<int, int>> triple;
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        vector<triple> tasksWithIndex;
        for(int i=0; i<n; i++) {
            tasksWithIndex.push_back({tasks[i][0], {tasks[i][1], i}});
        }
        sort(tasksWithIndex.begin(), tasksWithIndex.end());
        int i = 0;
        ll time = tasksWithIndex[0].first;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> ans;
        while(i < n || !pq.empty()) {
            while(i < n && time >= tasksWithIndex[i].first) {   // Note: >=
                pq.push({tasksWithIndex[i].second.first, tasksWithIndex[i].second.second});
                i++;
            }
            if(pq.empty()) time = tasksWithIndex[i].first;
            else {
                ans.push_back(pq.top().second);
                time += pq.top().first;
                pq.pop();
            }
        }
        return ans;
    }
};

/*
### Approach 2: CPU Task Scheduling with Min-Heap (My custom code wasted 3 hours) | Wasted because there's no way I remember this
1. Assign an index to each task so we can track their original positions after sorting and scheduling.
2. Sort all tasks by their enqueue time to simulate their arrival in chronological order before any execution.
3. Use a min-heap to select the next task. It prioritizes lower processing time, then smaller index if tied.
4. Initialize the simulation time with the enqueue time of the first task, which ensures we begin at the right point.
5. While processing, add all tasks to the heap whose enqueue time matches the current simulation time (they are available).
6. If the CPU is free and the heap has tasks, pop the top task and execute it by updating the current finish time.
7. If there are more tasks pending, advance time to the smaller of the next task’s arrival or current task’s finish.
8. If all tasks have arrived, just advance time to finish the remaining tasks in the heap without skipping gaps.
9. Repeat until all tasks are added and processed. The heap ensures correct order based on processing time and index.
10. Return the order in which tasks were executed as stored in the result vector after all processing is complete.
*/

/* 2. CPU Task Scheduling with Min-Heap (My custom code wasted 3 hours)
Time Complexity: O(n*log(n))   // sorting tasks and heap operations per task
Space Complexity: O(n)         // for task storage, heap, and output array
*/

typedef long long ll;
typedef pair<int, pair<int, int>> triple;
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();                                              // total number of tasks
        vector<triple> tasksWithIndex;                                     // {enqueueTime, {processingTime, index}}
        
        for(int i=0; i<n; i++) {                                           // attach index to each task
            tasksWithIndex.push_back({tasks[i][0], {tasks[i][1], i}});
        }

        sort(tasksWithIndex.begin(), tasksWithIndex.end());               // sort tasks by enqueue time
        
        int i = 0;                                                         // pointer to iterate over tasks
        ll time = tasksWithIndex[0].first;                                 // simulation time starts from first enqueue
        ll nextStartTime = time;                                           // tracks when current task will finish
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min-heap by {processingTime, index}
        vector<int> ans;                                                  // stores the order of task execution
        
        while(i < n || !pq.empty()) {                                     // continue until all tasks processed
            while(i < n && time == tasksWithIndex[i].first) {             // add tasks available at current time
                pq.push({tasksWithIndex[i].second.first, tasksWithIndex[i].second.second});
                i++;
            }
            if(time >= nextStartTime && !pq.empty()) {                    // if CPU is free and tasks are ready | Note: >= (not ==)
                ans.push_back(pq.top().second);                           // schedule the task with lowest processing time
                nextStartTime = time + pq.top().first;                    // update finish time for current task
                pq.pop();                                                 // remove task from heap
            }
            if(i < n) {                                                   // if more tasks to process
                if(nextStartTime > time)                                  // fast-forward time to next event
                    time = min((ll)tasksWithIndex[i].first, nextStartTime);
                else time = tasksWithIndex[i].first;                      // align time to next task arrival
            }
            else time = nextStartTime;                                    // if all tasks arrived, wait for execution
        }
        return ans;                                                       // return final execution order
    }
};

// or, same as above but with less comments and slightly changed while loop and debug lines

typedef long long ll;                          // Using long long due to integer overflow when adding to get nextStartTime
typedef pair<int, pair<int, int>> triple;
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        vector<triple> tasksWithIndex;
        for(int i=0; i<n; i++) {
            tasksWithIndex.push_back({tasks[i][0], {tasks[i][1], i}});
        }
        sort(tasksWithIndex.begin(), tasksWithIndex.end());
        // for(auto i: tasksWithIndex) cout<<i.first<<", "<<i.second.first<<" | "<<i.second.second<<endl;
        int i = 0;
        ll time = tasksWithIndex[0].first;
        ll nextStartTime = time;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> ans;
        while(true) {
            if(i == n && pq.empty()) break;
            while(i < n && time == tasksWithIndex[i].first) {   // Note: ==
                pq.push({tasksWithIndex[i].second.first, tasksWithIndex[i].second.second});
                i++;
            }
            // cout<<"time: "<<time<<" | i: "<<i<<" | ";
            if(time >= nextStartTime && !pq.empty()) {          // Note: >= (not == )
                ans.push_back(pq.top().second);
                nextStartTime = time + pq.top().first;
                pq.pop();
            }
            // if(i < n) cout<<"tasksWithIndex[i].first: "<<tasksWithIndex[i].first<<" | ";
            // cout<<"nextStartTime: "<<nextStartTime<<" | "<<endl;
            if(i < n) {
                if(nextStartTime > time)                        // Simply using min of these gets stuck in infinite loop
                    time = min((ll)tasksWithIndex[i].first, nextStartTime);
                else time = tasksWithIndex[i].first;
            }
            else time = nextStartTime;
        }
        return ans;
    }
};

// correct code but gets TLE due to slow propagation of time

typedef pair<int, pair<int, int>> triple;
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        vector<triple> tasksWithIndex;
        for(int i=0; i<n; i++) {
            tasksWithIndex.push_back({tasks[i][0], {tasks[i][1], i}});
        }
        sort(tasksWithIndex.begin(), tasksWithIndex.end());
        int i = 0;
        int time = tasksWithIndex[0].first;
        int nextStartTime = time;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> ans;
        while(true) {
            if(i == n && pq.empty()) break;
            while(i < n && time == tasksWithIndex[i].first) {
                pq.push({tasksWithIndex[i].second.first, tasksWithIndex[i].second.second});
                i++;
            }
            if(time == nextStartTime) {
                ans.push_back(pq.top().second);
                nextStartTime = time + pq.top().first;
                pq.pop();
            }
            time++;
        }
        return ans;
    }
};

// Ignore the code below
// The code is incorrect as it doesn't work if {enqTime, procTime} are duplicates
// Else, if the duplicates are not present, this works fine
// Still would get TLE

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        unordered_map<string, int> mp;
        for(int i=0; i<tasks.size(); i++) {
            string key = to_string(tasks[i][0]) + '#' + to_string(tasks[i][1]);
            mp[key] = i;
        }
        sort(tasks.begin(), tasks.end());
        int i = 0;
        int time = tasks[0][0];
        int nextStartTime = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> ans;
        while(true) {
            if(i == tasks.size() && pq.empty()) break;
            while(i < tasks.size() && time == tasks[i][0]) {
                string key = to_string(tasks[i][0]) + '#' + to_string(tasks[i][1]);
                pq.push({tasks[i][1], mp[key]});
                i++;
            }
            if(time >= nextStartTime) {
                ans.push_back(pq.top().second);
                nextStartTime = time + pq.top().first;
                pq.pop();
            }
            time++;
        }
        return ans;
    }
};