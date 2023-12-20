#include <bits/stdc++.h>
using namespace std;

// Define a structure to represent a production rule
struct ProductionRule {
    char nonTerminal;
    string rightHandSide;
};

// Function to calculate FIRST set for a given grammar
void calculateFirstSet(map<char, set<char>>& firstSet, const vector<ProductionRule>& grammar) {
    bool changes;

    do {
        changes = false;

        for (const ProductionRule& rule : grammar) {
            char nonTerminal = rule.nonTerminal;
            const string& rhs = rule.rightHandSide;

            // If the first symbol of the right-hand side is a terminal, add it to the FIRST set
            if (isalpha(rhs[0]) && islower(rhs[0])) {
                if (firstSet[nonTerminal].insert(rhs[0]).second) {
                    changes = true;
                }
            }
            // If the first symbol of the right-hand side is a non-terminal, add its FIRST set to the FIRST set
            else if (isalpha(rhs[0]) && isupper(rhs[0])) {
                for (char terminal : firstSet[rhs[0]]) {
                    if (firstSet[nonTerminal].insert(terminal).second) {
                        changes = true;
                    }
                }
            }
            // If the right-hand side can derive #, add the FIRST set of the next symbol in the right-hand side
            // (excluding #) to the FIRST set
            else if (rhs[0] == '#') {
                for (char terminal : firstSet[rhs[1]]) {
                    if (firstSet[nonTerminal].insert(terminal).second) {
                        changes = true;
                    }
                }
            }
        }

    } while (changes);
}

// Function to display the calculated FIRST sets
void displayFirstSets(const map<char, set<char>>& firstSet) {
    cout << "FIRST sets:" << endl;
    for (const auto& entry : firstSet) {
        if (isupper(entry.first)) { // Exclude terminals from the output
            cout << "FIRST(" << entry.first << ") = { ";
            for (char terminal : entry.second) {
                cout << terminal << ' ';
            }
            cout << '}' << endl;
        }
    }
}

int main() {
    // Define the grammar
    vector<ProductionRule> grammar;

    // Get input from the user for the production rules
    int numRules;
    cout << "Enter the number of production rules: ";
    cin >> numRules;

    cout << "Enter the production rules in the format (non-terminal -> right-hand side):" << endl;
    for (int i = 0; i < numRules; ++i) {
        ProductionRule rule;
        cin >> rule.nonTerminal;
        cin.ignore(); // Ignore the '->' part
        getline(cin, rule.rightHandSide);
        grammar.push_back(rule);
    }

    // Map to store the FIRST set for each non-terminal
    map<char, set<char>> firstSet;

    // Initialize FIRST set for terminals
    for (const ProductionRule& rule : grammar) {
        if (isalpha(rule.rightHandSide[0]) && islower(rule.rightHandSide[0])) {
            firstSet[rule.rightHandSide[0]].insert(rule.rightHandSide[0]);
        }
    }

    // Calculate FIRST set for non-terminals
    calculateFirstSet(firstSet, grammar);

    // Display the calculated FIRST sets
    displayFirstSets(firstSet);

    return 0;
}


// {'S', "AB"},
// {'A', "aA"},
// {'A', "#"},
// {'B', "bB"},
// {'B', "#"}