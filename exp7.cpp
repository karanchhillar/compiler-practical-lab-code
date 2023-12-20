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
    string rightHandSide;
};

// Function to perform left factoring for a given grammar
void leftFactorGrammar(vector<ProductionRule>& grammar) {
    map<char, vector<string>> nonTerminalRules;

    // Group production rules by non-terminal
    for (const ProductionRule& rule : grammar) {
        nonTerminalRules[rule.nonTerminal].push_back(rule.rightHandSide);
    }

    // Process each non-terminal
    for (auto& entry : nonTerminalRules) {
        char nonTerminal = entry.first;
        const vector<string>& rules = entry.second;

        // Find the common prefix among rules
        string commonPrefix = "";
        for (size_t i = 0; i < rules[0].size(); ++i) {
            char currentChar = rules[0][i];

            bool isCommon = true;
            for (const string& rule : rules) {
                if (rule[i] != currentChar) {
                    isCommon = false;
                    break;
                }
            }

            if (isCommon) {
                commonPrefix += currentChar;
            } else {
                break;
            }
        }

        // If there is a common prefix, perform left factoring
        if (!commonPrefix.empty()) {
            string newNonTerminal = "X"; // Create a new non-terminal
            char newNonTerminalChar = newNonTerminal[0];
            vector<string> newRules;

            // Add new rules for the original non-terminal
            for (const string& rule : rules) {
                if (rule.size() > commonPrefix.size()) {
                    newRules.push_back(rule.substr(commonPrefix.size()) + newNonTerminalChar);
                } else {
                    newRules.push_back(string(1, newNonTerminalChar));
                }
            }

            // Add new rules for the new non-terminal
            for (const string& rule : rules) {
                if (rule.size() > commonPrefix.size()) {
                    newRules.push_back(rule.substr(commonPrefix.size()));
                }
            }

            // Update the grammar
            grammar.erase(remove_if(grammar.begin(), grammar.end(),
                [nonTerminal](const ProductionRule& rule) {
                    return rule.nonTerminal == nonTerminal;
                }), grammar.end());

            grammar.push_back({nonTerminal, commonPrefix + newNonTerminal});
            grammar.push_back({newNonTerminalChar, newRules[0]});
            for (size_t i = 1; i < newRules.size(); ++i) {
                grammar.push_back({newNonTerminalChar, newRules[i]});
            }
        }
    }
}

// Function to display the grammar
void displayGrammar(const vector<ProductionRule>& grammar) {
    cout << "Grammar:" << endl;
    for (const ProductionRule& rule : grammar) {
        cout << rule.nonTerminal << " -> " << rule.rightHandSide << endl;
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

    // Display the original grammar
    cout << "\nOriginal Grammar:" << endl;
    displayGrammar(grammar);

    // Perform left factoring
    leftFactorGrammar(grammar);

    // Display the grammar after left factoring
    cout << "\nGrammar after Left Factoring:" << endl;
    displayGrammar(grammar);

    return 0;
}


// {'S', "abc"},
// {'S', "abd"},
// {'S', "abef"},
// {'A', "gh"},
// {'A', "g"},