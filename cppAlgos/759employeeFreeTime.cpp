/*
759. Employee Free Time
Hard

We are given a list schedule of employees, which represents the working time for each employee.

Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.

Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.

(Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined).  Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.

 

Example 1:

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation: There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:

Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]
 

Constraints:

1 <= schedule.length , schedule[i].length <= 50
0 <= schedule[i].start < schedule[i].end <= 10^8
*/
/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};

solution:
time complexity
CLogC
where C is the number of intervals across all employees
use minheap to merge intervals
get the gaps in the mergedIntervals

*/
class Solution {
public:
    
    
    struct IntervalsComparator {
        bool operator()(Interval& i1, Interval& i2) {
            return i1.start > i2.start;
        }
    };
    int Min(int a, int b) {
        return a > b ? b : a;
    }
    int Max(int a, int b) {
        return a < b ? b : a;
    }
    bool IsOverlap(Interval& i1, Interval& i2) {
        return i2.start < i1.end;
    }
    Interval MergeInterval(Interval& i1, Interval& i2) {
        return Interval(Min(i1.start,i2.start), Max(i1.end, i2.end));
    }

    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        vector<Interval> results;
        vector<Interval> mergedIntervals;
        priority_queue<Interval, vector<Interval>, IntervalsComparator> mh;
        
        for (int i = 0; i < schedule.size(); i++) {
            for (int j = 0; j < schedule[i].size(); j++) {
                mh.push(schedule[i][j]);
            }
        }
        
        
        while (!mh.empty()) {
            Interval first = mh.top();
            mh.pop();
            if (mh.empty()) {
                mergedIntervals.push_back(first);
                break;
            }
            Interval second = mh.top();
            mh.pop();
            if (IsOverlap(first, second)) {
                mh.push(MergeInterval(first, second));
            } else {
                mergedIntervals.push_back(first);
                mh.push(second);
            }
        }
        
        //for (int i = 0; i < mergedIntervals.size(); i++) {
        //    cout << mergedIntervals[i].start << " " << mergedIntervals[i].end << endl;
        //}
        
        for (int i = 0; i < mergedIntervals.size()-1; i++) {
            if (mergedIntervals[i+1].start - mergedIntervals[i].end > 0) {
                results.push_back(Interval(mergedIntervals[i].end, mergedIntervals[i+1].start));
            }
        }
        return results;
        
    }
};
