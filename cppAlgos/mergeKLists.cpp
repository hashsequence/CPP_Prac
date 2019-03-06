/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct Node {
    int Val;
    int Source;
};

class MinHeap {
    public:
    Node* harr;
    int cap;
    int heapSize;
    
    MinHeap(int c);
    ~MinHeap();
    int parent(int i) {return (i-1)/2;}
    int left(int i) {return (2*i)+1;}
    int right(int i) {return (2*i)+2;}
    Node insertKey(Node k);
    void minHeapify(int i);
    Node extractMin();
        
};

void swap(Node* a, Node* b);

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* list = nullptr;
        MinHeap h(lists.size());
        
        int i = 0;
        for (std::vector<ListNode*>::iterator it = lists.begin(); it != lists.end(); it++) {
            if ((*it) != nullptr) {
                h.insertKey({(*it)->val,i});
                (*it) = (*it)->next;
            }
            i++;
        }
    
       
        ListNode* listPtr;
        while (h.heapSize > 0) {
            Node currMin = h.extractMin();
           // cout << h.heapSize << " " << endl;
            if (currMin.Source != -1) {
                if (list == nullptr) {
                  list = new ListNode(currMin.Val);
                  listPtr = list;
                 } else {
                    listPtr->next = new ListNode(currMin.Val);
                    listPtr = listPtr->next;
                 }
            
                if (lists[currMin.Source] != nullptr) {
                 h.insertKey({lists[currMin.Source]->val, currMin.Source});
                 lists[currMin.Source] = lists[currMin.Source]->next;
                }
            }
            
        }
        
        return list;
    }
    
};

MinHeap::MinHeap(int c) : cap(c),heapSize(0) {
    harr = new Node[c];
}

MinHeap::~MinHeap() {
    delete []harr;
}

Node MinHeap::insertKey(Node k) {
    if(heapSize == cap) {
        return {INT_MAX, -1};
    }
    
    harr[heapSize] = k;
    int pos = heapSize;
    heapSize++;
    
    for(;pos != 0 && harr[pos].Val < harr[parent(pos)].Val; pos = parent(pos)) {
        swap(harr[pos], harr[parent(pos)]);
    }
    return k;
}

void MinHeap::minHeapify(int i) {
    int l = left(i); 
	int r = right(i); 
	int smallest = i; 
	if (l < heapSize && harr[l].Val < harr[smallest].Val)  {
        smallest = l; 
    }
	if (r < heapSize && harr[r].Val < harr[smallest].Val) {
        smallest = r; 
    }
	if (smallest != i) 
	{ 
		swap(&harr[i], &harr[smallest]); 
		minHeapify(smallest); 
	} 
}

Node MinHeap::extractMin() {
     if (heapSize == 0) {
         return {INT_MAX, -1};
     }   
    
    if (heapSize == 1) {
          heapSize--;
        return harr[0];
      
    }
    
    Node min = harr[0];
    harr[0] = harr[heapSize-1];
    heapSize--;
    minHeapify(0); 
    
    return min;
    
}

void swap(Node* x, Node* y) 
{ 
	Node temp = *x; 
	*x = *y; 
	*y = temp; 
} 
