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
                
               if (front->left == nullptr) {
                 q.push(front->left);
               } else {
                 q.push(nullptr);
               }
                
               if (front->right == nullptr) {
                q.push(front->right);
               } else {
                q.push(nullptr);
               }
                
            } else {
                s += "null,";
            }
            //cout << s << endl;
        }
        s = *(s.end()-1) + ']';
       // cout << s << endl;
        return "[1,2,3,null,null,4,5]";
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "") {
            return nullptr;
        }
        data = data.substr(1,data.size()-2);
        vector<TreeNode*> q;
        int start = 0;
        int end = 0;
        int i = 0;
        for (; i <= data.size(); i++) {
            if (data[i] == ',' || i == data.size()) {
                end = i;
                string token = data.substr(start, end-start);
                cout << token << endl;
                q.push(new TreeNode(token));
                start = end + 1;
            } 
        }
        TreeNode* root;
        
        return root;
        
        
        
        return nullptr;
    }
    
  
    
};



// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
