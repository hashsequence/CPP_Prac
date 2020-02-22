/*
138. Copy List with Random Pointer
Medium


A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

The Linked List is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) where random pointer points to, or null if it does not point to any node.
 

Example 1:


Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Example 2:


Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Example 3:



Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]
Example 4:

Input: head = []
Output: []
Explanation: Given linked list is empty (null pointer), so return null.
 

Constraints:

-10000 <= Node.val <= 10000
Node.random is null or pointing to a node in the linked list.
Number of Nodes will not exceed 1000.


*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

solution:

I need a mapping between the node to index for the original list  unordered_map<Node*,int> nodeToIndex
I need to index the newlist so we have vector<Node*> indexToNewNode

as we iterate over the original list we form the new list and index the newlist 
as well as map the node of the original nodes to the index

we iterate over the list again but this time we can figure out the mapping of the random pointers by index
and map that over to the new list : currN->random = indexToNewNode[nodeToIndex[curr->random]];

this is O(n)
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return head;
        }
        Node* currN;
        unordered_map<Node*,int> nodeToIndex;
        vector<Node*> indexToNewNode;
        
        
        int i = 0;
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            nodeToIndex[curr] = i;
            currN = new Node(curr->val);
            indexToNewNode.push_back(currN);
            if (i > 0) {
                indexToNewNode[i-1]->next = currN;
            }
            i++;
            currN = currN->next;
        }
        currN = indexToNewNode[0];
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            if (curr->random != nullptr) {
                currN->random = indexToNewNode[nodeToIndex[curr->random]];
            } 
            currN = currN->next;
        }
           
        
        return indexToNewNode[0];
        
    }
};
/*
a better solution is 
mapping between the original nodes to the corresponding new nodes
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> copies;
        copies[nullptr] = nullptr;
        
        for (auto current = head; current != nullptr; current = current->next) {
            Node* copy = new Node(current->val);
            copies[current] = copy;
        }
        
        for (auto current = head; current != nullptr; current = current->next) {
            copies[current]->next = copies[current->next];
            copies[current]->random = copies[current->random];
        }
        
        return copies[head];
    }
};

*/
