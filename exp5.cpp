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

// Function to convert infix to postfix
string infixToPostfix(const string& infix) {
    stack<char> operators;
    string postfix;

    for (char ch : infix) {
        if (isalnum(ch)) {
            // Operand: Add to the postfix expression
            postfix += ch;
        } else if (ch == '(') {
            // Left parenthesis: Push onto the stack
            operators.push(ch);
        } else if (ch == ')') {
            // Right parenthesis: Pop and add operators to the postfix until a matching '(' is encountered
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Pop the matching '('
        } else if (isOperator(ch)) {
            // Operator: Pop and add operators to the postfix until a lower or equal precedence operator is encountered
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    // Pop any remaining operators from the stack
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

int main() {
    string infixExpression;

    // Get input from the user
    cout << "Enter an infix expression: ";
    getline(cin, infixExpression);

    // Convert infix to postfix and display the result
    string postfixExpression = infixToPostfix(infixExpression);
    cout << "Postfix expression: " << postfixExpression << endl;

    return 0;
}
