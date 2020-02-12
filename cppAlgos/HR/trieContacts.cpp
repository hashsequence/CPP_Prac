/*
https://www.hackerrank.com/challenges/contacts/problem
*/
#include <bits/stdc++.h>
#include <string>
using namespace std;

/*
 * Complete the contacts function below.
 */
class Trie {
    public:
    class TrieNode {
        public:
        TrieNode* child[26];
        int count;
        bool isEnd;

        TrieNode():isEnd(false), count(0) {
            for (int i = 0; i < 26; i++) {
                child[i] = nullptr;
            }
        }
       
    };

    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }
    ~Trie() {
        stack<TrieNode*> s1;
        stack<TrieNode*> s2;
        TrieNode* curr = root;
        s1.push(curr);
        //post order traveral using two stacks to delete tree
        while(!s1.empty()) {
            curr = s1.top();
            s1.pop();
            s2.push(curr);
            for (int i = 25; i >= 0; i--) {
                if(curr->child[i]) {
                    s1.push(curr->child[i]);
                }
            }
        }

        while(!s2.empty()) {
            curr = s2.top();
            s2.pop();
            delete curr;
        }
    }

    void insert(string key);
    int search(string key);

};

void Trie::insert(string key) {
    TrieNode* crawl = root;
    for (int i = 0; i < key.length(); i++) {
        if(crawl->child[key[i]-'a'] == nullptr) {
            crawl->child[key[i] - 'a']  = new TrieNode();
            crawl->child[key[i] - 'a']->count++;
        } else {
            crawl->child[key[i] - 'a']->count++;
        }
        crawl = crawl->child[key[i]-'a'];
    }
    crawl->isEnd = true;
    //crawl->count++;
}

int Trie::search(string key) {
    TrieNode* crawl = root;
    for (int i = 0; i < key.length(); i++) {
        if(!crawl->child[key[i]-'a']){
            //cout << "returning crawl count 0 first \n";
            return 0;
        }
        crawl = crawl->child[key[i]-'a'];
    }
     if (crawl != nullptr) {
        // cout << "returning crawl count 2nd\n";
         return crawl->count;
     }
    // cout << "returning crawl count 0\n";
     return 0;
    /*
    if (crawl == nullptr) {
        return 0;
    }
    //DFS preorder traversal
    stack<TrieNode*> s1;
    TrieNode* curr = crawl;
    s1.push(curr);
    while(!s1.empty()) {
        TrieNode* node = s1.top();
        s1.pop();
        for (int i = 0; i < 26; i++) {
            if(node->child[i]) {
                s1.push(node->child[i]);
            }
        }
        if (node->isEnd) {
            count++;
        }
    }
    */
    
}
 

vector<int> contacts(vector<vector<string>> queries) {
    /*
     * Write your code here.
     */
     Trie wordbank = Trie();
     vector<int> results;
     for (int i = 0; i < queries.size(); i++) {
        //cout << queries[i][j] <<endl;
        if (queries[i][0] == "add") {
            wordbank.insert(queries[i][1]);
        }
        if (queries[i][0] == "find") {
            int num = wordbank.search(queries[i][1]);
            results.push_back(num);
        }

     }
    return results;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int queries_rows;
    cin >> queries_rows;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<string>> queries(queries_rows);
    for (int queries_row_itr = 0; queries_row_itr < queries_rows; queries_row_itr++) {
        queries[queries_row_itr].resize(2);

        for (int queries_column_itr = 0; queries_column_itr < 2; queries_column_itr++) {
            cin >> queries[queries_row_itr][queries_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = contacts(queries);

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
