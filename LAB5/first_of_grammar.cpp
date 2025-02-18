#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

int numOfProductions;
vector<string> productionSet;

void FIRST(string &, char);
void addToResultSet(string &, char);

int main() {
    cout << "How many number of productions?: ";
    cin >> numOfProductions;
    productionSet.resize(numOfProductions);
    
    cout << "Enter productions: " << endl;
    for (int i = 0; i < numOfProductions; i++) {
        cin >> productionSet[i];
    }
    
    char choice;
    do {
        char c;
        string result;
        cout << "\nFind the FIRST of: ";
        cin >> c;
        FIRST(result, c);
        
        cout << "\nFIRST(" << c << ") = { ";
        for (char res : result) {
            cout << res << " ";
        }
        cout << "}\n";
        
        cout << "Press 'y' to continue: ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    
    return 0;
}

void FIRST(string &Result, char c) {
    string subResult;
    bool foundEpsilon;
    
    if (!isupper(c)) {
        addToResultSet(Result, c);
        return;
    }
    
    for (const string &prod : productionSet) {
        if (prod[0] == c) {
            if (prod[2] == '$') {
                addToResultSet(Result, '$');
            } else {
                int j = 2;
                while (j < prod.length()) {
                    foundEpsilon = false;
                    FIRST(subResult, prod[j]);
                    for (char ch : subResult) {
                        addToResultSet(Result, ch);
                    }
                    for (char ch : subResult) {
                        if (ch == '$') {
                            foundEpsilon = true;
                            break;
                        }
                    }
                    if (!foundEpsilon) break;
                    j++;
                }
            }
        }
    }
}

void addToResultSet(string &Result, char val) {
    if (Result.find(val) == string::npos) {
        Result += val;
    }
}