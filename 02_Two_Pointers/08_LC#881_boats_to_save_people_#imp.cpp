/*  LC#881. Boats to Save People

It's easy focus on the constraints after sorting the array
*/

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int ans = 0, left = 0, right = people.size() - 1;
        sort(people.begin(), people.end());
        while(left <= right) {
            int remainingLimit = limit - people[right];
            if (left <= right && remainingLimit >= people[left]) { // Since, the boat can carry atmost two people
                left++;
            }
            right--;    // One boat carries either right or right + left i.e. one or two
            ans++;
        }
        return ans;
    }
};