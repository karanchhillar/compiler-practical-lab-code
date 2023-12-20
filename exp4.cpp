#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int getPrecedence(char op) {
    if (op == '^') return 3;
    else if (op == '*' || op == '/') return 2;
    else if (op == '+' || op == '-') return 1;
    else return 0; // for ')'
}

string infixToPrefix(const string& infix) {
    stack<char> operators;
    string prefix;

    for (char ch : infix) {
        if (isalnum(ch)) {
            prefix += ch;
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                prefix += operators.top();
                operators.pop();
            }
            if (!operators.empty())
                operators.pop();
        } else if (isOperator(ch)) {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(ch)) {
                prefix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        prefix += operators.top();
        operators.pop();
    }

    reverse(prefix.begin(), prefix.end());

    return prefix;
}

int main() {
    string infixExpression;

    cout << "Enter an infix expression: ";
    getline(cin, infixExpression);

    string prefixExpression = infixToPrefix(infixExpression);
    cout << "Prefix expression: " << prefixExpression << endl;

    return 0;
}
