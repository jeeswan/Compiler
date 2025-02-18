#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;

char s[20], stack[20];

int main() {
    // M table for parsing (transition rules)
    char m[5][6][4] = {
        {"tb", "", "", "tb", "", ""},
        {"", "+tb", "", "n", "n", "fc"},
        {"fc", "", "fc", "", "", ""},  // <== Fix: Change "" to "fc" in column 0
        {"", "n", "*fc", "a", "n", "n"},
        {"i", "", "", "(e)", "", ""}
    };

    // Size of each rule for parsing
    int size[5][6] = {
        {2, 0, 0, 2, 0, 0},
        {0, 3, 0, 0, 1, 1},
        {2, 0, 0, 2, 0, 0},
        {0, 1, 3, 0, 1, 1},
        {1, 0, 0, 3, 0, 0}
    };

    int i, j, k, str1, str2;

    cout << "Enter the input string: ";
    cin >> s;
    
    // Append '$' to the input string to mark the end
    strcat(s, "$");
    
    stack[0] = '$';
    stack[1] = 'e';

    i = 1; // Stack pointer
    j = 0; // Input pointer

    cout << left << setw(20) << "Stack" << "Input" << endl;
    cout << "-------------------------------------" << endl;

    while ((stack[i] != '$') && (s[j] != '$')) {
        cout << setw(20) << string(stack, stack + i + 1) << (s + j) << endl;

        // If stack and input match, pop from stack and move input pointer
        if (stack[i] == s[j]) {
            i--;
            j++;
            continue;
        }

        // Determine str1 based on the current stack symbol
        switch (stack[i]) {
            case 'e': str1 = 0; break;
            case 'b': str1 = 1; break;
            case 't': str1 = 2; break;
            case 'c': str1 = 3; break;
            case 'f': str1 = 4; break;
            default: cout << "\nERROR: Invalid symbol in stack" << endl; return 1;
        }

        // Determine str2 based on the current input symbol
        switch (s[j]) {
            case 'i': str2 = 0; break;
            case '+': str2 = 1; break;
            case '*': str2 = 2; break;
            case '(': str2 = 3; break;
            case ')': str2 = 4; break;
            case '$': str2 = 5; break;
            default: cout << "\nERROR: Invalid symbol in input" << endl; return 1;
        }

        // If no rule is available for the pair (str1, str2), exit with error
        if (m[str1][str2][0] == '\0') {
            cout << "\nERROR: No matching rule in parsing table" << endl;
            cout << "Stack Top: " << stack[i] << " (Index: " << str1 << ")" << endl;
            cout << "Current Input: " << s[j] << " (Index: " << str2 << ")" << endl;
            return 1;
        } 
        // If the rule is 'n', pop from stack (no replacement)
        else if (m[str1][str2][0] == 'n') {
            i--;
        } 
        // If the rule is 'i', push 'i' onto the stack
        else if (m[str1][str2][0] == 'i') {
            stack[i] = 'i';
        } 
        // Otherwise, apply the rule and push corresponding symbols onto the stack
        else {
            i--; // Remove the non-terminal
            for (k = size[str1][str2] - 1; k >= 0; k--) {
                stack[++i] = m[str1][str2][k];
            }
        }
    }

    cout << setw(20) << string(stack, stack + i + 1) << (s + j) << endl;
    cout << "\nSUCCESS: String is accepted!" << endl;
    return 0;
}