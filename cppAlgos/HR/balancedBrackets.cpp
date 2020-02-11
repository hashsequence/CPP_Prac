/*
https://www.hackerrank.com/challenges/balanced-brackets/problem
*/
#include <bits/stdc++.h>

using namespace std;

// Complete the isBalanced function below.
string isBalanced(string s) {
    stack<char> brackets;

    for (int i = 0; i < s.length(); i++) {
        //cout << s[i] << endl;
        switch(s[i]) {
            case '(' :
            case '[' :
            case '{' :
                brackets.push(s[i]);
                break;
            case ')':
                if (!brackets.empty() && brackets.top() == '(') {
                    brackets.pop();
                } else {
                    return "NO";
                }
                break;
            case ']':
                if (!brackets.empty() && brackets.top() == '[') {
                    brackets.pop();
                } else {
                    return "NO";
                }
                break;
            case '}':
                if (!brackets.empty() && brackets.top() == '{') {
                    brackets.pop();
                } else {
                    return "NO";
                }
                break;
        }
    }
    if (brackets.size() == 0) {
            return "YES";
        }
        return "NO";

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(cin, s);

        string result = isBalanced(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
