/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
private:
    stack<TreeNode*> s;
    TreeNode* it;
    bool hasN;
    TreeNode* getLeftMostTreeNode(TreeNode* root, stack<TreeNode*>& s) {
        for (TreeNode* i = root; i != nullptr; i = i->left) {
            s.push(i);
        }
         if (s.empty()) {
            return nullptr;
        }
        return s.top();
    }
    
public:
    BSTIterator(TreeNode* root) {
        it = getLeftMostTreeNode(root, s);
        if (s.empty()) {
            hasN = false;
        } else {
            hasN = true;
        }
    }
    
    /** @return the next smallest number */
    int next() {
        TreeNode* next = it;
        s.pop();
        it = getLeftMostTreeNode(next->right, s);
         if (it == nullptr) {
            hasN = false;
            it = next;
            return it->val;
        } 
        return next->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return hasN;
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
