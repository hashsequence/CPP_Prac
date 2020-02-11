/*
https://www.hackerrank.com/challenges/tree-level-order-traversal/problem
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
/*
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
*/

    void levelOrder(Node * root) {
        if (root == nullptr) {
            return;
        }
        queue<Node*> q1;
        queue<Node*> q2;

        queue<Node*>* current = &q1;
        queue<Node*>* other = &q2;
        current->push(root);

        while(!current->empty()) {
            Node* currNode = current->front();
            cout << currNode->data << " ";
            current->pop();
            
                if (currNode->left != nullptr) {
                other->push(currNode->left);
                }
                if (currNode->right != nullptr) {
                other->push(currNode->right);
                }
            
            if (current->empty()) {
                std::swap(current,other);
            }
        }
        cout << endl;
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
  
	myTree.levelOrder(root);
    return 0;
}
