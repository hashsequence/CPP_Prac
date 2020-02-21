/*
545. Boundary of Binary Tree
Medium

Given a binary tree, return the values of its boundary in anti-clockwise direction starting from root. Boundary includes left boundary, leaves, and right boundary in order without duplicate nodes.  (The values of the nodes may still be duplicates.)

Left boundary is defined as the path from root to the left-most node. Right boundary is defined as the path from root to the right-most node. If the root doesn't have left subtree or right subtree, then the root itself is left boundary or right boundary. Note this definition only applies to the input binary tree, and not applies to any subtrees.

The left-most node is defined as a leaf node you could reach when you always firstly travel to the left subtree if exists. If not, travel to the right subtree. Repeat until you reach a leaf node.

The right-most node is also defined by the same way with left and right exchanged.

Example 1

Input:
  1
   \
    2
   / \
  3   4

Ouput:
[1, 3, 4, 2]

Explanation:
The root doesn't have left subtree, so the root itself is left boundary.
The leaves are node 3 and 4.
The right boundary are node 1,2,4. Note the anti-clockwise direction means you should output reversed right boundary.
So order them in anti-clockwise without duplicates and we have [1,3,4,2].
 

Example 2

Input:
    ____1_____
   /          \
  2            3
 / \          / 
4   5        6   
   / \      / \
  7   8    9  10  
       
Ouput:
[1,2,4,7,8,9,10,6,3]

Explanation:
The left boundary are node 1,2,4. (4 is the left-most node according to definition)
The leaves are node 4,7,8,9,10.
The right boundary are node 1,3,6,10. (10 is the right-most node).
So order them in anti-clockwise without duplicate nodes we have [1,2,4,7,8,9,10,6,3].
solution:
make seperate functions to dfs leaves, left, and right boundaries

note: if the root has no left subtree then left boundary is only root
if there is no right subtree of the root then there is no right subtree
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void dfsLeaves(vector<int>& res, TreeNode* current) {
        if (current-> left == nullptr && current->right == nullptr) {
            res.push_back(current->val);
        }
        if (current->left != nullptr) {
            dfsLeaves(res, current->left);
        }
        if (current->right != nullptr) {
            dfsLeaves(res, current->right);
        }
    }
    
    void dfsLeft(vector<int>& res, TreeNode* current) {
        if (current-> left == nullptr && current->right == nullptr) {
            return;
        }
        if (current->left != nullptr) {
            res.push_back(current->val);
            dfsLeft(res, current->left);
        } else if (current->right != nullptr) {
            res.push_back(current->val);
            dfsLeft(res, current->right);
        }
    }
    void dfsRight(vector<int>& res, TreeNode* current) {
        if (current-> left == nullptr && current->right == nullptr) {
            return;
        }
        if (current->right != nullptr) {
            dfsRight(res, current->right);
            res.push_back(current->val);
        } else if (current->left != nullptr) {
            dfsRight(res, current->left);
            res.push_back(current->val);
        }
    }
    
    void dfs(vector<int>& res, TreeNode* current) {
        //edge cases
        if (current == nullptr) {
            return;
        }
        if (current-> left == nullptr && current->right == nullptr) {
            res.push_back(current->val);
            return;
        }
        
        //first case if there are subtree for left and right
        if (current-> left != nullptr && current->right != nullptr) {
            //cout <<"first case" << endl;
            dfsLeft(res, current);
            dfsLeaves(res,current);
            dfsRight(res,current->right);
            //second case there is only a left subtree, so no right boundary
        } else if (current-> left != nullptr && current->right == nullptr) {
            //cout <<"second case" << endl;
            res.push_back(current->val);
            dfsLeft(res, current->left);
            dfsLeaves(res,current->left);
            //third case there is only a right subtree so no left boundary
        } else if (current-> left == nullptr && current->right != nullptr) {
            //cout <<"third case" << endl;
            res.push_back(current->val);
            dfsLeaves(res,current->right);
            dfsRight(res, current->right);
        }
    }
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        vector<int> res;
        dfs(res,root);
        return res;
    }
};
