/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};
*/
class Solution {
public:
    Node* connect(Node* root) {
        return connectRecursive(root);
    }
    
    Node* connectRecursive(Node* root) {
         if (root == nullptr) {
             return root;
         }
        Node* l = root->left;
        Node* r = root->right; 
        
        if (l != nullptr) {
            l->next = r;
        }
        if (r != nullptr) {
            if (root->next != nullptr) {
                r->next = root->next->left;
            } else {
                r->next = nullptr;
            }
        }
        connectRecursive(l);
        connectRecursive(r);
        return root;
        
    }
    
    Node* connectWithQueue(Node* root) {
        if (root == nullptr) {
            return root;
        }
        queue<pair<Node*,int>> q;
        
        q.push(pair(root,0));
        pair<Node*,int> curr;
        while(!q.empty()) {
            curr = q.front();
            q.pop();
            if (q.empty()) {
                curr.first->next = nullptr;
            } else {
                if (q.front().second == curr.second)
                curr.first->next = q.front().first;
            }
            if (curr.first->left != nullptr) {
                q.push(pair(curr.first->left,curr.second+1));
            }
             if (curr.first->right != nullptr) {
                q.push(pair(curr.first->right,curr.second+1));
            }
        }

        return root;
    }
};
