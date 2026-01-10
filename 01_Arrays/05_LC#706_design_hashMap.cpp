/* LC#706. Design HashMap

Two methods:
1. Using an array or a vector: O(1)
2. Using a linked list: O(n/k) | TODO

*/

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

/*
### Approach 1: Hash Map Implementation using a vector/array.
1. Use a fixed size vector where each index directly represents a possible key value.
2. Initialize all entries with a default invalid value to indicate absence of key.
3. Put operation assigns the given value directly at the index equal to the key.
4. Get operation retrieves the value directly from the index without any probing or hashing computation.
5. Remove operation resets the index back to default value, effectively deleting the key.
6. Direct addressing avoids collisions entirely and ensures constant time operations.
7. Space usage is proportional to the maximum possible key range supported by the data structure.
*/

// 1. Using a vector/array (My original solution)
// Time Complexity: put -> O(1), get -> O(1), remove -> O(1)
// Space Complexity: O(n)
// where n is 1e6 + 1

class MyHashMap {
    int n;
    vector<int> hashmap;
public:
    MyHashMap() {
        n = 1e6 + 1;
        hashmap.resize(n, -1);      // Since, both key and value varies from 0 to 1,000,000
    }
    
    void put(int key, int value) {
        hashmap[key] = value; 
    }
    
    int get(int key) {
        return hashmap[key];
    }
    
    void remove(int key) {
        hashmap[key] = -1;
    }
};

// or, same as above but using modern default constructor
class MyHashMap {
    vector<int> hashmap;                                            // array-based hash map storage
public:
    MyHashMap(): hashmap(1000001, -1) {}                            // initialize map with default values
    
    void put(int key, int value) {
        hashmap[key] = value;                                       // store value at index key
    }
    
    int get(int key) {
        return hashmap[key];                                        // return value stored at key
    }
    
    void remove(int key) {
        hashmap[key] = -1;                                          // reset key to default empty value
    }
};
