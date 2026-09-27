#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

bool isFunction(string t) {
    return t == "pm" || t == "sqrt" || t == "sin" || t == "cos" || t == "tan";
}

bool isOperator(string t) {
    return t == "+" || t == "-" || t == "*" || t == "/" || t == "^";
}

int precedence(string op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

vector<string> tokenize(string expr) {
    vector<string> tokens;
    stringstream ss(expr);
    string tok;
    while (ss >> tok) tokens.push_back(tok);
    return tokens;
}

vector<string> infixToPostfix(vector<string> tokens) {
    stack<string> st;
    vector<string> output;

    for (string t : tokens) {
        if (isFunction(t)) {
            st.push(t);
        } else if (t == "(") {
            st.push(t);
        } else if (t == ")") {
            while (!st.empty() && st.top() != "(") {
                output.push_back(st.top());
                st.pop();
            }
            st.pop();
            if (!st.empty() && isFunction(st.top())) {
                output.push_back(st.top());
                st.pop();
            }
        } else if (isOperator(t)) {
            while (!st.empty() && isOperator(st.top()) &&
                   ((t != "^" && precedence(st.top()) >= precedence(t)) ||
                    (t == "^" && precedence(st.top()) > precedence(t)))) {
                output.push_back(st.top());
                st.pop();
            }
            st.push(t);
        } else {
            output.push_back(t);
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
    for (string t : postfix) {
        if (isFunction(t)) {
            string a = st.top(); st.pop();
            st.push(t + " " + a);
        } else if (isOperator(t)) {
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();
            st.push(t + " " + a + " " + b);
        } else {
            st.push(t);
        }
    }
    return st.top();
}

string join(vector<string> v) {
    string result;
    for (size_t i = 0; i < v.size(); i++) {
        result += v[i];
        if (i != v.size() - 1) result += " ";
    }
    return result;
}

void convert(string label, string infix) {
    vector<string> tokens = tokenize(infix);
    vector<string> postfix = infixToPostfix(tokens);
    string prefix = postfixToPrefix(postfix);

    cout << "==== " << label << " ====\n";
    cout << "Infix   : " << infix << "\n";
    cout << "Postfix : " << join(postfix) << "\n";
    cout << "Prefix  : " << prefix << "\n\n";
}

int main() {
    convert("1. tan(theta/2) RHS: +- sqrt((1-cos(theta))/(1+cos(theta)))",
             "pm ( sqrt ( ( 1 - cos ( theta ) ) / ( 1 + cos ( theta ) ) ) )");

    convert("2. sin^2(theta) RHS: 1 - cos^2(theta)",
             "1 - cos ( theta ) ^ 2");

    convert("3. sin(alpha)sin(beta) RHS: (1/2)[cos(alpha-beta) - cos(alpha+beta)]",
             "( 1 / 2 ) * ( cos ( alpha - beta ) - cos ( alpha + beta ) )");

    return 0;
}
