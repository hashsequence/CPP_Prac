/*
1192. Critical Connections in a Network
Hard



Share
There are n servers numbered from 0 to n-1 connected by undirected server-to-server connections forming a network where connections[i] = [a, b] represents a connection between servers a and b. Any server can reach any other server directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some server unable to reach some other server.

Return all critical connections in the network in any order.

 

Example 1:



Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.
 

Constraints:

1 <= n <= 10^5
n-1 <= connections.length <= 10^5
connections[i][0] != connections[i][1]
There are no repeated connections.

solution:
https://www.geeksforgeeks.org/bridge-in-a-graph/

basically the problem reduces to finding the bridges of a graph
first we must know to use an adjacent edge list
then we must know to use dfs to traverse the graph via adjacecy list

the hard part is knowing when the edge is indeed a bridge,

we use the discovery array to keep track of when the vertex is first encountered
we use a lowest array to keep track of the earliest that this vertex can be reached from 
the arbritray starting point

we use a visited array to keep track of which vertex has been traversed already
*/
class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        //initialize adjacency list
        unordered_map<int,vector<int>> adj;
        for (int i = 0; i < connections.size(); i++) {
            adj[connections[i][0]].push_back(connections[i][1]);
            adj[connections[i][1]].push_back(connections[i][0]);
        }
        vector<bool> visited(n, false);
        vector<int> low(n);
        vector<int> disc(n);
        vector<int> parent(n);
        vector<vector<int>> res;
        int time = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                Dfs(res, adj, visited, low, disc, i, -1, time);
            }
        }
        return res;
    }
    
    void Dfs(vector<vector<int>>& res, unordered_map<int,vector<int>>& adj, vector<bool>& visited, vector<int>& low, vector<int>& disc, int current, int parentOfCurrent, int& time) {
        //mark current vertex as visited
        visited[current] = true;
        //increment time
        time++;
        //mark discovery time as now
        disc[current] = time;
        //mark lowest time as now
        low[current] = time;
        //iterate over adjacency list for current
        for (vector<int>::iterator it = adj[current].begin(); it != adj[current].end(); it++) {
            int next = *it;
            //here is the hard part
            //if we have not visited it we can further dfs it
            if (!visited[next]) {
                Dfs(res, adj, visited, low, disc, next, current, time);
                //we set the lowest time of current to the minimum of current and next
                //if the min changes to the low[next] then we know that next a connection to some ancestor to current
                low[current] = min(low[current], low[next]);
                //if the discovery time of current is less than the lowest time of the next vertex then we know 
                //that this is the only path to that next vertex, making the edge current -- next a bridge
                if ( disc[current] < low[next]) {
                    res.push_back({current, next});
                }
            } else if (next != parentOfCurrent){
                //if the next vertex is not visited and not a parent of current
                //we update the lowest time of current to the minimum of lowest time of current and the discovery time of the next
                //the logic is that if we discovered the next vertex at an earlier time, then the lowest of current should be the discovery time of the next vertex
                low[current] = min(low[current], disc[next]);
            } 
        }
    }
};
