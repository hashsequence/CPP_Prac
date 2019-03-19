/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
   
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s = "";
        
        if (root == nullptr) {
            return s;
        }
        
        s = "[";
        queue<TreeNode*> q;
        TreeNode * front;
        q.push(root);
        
        while(!q.empty()) {
            front = q.front();
            q.pop();
            if (front != nullptr) {
                s += to_string(front->val) + ",";
                
               if (front->left != nullptr) {
                 q.push(front->left);
               } else {
                 q.push(nullptr);
               }
                
               if (front->right != nullptr) {
                q.push(front->right);
               } else {
                q.push(nullptr);
               }
                
            } else {
                s += "null,";
            }
          //  cout << s << endl;
        }
        *(s.end()-1) = ']';
       cout << s << endl;
       // return "[1,2,3,null,null,4,56]";
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "") {
            return nullptr;
        }
        data = data.substr(1,data.size()-2);
        queue<TreeNode*> q;
        queue<TreeNode*> levelOrder;
        int start = 0;
        int end = 0;
        int i = 0;
        for (; i <= data.size(); i++) {
            if (data[i] == ',' || i == data.size()) {
                end = i;
                string token = data.substr(start, end-start);
                //cout << token << endl;
                q.push([](string val){return val == "null" ? nullptr : new TreeNode(atoi(val.c_str()));}(token));
                start = end + 1;
            } 
        }
        TreeNode* root = q.front();
        q.pop();
        levelOrder.push(root);
        while (!q.empty()) {
            TreeNode* treePtr = levelOrder.front();
            levelOrder.pop();
            TreeNode* left = q.front();
            q.pop();
            TreeNode* right = q.front();
            q.pop();
            
            if (left != nullptr) {
                treePtr->left = left;
                levelOrder.push(left);
            } 
            if (right != nullptr) {
                treePtr->right = right;
                levelOrder.push(right);
            }
        }
        return root;
    }
    
  
    
};



// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
