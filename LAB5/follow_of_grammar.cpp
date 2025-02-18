#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int numProductions;
vector<string> productions;

void follow(string &result, char c);
void first(string &result, char c);
void addToResultSet(string &result, char val);

int main() {
    size_t i;
    char c;
    string result;

    cout << "Enter the number of productions: ";
    cin >> numProductions;

    productions.resize(numProductions);
    cout << "Enter the productions:\n";
    for (i = 0; i < numProductions; i++) {
        cin >> productions[i];
    }

    cout << "Find FOLLOW of: ";
    cin >> c;

    follow(result, c);
    cout << "FOLLOW(" << c << ") = { ";
    for (i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << "}\n";

    return 0;
}

void follow(string &result, char c) {
    int i, k;
    size_t j;
    string subResult;
    result.clear();

    // If c is the start symbol, add '$' to FOLLOW(c)
    if (productions[0][0] == c) {
        addToResultSet(result, '$');
    }

    // Scan all productions
    for (i = 0; i < numProductions; i++) {
        size_t len = productions[i].length();
        for (j = 2; j < len; j++) { // Start from the 2nd character (after the arrow)
            if (productions[i][j] == c) { // Found c in RHS
                subResult.clear(); // Reset subResult before using it

                if (productions[i][j + 1] != '\0') { // If next symbol exists
                    first(subResult, productions[i][j + 1]);

                    // Add FIRST of next symbol (excluding ε)
                    for (k = 0; k < subResult.size(); k++) {
                        if (subResult[k] != '#') { 
                            addToResultSet(result, subResult[k]);
                        }
                    }

                    // If ε is in FIRST(next), also add FOLLOW(LHS)
                    for (k = 0; k < subResult.size(); k++) {
                        if (subResult[k] == '#') { 
                            follow(result, productions[i][0]);
                        }
                    }
                } else { // If c is at end of production, add FOLLOW(LHS)
                    if (productions[i][0] != c) {
                        follow(result, productions[i][0]);
                    }
                }
            }
        }
    }
}

void first(string &result, char c) {
    int i;
    result.clear(); // Reset result at the beginning

    if (!isupper(c)) { // If c is a terminal
        addToResultSet(result, c);
        return;
    }

    // If c is a non-terminal, scan its productions
    for (i = 0; i < numProductions; i++) {
        if (productions[i][0] == c) {
            if (productions[i][2] == '#') { // ε production
                addToResultSet(result, '#');
            } else if (!isupper(productions[i][2])) { // Terminal
                addToResultSet(result, productions[i][2]);
            } else { // Non-terminal, recurse
                first(result, productions[i][2]);
            }
        }
    }
}

void addToResultSet(string &result, char val) {
    if (result.find(val) == string::npos) { // Avoid duplicates
        result.push_back(val); // Add new value to result
    }
}

