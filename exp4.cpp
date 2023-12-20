#include <bits/stdc++.h>
using namespace std;

// Function to check if a character is an operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
    if (op == '^') return 3;
    else if (op == '*' || op == '/') return 2;
    else if (op == '+' || op == '-') return 1;
    else return 0; // for '('
}

// Function to convert infix to prefix
string infixToPrefix(const string& infix) {
    stack<char> operators;
    string prefix;

    // Reverse the infix expression
    string reversedInfix = infix;
    reverse(reversedInfix.begin(), reversedInfix.end());

    for (char ch : reversedInfix) {
        if (isalnum(ch)) {
            // Operand: Add to the prefix expression
            prefix += ch;
        } else if (ch == ')') {
            // Right parenthesis: Push onto the stack
            operators.push(ch);
        } else if (ch == '(') {
            // Left parenthesis: Pop and add operators to the prefix until a matching ')' is encountered
            while (!operators.empty() && operators.top() != ')') {
                prefix += operators.top();
                operators.pop();
            }
            operators.pop(); // Pop the matching ')'
        } else if (isOperator(ch)) {
            // Operator: Pop and add operators to the prefix until a lower or equal precedence operator is encountered
            while (!operators.empty() && getPrecedence(operators.top()) > getPrecedence(ch)) {
                prefix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    // Pop any remaining operators from the stack
    while (!operators.empty()) {
        prefix += operators.top();
        operators.pop();
    }

    // Reverse the final prefix expression to get the correct order
    reverse(prefix.begin(), prefix.end());

    return prefix;
}

int main() {
    string infixExpression;

    // Get input from the user
    cout << "Enter an infix expression: ";
    getline(cin, infixExpression);

    // Convert infix to prefix and display the result
    string prefixExpression = infixToPrefix(infixExpression);
    cout << "Prefix expression: " << prefixExpression << endl;

    return 0;
}
