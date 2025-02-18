#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

// List of C++ keywords
const vector<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

// Function to check if a string is a keyword
bool isKeyword(const string &str) {
    for (const auto &keyword : keywords) {
        if (str == keyword) {
            return true;
        }
    }
    return false;
}

// Function to check if an identifier is valid
bool isValidIdentifier(const string &str) {
    if (str.empty() || (!isalpha(str[0]) && str[0] != '_')) {
        return false; // Must start with a letter or underscore
    }
    
    for (size_t i = 1; i < str.length(); i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return false; // Must contain only letters, digits, or underscore
        }
    }

    return !isKeyword(str); // Should not be a keyword
}

int main() {
    string identifier;

    cout << "Enter an identifier: ";
    cin >> identifier;

    if (isValidIdentifier(identifier)) {
        cout << "\"" << identifier << "\" is a valid identifier." << endl;
    } else {
        cout << "\"" << identifier << "\" is not a valid identifier." << endl;
    }

    return 0;
}