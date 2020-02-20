/*
200. Number of Islands
Medium

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1
Example 2:

Input:
11000
11000
00100
00011

Output: 3

solution:
iterate over grid, when you see '1' dfs the islands and mark it
and increment numIslands 
*/
class Solution {
public:
     void Dfs(vector<vector<char>>& grid, int i, int j) {
        stack<pair<int,int>> s;
        s.push(make_pair(i, j));
        while (!s.empty()) {
            pair<int,int> curr = s.top();
            s.pop();
            grid[curr.first][curr.second] = '0';
            int i = curr.first;
            int j = curr.second;
            //cout << i << " " << j << endl;
            if (i-1 >=0 && grid[i-1][j] == '1') 
            {
                s.push(make_pair(i-1,j));
            }
            if (j-1 >=0  && grid[i][j-1] == '1') 
            {
                s.push(make_pair(i,j-1));
            }
            if (i+1 < grid.size() && grid[i+1][j] == '1') 
            {
                s.push(make_pair(i+1,j));
            }
            if (j+1 < grid[0].size()  && grid[i][j+1] == '1') 
            {
                s.push(make_pair(i,j+1));
            }
        }
    }
    
    int numIslands(vector<vector<char>>& grid) {
        if (grid.size() == 0) {
            return 0;
        }
        int numIslands = 0;
        
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '1') {
                    numIslands++;
                    Dfs(grid, i, j);
                }
            }
        }
        return numIslands;
    }
    
};



