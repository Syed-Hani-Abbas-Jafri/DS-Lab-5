#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
#include <cctype>
using namespace std;

bool isOperatorChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

vector<string> tokenize(string expr) {
    vector<string> tokens;
    int i = 0;
    while (i < (int)expr.size()) {
        if (expr[i] == ' ') { i++; continue; }
        if (isdigit(expr[i]) || expr[i] == '.') {
            string num;
            while (i < (int)expr.size() && (isdigit(expr[i]) || expr[i] == '.')) num += expr[i++];
            tokens.push_back(num);
        } else if (expr[i] == 'x') {
            tokens.push_back("x");
            i++;
        } else {
            tokens.push_back(string(1, expr[i]));
            i++;
        }
    }
    return tokens;
}

vector<string> infixToPostfix(vector<string> tokens) {
    stack<string> st;
    vector<string> output;

    for (string tok : tokens) {
        if (tok == "(") {
            st.push(tok);
        } else if (tok == ")") {
            while (!st.empty() && st.top() != "(") {
                output.push_back(st.top());
                st.pop();
            }
            st.pop();
        } else if (tok.size() == 1 && isOperatorChar(tok[0])) {
            while (!st.empty() && st.top().size() == 1 && isOperatorChar(st.top()[0]) &&
                   ((tok[0] != '^' && precedence(st.top()[0]) >= precedence(tok[0])) ||
                    (tok[0] == '^' && precedence(st.top()[0]) > precedence(tok[0])))) {
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

double evaluatePostfix(vector<string> postfix, double xVal) {
    stack<double> st;
    for (string tok : postfix) {
        if (tok.size() == 1 && isOperatorChar(tok[0])) {
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            double res = 0;
            switch (tok[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                case '^': res = pow(a, b); break;
            }
            st.push(res);
        } else if (tok == "x") {
            st.push(xVal);
        } else {
            st.push(stod(tok));
        }
    }
    return st.top();
}

void parseCondition(string cond, string &op, double &rhs) {
    size_t pos = string::npos;

    if ((pos = cond.find(">=")) != string::npos) op = ">=";
    else if ((pos = cond.find("<=")) != string::npos) op = "<=";
    else if ((pos = cond.find("==")) != string::npos) op = "==";
    else if ((pos = cond.find("!=")) != string::npos) op = "!=";
    else if ((pos = cond.find(">")) != string::npos) op = ">";
    else if ((pos = cond.find("<")) != string::npos) op = "<";

    string rhsStr = cond.substr(pos + op.size());
    rhs = stod(rhsStr);
}

bool evaluateCondition(double x, string op, double rhs) {
    if (op == ">=") return x >= rhs;
    if (op == "<=") return x <= rhs;
    if (op == "==") return x == rhs;
    if (op == "!=") return x != rhs;
    if (op == ">") return x > rhs;
    if (op == "<") return x < rhs;
    return false;
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
    cout << "Enter number of piecewise expressions: ";
    cin >> n;
    cin.ignore();

    vector<string> expressions(n), conditions(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter Expression " << i + 1 << ": ";
        getline(cin, expressions[i]);
        cout << "Enter Condition " << i + 1 << ": ";
        getline(cin, conditions[i]);
    }

    double xVal;
    cout << "Enter x: ";
    cin >> xVal;

    int selected = -1;
    for (int i = 0; i < n; i++) {
        string op;
        double rhs;
        parseCondition(conditions[i], op, rhs);
        if (evaluateCondition(xVal, op, rhs)) {
            selected = i;
            break;
        }
    }

    if (selected == -1) {
        cout << "\nNo condition is satisfied for x = " << xVal << endl;
        return 0;
    }

    vector<string> tokens = tokenize(expressions[selected]);
    vector<string> postfix = infixToPostfix(tokens);
    double result = evaluatePostfix(postfix, xVal);

    cout << "\nCondition: " << conditions[selected] << endl;
    cout << "Expression: " << expressions[selected] << endl;
    cout << "Postfix: " << joinTokens(postfix) << endl;
    cout << "f(" << xVal << ") = " << result << endl;

    return 0;
}
