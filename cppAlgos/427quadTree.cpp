/*
// Definition for a QuadTree node.
class Node {
public:
    bool->val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {}

    Node(bool ->val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
       ->val = ->val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/
/*
orientation of grid
tl bl
tr br

*/
class Solution {
public:

    Node* construct(vector<vector<int>>& grid) {
        printGrid(grid);
         return constructHelper(grid,0, grid.size(),0, grid.size());
    }
    
    Node* constructV1(vector<vector<int>>& grid) {
        if (grid.size() == 0) {
            return nullptr;
        }
        if (grid.size() == 1) {
            return new Node(grid[0][0], true, nullptr, nullptr, nullptr, nullptr);
        }
        vector<vector<int>> topLeft, topRight, bottomLeft, bottomRight;
        splitGrid(grid, topLeft, topRight, bottomLeft, bottomRight);
        //cout << "split" << endl;
        //cout << "topLeft" << endl;
        //printGrid(topLeft);
        //cout << "topRight" << endl;
        //printGrid(topRight);
        //cout << "bottomLeft" << endl;
        //printGrid(bottomLeft);
        //cout << "bottomRight" << endl;
        //printGrid(bottomRight);
        Node* topLeftNode = constructV1(topLeft);
        Node* bottomLeftNode = constructV1(topRight);
        Node* topRightNode = constructV1(bottomLeft);
        Node* bottomRightNode = constructV1(bottomRight);
        if (topLeftNode->val == topRightNode->val && bottomLeftNode->val == bottomRightNode->val && topLeftNode->val == bottomLeftNode->val && topLeftNode->isLeaf && topRightNode->isLeaf && bottomLeftNode->isLeaf && bottomRightNode->isLeaf ) {
            return new Node(topLeftNode->val, true, nullptr, nullptr, nullptr, nullptr);
        } 
        return new Node(false, false, topLeftNode, topRightNode, bottomLeftNode, bottomRightNode);
   
        
    }
    
     Node* constructHelper(vector<vector<int>>& grid, int l, int r, int u, int d) {
        if (r == l) {
            return nullptr;
        }
          if (r - l == 1 && d - u == 1) {
           // cout << l << " " << u << " " << grid[l][u] <<  endl;
            return new Node(grid[l][u], true, nullptr, nullptr, nullptr, nullptr);
        }
     //   cout << "topLeft" << endl;
     //   cout << l << l+(r-l)/2 << u << u+(d-u)/2 << endl;
     //   cout << "topRight" << endl;
     //   cout << l+(r-l)/2 << r << u << u+(d-u)/2 << endl;
     //   cout << "bottomLeft" << endl;
     //   cout << l << l+(r-l)/2 << u+(d-u)/2 << d << endl;
     //   cout << "bottomRight" << endl;
     //   cout << l+(r-l)/2 << r << u+(d-u)/2 << d << endl;
     //   cout << "--------------------------------------" << endl;
     //    cout << (r-l)/2 << endl;
        Node* topLeftNode = constructHelper(grid, l, l+(r-l)/2, u, u+(d-u)/2);
        Node* bottomLeftNode = constructHelper(grid,  l+(r-l)/2 , r, u, u+(d-u)/2);
        Node* topRightNode= constructHelper(grid, l, l+(r-l)/2, u+(d-u)/2, d);
        Node* bottomRightNode = constructHelper(grid, l+(r-l)/2, r, u+(d-u)/2, d);
         if (topLeftNode->val == topRightNode->val && bottomLeftNode->val == bottomRightNode->val && topLeftNode->val == bottomLeftNode->val && topLeftNode->isLeaf && topRightNode->isLeaf && bottomLeftNode->isLeaf && bottomRightNode->isLeaf) {
            return new Node(topLeftNode->val, true, nullptr, nullptr, nullptr, nullptr);
        } 
        return new Node(true, false, topLeftNode, topRightNode, bottomLeftNode, bottomRightNode);
   
     }
    
    void printGrid(vector<vector<int>>& grid) {
             for (int i = 0; i < grid.size(); i++) {
                for (int j = 0; j < grid.size(); j++) {
                 cout << grid[i][j];   
                }
                 cout << endl;
             }
    }
    void splitGrid(vector<vector<int>>& grid, vector<vector<int>>& topLeft, vector<vector<int>>& topRight, vector<vector<int>>& bottomLeft, vector<vector<int>>& bottomRight) {
        for (int i = 0; i < grid.size(); i++) {
            vector<int> row;
            for (int j = 0; j < grid.size(); j++) {
                if (i < grid.size()/2) {
                    row.push_back(grid[i][j]);
                    if (j == grid.size()/2 - 1) {
                        topLeft.push_back(row);
                        row.clear();
                    } 
                    if (j == grid.size() - 1) {
                        topRight.push_back(row);
                        row.clear();
                    }
                } else {
                     row.push_back(grid[i][j]);
                     if (j == grid.size()/2 - 1) {
                        bottomLeft.push_back(row);
                        row.clear();
                    } 
                    if (j == grid.size() - 1) {
                        bottomRight.push_back(row);
                        row.clear();
                    }
                     
                }
            }
           
        }
    }
};
