/*
https://www.hackerrank.com/challenges/swap-nodes-algo/problem

solution: 
the hardest part is interpreting the problem
*/
#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the swapNodes function below.
 */

void swap(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}
//preorder traversal(i dont think traversal order matter) to get depth at each node (current)
void get_depth(unordered_map<int,int>& depthArr, const vector<vector<int>>& indexes, int currentVal, int depth) {
    depthArr[currentVal] = depth;
    if (indexes[currentVal][0] > 0) {
        get_depth(depthArr, indexes, indexes[currentVal][0], depth+1);
    } 
    if (indexes[currentVal][1] > 0) {
        get_depth(depthArr, indexes, indexes[currentVal][1], depth+1);
    } 
}

//currentValue is the index of the indexes vector, indexes[currentVal][0] is the left child node, indexes[currentVal][1] is the right child
void in_order(const vector<vector<int>>& indexes, vector<int>& traversal, int currentVal)
{
    //cout << "curr: " <<  currentVal << " left: " << indexes[currentVal][0] << " right " << indexes[currentVal][1] << endl;
    if (indexes[currentVal][0] > 0) {
        in_order(indexes, traversal, indexes[currentVal][0]);
    } 
    traversal.push_back(currentVal);
    if (indexes[currentVal][1] > 0) {
        in_order(indexes, traversal, indexes[currentVal][1]);
    }
}

vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {
    /*
     * Write your code here.
     */
     //it turns out that for each indexes[i][j] : i is the current value, indexes[i][0] is the left child of i and indexes[i][1] is the right child
     //we must insert a vector in the beginning to denote the root

    indexes.insert(indexes.begin(), vector<int>(2));
    indexes[0][0] = 1;
    indexes[0][1] = 1;
    //must use a map to map the value of the depth to the node(currentVal)    // (key, val) := (currentVal, depth)
    unordered_map<int,int> depthMap;
    vector<vector<int>> results;
    get_depth(depthMap, indexes, 0, 0);
    for (int i = 0; i < queries.size(); i++) {
        vector<int> traversal;
        for (int j = 1; j < indexes.size(); j++) {
            if (depthMap[j] % queries[i] == 0) {
                swap(&indexes[j][0], &indexes[j][1]);
            }
        }
        in_order(indexes, traversal, 1);
        results.push_back(traversal);
    }
    
    return results;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> indexes(n);
    for (int indexes_row_itr = 0; indexes_row_itr < n; indexes_row_itr++) {
        indexes[indexes_row_itr].resize(2);

        for (int indexes_column_itr = 0; indexes_column_itr < 2; indexes_column_itr++) {
            cin >> indexes[indexes_row_itr][indexes_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int queries_count;
    cin >> queries_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(queries_count);

    for (int queries_itr = 0; queries_itr < queries_count; queries_itr++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[queries_itr] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (int result_row_itr = 0; result_row_itr < result.size(); result_row_itr++) {
        for (int result_column_itr = 0; result_column_itr < result[result_row_itr].size(); result_column_itr++) {
            fout << result[result_row_itr][result_column_itr];

            if (result_column_itr != result[result_row_itr].size() - 1) {
                fout << " ";
            }
        }

        if (result_row_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
