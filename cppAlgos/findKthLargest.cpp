class MinHeap {
    
    public:
    int* harr;
    int cap;
    int heapSize;
    
  
    MinHeap(int cap);
    ~MinHeap();
    int parent(int i) {return (i-1)/2;}
    int left(int i) {return (2*i)+1;}
    int right(int i) {return (2*i)+2;}
    int insertKey(int k);
    void minHeapify(int i);
    void recMinHeapify(int i);
};

void swap(int* a, int* b);
 

class Solution {
public:
    
    int findKthLargest(vector<int>& nums, int k) {
        MinHeap* mh = new MinHeap(k);
        int i = 0;
        for (std::vector<int>::iterator it = nums.begin() ; it != nums.end(); ++it) {
            if (i >= 0 && i <= k-1) {
                  mh->insertKey(*it);
            } else if (i >= k) {
                if(*it > mh->harr[0]) {
                    mh->harr[0] = *it;
                    mh->minHeapify(0);
                }
            }
            i++;
        }
        return mh->harr[0];
    
    }
};

MinHeap::MinHeap(int cap) : cap(cap), heapSize(0) {
    harr = new int[cap]();
}
MinHeap::~MinHeap() {
    delete []harr;
}

int MinHeap::insertKey(int k) {
    if (heapSize == cap) {
        return -1;
    }
    
    int pos = heapSize;
    harr[heapSize] = k;
    heapSize++;
    
    for (;pos != 0 && harr[pos] < harr[parent(pos)]; pos = parent(pos)) {
        swap(&harr[pos],&harr[parent(pos)]);
    }
    return k;
}

void MinHeap::recMinHeapify(int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < heapSize && harr[l] < harr[i]) 
        smallest = l; 
    if (r < heapSize && harr[r] < harr[smallest]) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&harr[i], &harr[smallest]); 
        recMinHeapify(smallest); 
    } 
} 


void MinHeap::minHeapify(int i) {
    int smallest;
    bool flag = 1;
    for (int a = i; flag;a = smallest) {
        int l = left(a);
        int r = right(a);
        smallest = a;
        
         if (l < heapSize && harr[a] > harr[l]) {
             smallest = l;
         }
    
         if (r < heapSize && harr[smallest] > harr[r]) {
            smallest = r;
         }

        if (smallest != a) {
            swap(&harr[smallest],&harr[a]);
        } else {
            flag = 0;
        }
       
    }
   
}

void swap (int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

