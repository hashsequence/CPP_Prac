/*
146. LRU Cache
Medium

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2  ); // 2 is capacity

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

solution:

I can use an unorderd_map to have O(1) access to the element for retrieval
and also O(1) insert 

however how do I keep track of which items are used the most,
I can implement a doubly linked list 
and put the least recently used is the head

*/




class LRUCache {
public:
    struct Node {
        int key;
        int value;
        Node* next;
        Node* prev;
        
        Node(int key, int value) : key(key), value(value) {
            next = nullptr;
            prev = nullptr;
        }
        
        
    };
    class LinkedList {
      public:
        Node* head;
        Node* tail;
        int size;
        int capacity;
        
        LinkedList() {}
        LinkedList(int capacity ) : capacity(capacity) {
            size = 0;
            head = nullptr;
            tail = nullptr;
        }
        
        Node* popFront() {
           if (size == 0) {
               return nullptr;
           }
            if (size == 1) {
                Node* delNode = head;
                head = nullptr;
                tail = nullptr; 
                size--;
                return delNode;
            }
            if (size > 1) {
                Node* delNode = head;
                head = head->next;
                head->prev = nullptr;
                size--;
                return delNode;
            }
            return nullptr;
        }
        Node* popEnd() {
            if (size == 0) {
               return nullptr;
           }
            if (size == 1) {
                Node* delNode = head;
                head = nullptr;
                tail = nullptr; 
                size--;
                return delNode;
            }
            if (size > 1) {
                Node* delNode = tail;
                tail = tail->prev;
                tail->next = nullptr;
                size--;
                return delNode;
            }
            return nullptr;
        }
        
        void insert(Node* node) {
           if (size == 0) {
               head = node;
               head->prev = nullptr;
               head->next = nullptr;
               tail = head;
               size++;
               return;
           }
            if (size > 0) {
                tail->next = node;
                node->prev = tail;
                tail = node;
                tail->next = nullptr;
                size++;
                return;
            }
        }
        
        Node* remove(Node* node) {
            if (node == nullptr || size == 0) {
                return node;
            }
            if (size >= 1) {
                 if (node == head) {
                    return popFront();
                }
                if (node == tail) {
                    return popEnd();
                } 
                node->prev->next = node->next;
                node->next->prev = node->prev;
                size--;
                return node;
            }
            return nullptr;
        }
        ~LinkedList() {
            while (size > 0) {
                popFront();
            }
        }
        
    };
    
    unordered_map<int,Node*> mp; 
    LinkedList ls;
    int cap;
    int size;
    
    LRUCache(int capacity) {
        cap = capacity;
        size = 0;
        ls = LinkedList(capacity);
    }
    
    int get(int key) {
        if (mp.find(key) != mp.end()){
            if (size == 1) {
                return mp[key]->value;
            } else if (size > 1) {
                ls.remove(mp[key]);
                ls.insert(mp[key]);
            }
            return mp[key]->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (mp.find(key) == mp.end()) {
            Node* nNode = new Node(key, value);
            if (size == cap) {
                Node* delNode = ls.popFront();
                mp.erase(delNode->key);
                delete delNode;
                size--;
            }
            mp[key] = nNode;
            ls.insert(nNode);
            size++;
        } else {
            Node* delNode = mp.find(key)->second;
            ls.remove(delNode);
            mp.erase(key);
            delete delNode;
            Node* nNode = new Node(key, value);
            mp[key] = nNode;
            ls.insert(nNode);    
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
