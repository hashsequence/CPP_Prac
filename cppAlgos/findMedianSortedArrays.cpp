class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int k = (nums1.size() + nums2.size())/2;
        
        if ((nums1.size() + nums2.size()) % 2 > 0) {
          return findKthElement(nums1,0,nums2,0,k+1);
        } else if ((nums1.size() + nums2.size()) % 2 == 0) {
         //   cout << "i see even " << findKthElement(nums1,0,nums2,0,k) << " " << findKthElement(nums1,0,nums2,0,k+1) << endl;
          return (findKthElement(nums1,0,nums2,0,k) + findKthElement(nums1,0,nums2,0,k+1))/2;
        } 
        return -1;
    }
    
    double findKthElement(vector<int>& nums1, int start1, vector<int>& nums2, int start2, int k) {  
        int n = nums1.size()-start1, m = nums2.size()-start2;
        if (k <=0 || k > (m + n)) {
            return -1;
        }
        

        if (n > m) {
            // cout << n << " " << m << " " << k << " "  <<  endl;
             // cout << "i see this n > m" << endl;
            return findKthElement(nums2, start2, nums1, start1, k);
        }
              
        if (n == 0) {
             //cout << n << " " << m << " " << k << " "  <<  nums2[k-1] << endl;
            //cout << "i see this n == 0" << endl;
            return nums2[start2 + k-1];
        }
          
        if (k == 1) {
          //  cout << n << " " << m << " " << k << " " << endl;
            //cout << "i see this k == 1" << endl;
            return min(nums1[start1],nums2[start2]);
        }
        
        int i = min(n, k/2), j = min(m,k/2);
        
        if (nums1[start1 + i-1] > nums2[start2 + j-1]) {
           return findKthElement(nums1, start1, nums2 ,start2 + j, k-j);
        } else {
           return findKthElement(nums1, start1 + i, nums2, start2, k-i);
        }
        return -1;
        
    }
    
    int min(int a, int b) {
        
        return a < b ? a : b;
    }
    
};
