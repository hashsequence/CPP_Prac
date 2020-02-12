/*
https://www.hackerrank.com/challenges/find-the-running-median/problem

implement a median heap :
You need two heaps: one min-heap and one max-heap. Each heap contains about one half of the data. Every element in the min-heap is greater or equal to the median, and every element in the max-heap is less or equal to the median.

When the min-heap contains one more element than the max-heap, the median is in the top of the min-heap. And when the max-heap contains one more element than the min-heap, the median is in the top of the max-heap.

When both heaps contain the same number of elements, the total number of elements is even. In this case you have to choose according your definition of median: a) the mean of the two middle elements; b) the greater of the two; c) the lesser; d) choose at random any of the two...

Every time you insert, compare the new element with those at the top of the heaps in order to decide where to insert it. If the new element is greater than the current median, it goes to the min-heap. If it is less than the current median, it goes to the max heap. Then you might need to rebalance. If the sizes of the heaps differ by more than one element, extract the min/max from the heap with more elements and insert it into the other heap.
*/
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

/*
 * Complete the runningMedian function below.
 */
void siftUp(vector<int>&, int);
void swap(int*, int*);
void balance(priority_queue<int,vector<int>,less<int>>&, priority_queue<int,vector<int>,greater<int>>&);

vector<double> runningMedian(vector<int> a) {
    /*
     * Write your code here.
     */
     
     priority_queue<int,vector<int>,less<int>> maxHeap;
     priority_queue<int,vector<int>,greater<int>> minHeap;
     vector<double> results;
     if (a.size() == 0) {
         return results;
     }
     double median = a[0];
     for (int i = 0; i < a.size(); i++) {
        //cout << "median: " << median << endl;
        if (a[i] >= median) {
            minHeap.push(a[i]);
        } else {
            maxHeap.push(a[i]);
        }     
        balance(maxHeap, minHeap);
        if (minHeap.size() == maxHeap.size()) {
            median = (minHeap.top() + maxHeap.top())/2.0;
           // cout<< "equal -- minHeap.top(): " << minHeap.top() << " maxHeap.top(): " << maxHeap.top() << " median: " << median << endl;
            results.push_back(median);
        } else {
            median = maxHeap.size() > minHeap.size() ? maxHeap.top() : minHeap.top();
              //cout<< "unequal -- minHeap.top(): " << minHeap.top() << " maxHeap.top(): " << maxHeap.top() << " median: " << median << endl;
            results.push_back(median);
        }
     }
     return results;
     

}

void balance(priority_queue<int,vector<int>,less<int>>& maxHeap, priority_queue<int,vector<int>,greater<int>>& minHeap) {
    //cout<< "before balance: minHeap.size(): " << minHeap.size() << " maxHeap.size(): " << maxHeap.size() << endl;
    if (maxHeap.size() > 0 && ((int(maxHeap.size()) - int(minHeap.size())) > 1)) {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
    } else if (minHeap.size() > 0 && (int((minHeap.size()) - int(maxHeap.size())) > 1)) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
    }
    //cout<< "balanced: minHeap.size(): " << minHeap.size() << " maxHeap.size(): " << maxHeap.size() << endl;
}

void siftUp(vector<int>& a, int index) {
    for (int i = index; i >= 0; i--) {
        if (a[index] < a[i]) {
            swap(a[index],a[i]);
            index = i;
        }
    }
}

void swap(int* a, int* b) {
    int* t = a;
    b = t;
    a = b;
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[a_itr] = a_item;
    }

    vector<double> result = runningMedian(a);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
