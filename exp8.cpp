#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

// Define a structure to represent a production rule
struct ProductionRule {
    char nonTerminal;
    vector<string> rightHandSide;
};

// Function to remove left recursion for a given grammar
void removeLeftRecursion(vector<ProductionRule>& grammar) {
    vector<ProductionRule> newGrammar;

    for (const ProductionRule& rule : grammar) {
        char nonTerminal = rule.nonTerminal;
        const vector<string>& rightHandSide = rule.rightHandSide;

        vector<string> nonRecursive;
        vector<string> recursive;

        // Separate rules into recursive and non-recursive
        for (const string& rhs : rightHandSide) {
            if (rhs[0] == nonTerminal) {
                recursive.push_back(rhs.substr(1) + nonTerminal + "'");
            } else {
                nonRecursive.push_back(rhs + nonTerminal + "'");
            }
        }

        if (!recursive.empty()) {
            // Add non-recursive rules to the new grammar
            for (const string& rhs : nonRecursive) {
                newGrammar.push_back({nonTerminal, {rhs}});
            }

            // Add new rules to handle left recursion
            string newNonTerminal = nonTerminal + "'";
            newGrammar.push_back({nonTerminal, recursive});
            newGrammar.push_back({newNonTerminal[0], {"#"}}); // # represents an empty string

        } else {
            // No left recursion, add the original rule to the new grammar
            newGrammar.push_back({nonTerminal, rightHandSide});
        }
    }

    grammar = newGrammar;
}

// Function to display the grammar
void displayGrammar(const vector<ProductionRule>& grammar) {
    cout << "Grammar:" << endl;
    for (const ProductionRule& rule : grammar) {
        cout << rule.nonTerminal << " -> ";
        for (size_t i = 0; i < rule.rightHandSide.size(); ++i) {
            cout << rule.rightHandSide[i];
            if (i < rule.rightHandSide.size() - 1) {
                cout << " | ";
            }
        }
        cout << endl;
    }
}

int main() {
    // Define the grammar
    vector<ProductionRule> grammar;

    // Get input from the user for the production rules
    int numRules;
    cout << "Enter the number of production rules: ";
    cin >> numRules;

    cout << "Enter the production rules in the format (non-terminal -> right-hand side1 | right-hand side2 | ...):" << endl;
    for (int i = 0; i < numRules; ++i) {
        ProductionRule rule;
        cin >> rule.nonTerminal;
        string arrow;
        cin >> arrow;
        string rhs;
        getline(cin, rhs); // Read the entire right-hand side
        size_t pos = 0;
        while ((pos = rhs.find('|')) != string::npos) {
            rule.rightHandSide.push_back(rhs.substr(1, pos - 1));
            rhs.erase(0, pos + 1);
        }
        rule.rightHandSide.push_back(rhs.substr(1)); // Add the last right-hand side
        grammar.push_back(rule);
    }

    // Display the original grammar
    cout << "\nOriginal Grammar:" << endl;
    displayGrammar(grammar);

    // Remove left recursion
    removeLeftRecursion(grammar);

    // Display the grammar after removing left recursion
    cout << "\nGrammar after Removing Left Recursion:" << endl;
    displayGrammar(grammar);

    return 0;
}

// 3
// E -> E + T | E - T | T
// T -> T * F | T / F | F
// F -> (E) | id
