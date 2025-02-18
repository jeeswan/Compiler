#include <iostream>
#include <cstring>

using namespace std;

int i = 0, j = 0, no = 0, tmpch = 90; // tmpch starts at ASCII 'Z'
char expr[100], leftOperand[15], rightOperand[15];

void findOperators();
void generateIntermediateCode();
void extractLeft(int);
void extractRight(int);

struct Operator {
    int pos;
    char op;
} operators[15];

int main() {
    cout << "Enter the expression: ";
    cin >> expr;
    cout << "The intermediate code:\t\tExpression\n";

    findOperators();
    generateIntermediateCode();
    
    return 0;
}

void findOperators() {
    char opList[] = {':', '/', '*', '+', '-'};
    int opListSize = sizeof(opList) / sizeof(opList[0]);
    for (int k = 0; k < opListSize; k++) {
        for (i = 0; expr[i] != '\0'; i++) {
            if (expr[i] == opList[k]) {
                operators[j].pos = i;
                operators[j].op = opList[k];
                j++;
            }
        }
    }
    operators[j].op = '\0'; // Mark end of operators
}

void generateIntermediateCode() {
    for (i = 0; operators[i].op != '\0'; i++) {
        // Clear buffers before extraction
        leftOperand[0] = '\0';
        rightOperand[0] = '\0';
        
        extractLeft(operators[i].pos);
        extractRight(operators[i].pos);
        
        expr[operators[i].pos] = tmpch--; // Assign temp variable
        
        // Print the intermediate code line:
        // Format: <temp> := <leftOperand><operator><rightOperand>   <updated expression>
        cout << "\t" << expr[operators[i].pos] << " := " 
             << leftOperand << operators[i].op << rightOperand << "\t\t";
        
        for (int k = 0; expr[k] != '\0'; k++) {
            if (expr[k] != '$')
                cout << expr[k];
        }
        cout << endl;
    }
    
    // Final extraction (if needed)
    extractRight(-1);
    if (no == 0) {
        extractLeft(strlen(expr));
        cout << "\t" << rightOperand << " := " << leftOperand << endl;
        return;
    }
    cout << "\t" << rightOperand << " := " << expr[operators[i - 1].pos] << endl;
}

void extractLeft(int x) {
    int w = 0;
    int flag = 0;
    x--; // Move one position left from the operator
    while (x >= 0 && strchr("+-*/:=", expr[x]) == NULL) {
        if (expr[x] != '$' && flag == 0) {
            leftOperand[w++] = expr[x];
            leftOperand[w] = '\0'; // Null-terminate
            expr[x] = '$';         // Mark as processed
            flag = 1;              // Only extract one character
        }
        x--;
    }
}

void extractRight(int x) {
    int w = 0;
    int flag = 0;
    x++; // Move one position right from the operator
    while (expr[x] != '\0' && strchr("+-*/:=", expr[x]) == NULL) {
        if (expr[x] != '$' && flag == 0) {
            rightOperand[w++] = expr[x];
            rightOperand[w] = '\0'; // Null-terminate
            expr[x] = '$';          // Mark as processed
            flag = 1;               // Only extract one character
        }
        x++;
    }
}