/* LC#705. Design HashSet

Multiple methods:
1. Brute Force
2. Using an array or a vector: O(1)
3. Using a linked list: O(n/k) | TODO
*/

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

/*
### Approach 2: Hash Set Implementation using a vector/array.
1. Use a fixed size boolean vector where each index corresponds to a possible key value.
2. Initialize all positions as false to represent empty set state.
3. Add operation sets the index corresponding to key as true to mark presence.
4. Remove operation resets the index back to false to mark absence of key.
5. Contains operation directly checks the boolean value at the index equal to key.
6. Direct addressing eliminates collisions and ensures constant time operations.
7. Space usage depends on the maximum allowed key range.
*/

// 2. Using a vector/array (My original solution)
// Time Complexity: add -> O(1), remove -> O(1), contains -> O(1)
// Space Complexity: O(n)
// where n is 1e6 + 1

class MyHashSet {
    vector<bool> hashSet;                                           // direct addressing boolean storage
public: 
    MyHashSet(): hashSet(1e6 + 1, false) {}                         // Since, key varies from 0 to 1,000,000 and initialize all keys as absent
    
    void add(int key) {
        hashSet[key] = true;                                        // mark key as present
    }
    
    void remove(int key) {
        hashSet[key] = false;                                       // mark key as absent
    }
    
    bool contains(int key) {
        return hashSet[key];                                        // check presence of key
    }
};
