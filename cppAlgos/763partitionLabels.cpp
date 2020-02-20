/*
763. Partition Labels
Medium


A string S of lowercase letters is given. We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
Note:

S will have length in range [1, 500].
S will consist of lowercase letters ('a' to 'z') only.

solution:
iterate over vector and get intervals for each character
we can use an unordered_map of pairs to represent the interval

merge intervals using the minHeap

*/
class Solution {
public:
    struct CompareIntervals {
        bool operator()(pair<int,int>& o1, pair<int,int>& o2) {
            return o1.first > o2.first;
        }
    };
    
    bool intervalsOverlap(pair<int,int>& o1, pair<int,int>& o2) {
        return (o2.first < o1.second); 
    }
    
    pair<int,int> mergeIntervals(pair<int,int>& o1, pair<int,int>& o2) {
        return make_pair(o1.first, (o1.second < o2.second ? o2.second : o1.second));
    }
    vector<int> partitionLabels(string S) {
        vector<int> res;
        unordered_map<char,pair<int,int>> intervals;
        priority_queue<pair<int,int>, vector<pair<int,int>>, CompareIntervals> minHeap;
        //get intervals
        for (int i = 0; i < S.length(); i++) {
            if (intervals.find(S[i]) == intervals.end()) {
                intervals[S[i]] = make_pair(i, i);
            } else {
                intervals[S[i]].second = i;
            }
        }
    
        for(unordered_map<char,pair<int,int>>::iterator it = intervals.begin(); it != intervals.end(); it++) {
            //cout << it->first << " [" << it->second.first << "," << it->second.second << "]" << endl;
            minHeap.push(it->second);
        }
        
        //merge intervals
        while (!minHeap.empty()) {
            pair<int,int> curr = minHeap.top();
            //cout << curr.first << " " << curr.second << endl;
            minHeap.pop();
            if (minHeap.empty() == true) {
                res.push_back(curr.second-curr.first+1);
            } else {
                pair<int,int> next = minHeap.top();
                if (intervalsOverlap(curr, next)) {
                    minHeap.pop();
                    minHeap.push(mergeIntervals(curr,next));
                } else {
                    res.push_back(curr.second-curr.first+1);
                }
            }
        }
        return res;
    }
};
