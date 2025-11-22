class cmp {
public:
    bool operator() (vector<vector<int>> &a, vector<vector<int>> &b) const {
        return a[1] < b[1];
    }
};
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        sort(trips.begin(), trips.end(), cmp());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for(auto trip: trips) {
            if(pq.empty()) {
                pq.push({trip[2], trip[0]});
            }
            else {
                if(trip[1] >= pq.top().first) pq.push({trip[2], trip[0]});
                else {
                    pair<int, int> top = pq.top(); pq.pop();
                    int shortestEndDist = top.first;
                    int prevCapacity = top.second;
                    int currCapacity = trip[0];
                    if(prevCapacity + currCapacity > capacity) return false;
                    pq.push({trip[2], trip[0]})
                }
            }
        }
        return true;
    }
};