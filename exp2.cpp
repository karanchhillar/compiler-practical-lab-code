#include <bits/stdc++.h>
using namespace std;

int main() {
    string inputString;

    // Get input from the user
    cout << "Enter a string: ";
    getline(cin, inputString);

    // Process the string and identify characters and digits
    cout << "Identified tokens:" << endl;
    for (char ch : inputString) {
        if (isdigit(ch)) {
            cout << "Digit: " << ch << endl;
        } else if (isalpha(ch)) {
            cout << "Character: " << ch << endl;
        }
        // Ignore other characters (e.g., spaces, punctuation)
    }

    return 0;
}
