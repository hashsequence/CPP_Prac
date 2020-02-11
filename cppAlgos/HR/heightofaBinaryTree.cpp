/*
https://www.hackerrank.com/challenges/tree-height-of-a-binary-tree/problem
*/
#include <bits/stdc++.h>

using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }
/*The tree node has data, left child and right child 
class Node {
    int data;
    Node* left;
    Node* right;
};

*/
    int height(Node* root) {
        // Write your code here.
        if (root == nullptr) {
            return 0;
        }
        stack<Node*> s1;
        stack<Node*> s2;
        int heightCount = -1;

        stack<Node*>* current = &s1;
        stack<Node*>* other = &s2;
        current->push(root);
        while (!current->empty() ) {
            
            Node* currNode = current->top();
            current->pop();
            if (currNode != nullptr && currNode->right != nullptr) {
                other->push(currNode->right);
            }
            if (currNode != nullptr && currNode->left != nullptr) {
                other->push(currNode->left);
            }
            if (current->empty()) {
                std::swap(current, other);
                heightCount++;
            }
        }
        return heightCount;
        
    }

}; //End of Solution

int main() {
  
    Solution myTree;
    Node* root = NULL;
    
    int t;
    int data;

    std::cin >> t;

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }
  
    int height = myTree.height(root);
    
  	std::cout << height;

    return 0;
}
