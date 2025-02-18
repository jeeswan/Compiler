#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

// Function to count operators in an expression
int countOperators(const string &expression) {
    int count = 0;
    for (char ch : expression) {
        switch (ch) {
        case '+': case '-': case '*': case '/': case '=':
            count++;
            break;
        default:
            break;
        }
    }
    return count;
}

int main() {
    string expression;

    cout << "Enter an expression: ";
    getline(cin, expression);
    
    int count = countOperators(expression);
    cout << "The number of operators in the expression is " << count << endl;

    return 0;
}