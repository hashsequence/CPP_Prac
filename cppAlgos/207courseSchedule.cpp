/*
207. Course Schedule
Medium


There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

Example 1:

Input: 2, [[1,0]] 
Output: true
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: 2, [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.
Note:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.

solution:

first create and adjaceny matrix

we are going to do a dfs 

for memoization we need a visited array so we know what vertices we have gone through,
but we also need another array called recursion stack for backtracking.

*/

class Solution {
  public:
    //check if there is a cycle
    bool Dfs(unordered_map < int, vector < int >> & adj, vector < bool > & visited, vector < bool > & recStack, int current) {
      //mark current vertex as visited and add current to recStack
      if (!visited[current]) {
        visited[current] = true;
        recStack[current] = true;
        //iterate over vertex's adjacent members
        for (int i = 0; i < adj[current].size(); i++) {
          //if the neighbor adj[current][i] is not visited, and there is no cycles in the subtree then return false for no cucles
          if (!visited[adj[current][i]] && Dfs(adj, visited, recStack, adj[current][i])) {
            return true;
          } else if (recStack[adj[current][i]]) {
            //if recStack[adj[current][i]] is true then that means we looped back and made a cycle so return true
            return true;
          }
        }
      }
      recStack[current] = false;
      return false;
    }

  bool canFinish(int numCourses, vector < vector < int >> & prerequisites) {
    if (numCourses <= 1 || prerequisites.size() == 0) {
      return true;
    }
    //initiate adjaceny matrix
    unordered_map < int, vector < int >> adj;
    for (int i = 0; i < prerequisites.size(); i++) {
      adj[prerequisites[i][0]].push_back(prerequisites[i][1]);
    }
    //initiate visited array and recStack
    vector < bool > visited(numCourses, false);
    vector < bool > recStack(numCourses, false);

    for (int i = 0; i < numCourses; i++) {
        if (Dfs(adj, visited, recStack, i)) {
            return false;
        }
    }
    return true;
  }

};
