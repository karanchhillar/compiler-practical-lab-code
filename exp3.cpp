#include <bits/stdc++.h>
using namespace std;

// Function to check if a character is an operator
bool isOperator(char ch) {
    const char operators[] = "+-*/%=<>&|!"; // Add more operators as needed
    return (strchr(operators, ch) != nullptr);
}

int main() {
    string inputString;

    // Get input from the user
    cout << "Enter a string: ";
    getline(cin, inputString);

    // Process the string and identify alphanumeric characters and operators
    cout << "Identified tokens:" << endl;
    for (char ch : inputString) {
        if (isalnum(ch)) {
            cout << "Alphanumeric: " << ch << endl;
        } else if (isOperator(ch)) {
            cout << "Operator: " << ch << endl;
        }
        // Ignore other characters (e.g., spaces, punctuation)
    }

    return 0;
}
