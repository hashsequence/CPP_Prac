/*
456. 132 Pattern
Medium

Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a subsequence ai, aj, ak such that i < j < k and ai < ak < aj. Design an algorithm that takes a list of n numbers as input and checks whether there is a 132 pattern in the list.

Note: n will be less than 15,000.

Example 1:
Input: [1, 2, 3, 4]

Output: False

Explanation: There is no 132 pattern in the sequence.
Example 2:
Input: [3, 1, 4, 2]

Output: True

Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
Example 3:
Input: [-1, 3, 2, 0]

Output: True

Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].

solution:
we iterate over nums to find min from [0,i] at i

we use a stack
we iterate over nums again

2ndway:
we iterate over the nums backwards
we basically keep track of the max by maintaining that the top of the stack is the max or our potential 3
we maintain that potential2 is always the second largest from [i+1,n-1]
and when potential2 > nums[i] then we found our 132


*/
class Solution {
public:
    
    bool find132pattern(vector<int>& nums) {
        if (nums.size() < 3) {
            return false;
        } 
        stack<int> potential3;
        int potential2 = nums[0];
        for(int i = 1; i < nums.size(); i++ ) {
            if (potential2 > nums[i]) {
                potential2 = nums[i];
            }
        }
        for(int i = nums.size()-1; i >= 0; i--) {
            //after the loop potential3.top() > nums[i] 
            while (!potential3.empty() && potential3.top() < nums[i]) {
                potential2 = max(potential2, potential3.top());
                cout << potential2 << endl;
                potential3.pop();
            }
            if (potential2 > nums[i]) {
                cout <<  nums[i]   <<  " " << potential3.top() << " " <<  potential2 << endl;
                return true;
            } else {
                //now potential3.top() > potential2
                //this maintains that potential3.top is always greater than potential2 at i
                cout << "push" <<endl;
                potential3.push(nums[i]);
                
            }
        }
        return false;
    }
    bool find132patternFirstWay(vector<int>& nums) {
        if (nums.size() < 3) {
            return false;
        } 
        //get the min for each i which is the min in (0,i)
        vector<int> min_from0To;
        int min = nums[0];
        min_from0To.push_back(min);
        for(int i = 1; i < nums.size(); i++) {   
            if (nums[i] < min) {
                min_from0To.push_back(nums[i]);
                min = nums[i];
            } else {
                min_from0To.push_back(min);
            }
        }
        //iterate backward to find 3 2
        //we an use a stack as we go backwards
        stack<int> s;
        for (int i = nums.size()-1; i >= 1; i--) {
            if (nums[i] > min_from0To[i-1]) {
                if (s.size() > 0 && nums[i] > s.top()) {
                    while (!s.empty()) {
                        if (s.top() > min_from0To[i-1]) {
                            return true;
                        } else {
                            s.pop();
                        }
                    }
                } 
                s.push(nums[i]);
            }
        }
        return false;
        
    }
};
