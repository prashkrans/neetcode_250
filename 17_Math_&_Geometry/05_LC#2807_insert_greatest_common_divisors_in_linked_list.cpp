/* LC#2807. Insert Greatest Common Divisors in Linked List

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// 1. Recursive
// Time complexity: O(n * log(max(a, b)))                           // n = number of nodes, log for gcd computation per pair
// Tpace complexity: O(n)                                           // due to recursion stack and one new node inserted per pair

class Solution {
    int getGcd(int a, int b) {
        if(b == 0) return a;                                        // Base case: return a when b becomes 0
        return getGcd(b, a % b);                                    // Recursive call: gcd(b, a mod b)
    }
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if(!head || !head->next) return head;                       // Base case: if one or no node, return as is
        ListNode* headNext = head->next;                            // Pointer to the next node
        int gcdVal = getGcd(head->val, headNext->val);              // Compute gcd between current and next node values
        ListNode* newNode = new ListNode(gcdVal);                   // Create new node with gcd value
        head->next = newNode;                                       // Link current node to the new node
        newNode->next = insertGreatestCommonDivisors(headNext);     // Recur for the rest of the list
        return head;                                                // Return modified head node
    }
};

// or, the same as above but without comments

class Solution {
    int getGcd(int a, int b) {
        if(b == 0) return a;
        return getGcd(b, a % b);
    }
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* headNext = head->next;
        int gcdVal = getGcd(head->val, headNext->val);
        ListNode* newNode = new ListNode(gcdVal);
        head->next = newNode;
        newNode->next = insertGreatestCommonDivisors(headNext);
        return head;
    }
};


// 2. Iterative (More space efficient than recursive)
// Time complexity: O(n * log(max(a, b)))                             // n = number of nodes, log for gcd computation per pair
// Space complexity: O(1)                                             // iterative approach with constant extra space used

class Solution {
    int getGcd(int a, int b) {
        if(b == 0) return a;                                          // Base case of Euclidean algorithm
        return getGcd(b, a % b);                                      // Recursive call: gcd(b, a mod b)
    }
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if(!head || !head->next) return head;                         // Edge case: if 0 or 1 node, return as is
        ListNode* curr = head;                                        // Start from the head of the list
        while(curr && curr->next) {                                   // Traverse while there is a pair to process
            ListNode* currNext = curr->next;                          // Store next node
            int gcdVal = getGcd(curr->val, currNext->val);            // Compute gcd between current and next node values
            ListNode* newNode = new ListNode(gcdVal);                 // Create a new node with the gcd value
            curr->next = newNode;                                     // Insert new node after current node
            newNode->next = currNext;                                 // Link new node to the next original node
            curr = currNext;                                          // Move to the next pair
        }
        return head;                                                  // Return the modified list
    }
};

// or, same as above but without comments and using in-built gcd function

class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* curr = head;
        while(curr && curr->next) {
            ListNode* currNext = curr->next;
            int gcdVal = gcd(curr->val, currNext->val);         // using in-built gcd() 
            ListNode* newNode = new ListNode(gcdVal);
            curr->next = newNode;
            newNode->next = currNext;
            curr = currNext;     
        }
        return head;
    }
};