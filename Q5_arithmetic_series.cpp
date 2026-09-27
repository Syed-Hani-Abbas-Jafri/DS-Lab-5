#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

bool isOperatorChar(char c) {
    return c == '+';
}

vector<string> infixToPostfix(vector<string> tokens) {
    stack<string> st;
    vector<string> output;

    for (string tok : tokens) {
        if (tok.size() == 1 && isOperatorChar(tok[0])) {
            while (!st.empty() && st.top().size() == 1 && isOperatorChar(st.top()[0])) {
                output.push_back(st.top());
                st.pop();
            }
            st.push(tok);
        } else {
            output.push_back(tok);
        }
    }
    while (!st.empty()) {
        output.push_back(st.top());
        st.pop();
    }
    return output;
}

string postfixToPrefix(vector<string> postfix) {
    stack<string> st;
    for (string tok : postfix) {
        if (tok.size() == 1 && isOperatorChar(tok[0])) {
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();
            st.push(tok + " " + a + " " + b);
        } else {
            st.push(tok);
        }
    }
    return st.top();
}

string joinTokens(vector<string> v) {
    string result;
    for (size_t i = 0; i < v.size(); i++) {
        result += v[i];
        if (i != v.size() - 1) result += " ";
    }
    return result;
}

int main() {
    int n;
    cout << "Enter number of terms (n): ";
    cin >> n;

    vector<int> terms(n);
    for (int i = 0; i < n; i++) {
        terms[i] = 3 * (i + 1) - 2;
    }

    vector<string> tokens;
    for (int i = 0; i < n; i++) {
        tokens.push_back(to_string(terms[i]));
        if (i != n - 1) tokens.push_back("+");
    }

    vector<string> postfix = infixToPostfix(tokens);
    string prefix = postfixToPrefix(postfix);

    cout << "\nSeries: ";
    for (int i = 0; i < n; i++) {
        cout << terms[i];
        if (i != n - 1) cout << " + ";
    }
    cout << endl;

    cout << "Postfix: " << joinTokens(postfix) << endl;
    cout << "Prefix: " << prefix << endl;

    return 0;
}
