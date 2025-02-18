#include <iostream>
#include <string>

using namespace std;

// Function to check if a given string is a valid comment
bool isValidComment(const string &str) {
    int len = str.length();
    
    // Check for single-line comment (starts with //)
    if (len >= 2 && str[0] == '/' && str[1] == '/') {
        return true;
    }

    // Check for multi-line comment (starts with /* and ends with */)
    if (len >= 4 && str[0] == '/' && str[1] == '*' && str[len - 2] == '*' && str[len - 1] == '/') {
        return true;
    }

    return false;
}

int main() {
    string comment;

    cout << "Enter a comment: ";
    getline(cin, comment);

    if (isValidComment(comment)) {
        cout << "\"" << comment << "\" is a valid comment." << endl;
    } else {
        cout << "\"" << comment << "\" is not a valid comment." << endl;
    }

    return 0;
}