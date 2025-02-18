#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

char op[2], arg1[5], arg2[5], result[5];

int main() {
    // Ensure the input file exists
    ofstream checkFile("input.txt", ios::app); // Opens in append mode, creates if it doesn't exist
    checkFile.close(); // Close immediately, no need to write anything

    // Open the input and output files
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    // Check if the input file is open
    if (!inputFile.is_open()) {
        cerr << "Error opening input.txt file!" << endl;
        return 1;
    }
    
    // Check if the output file is open
    if (!outputFile.is_open()) {
        cerr << "Error opening output.txt file!" << endl;
        return 1;
    }

    // Process each line from the input file
    while (inputFile >> op >> arg1 >> arg2 >> result) {
        if (strcmp(op, "+") == 0) {
            outputFile << "MOV R0, " << arg1 << endl;
            outputFile << "ADD R0, " << arg2 << endl;
            outputFile << "MOV " << result << ", R0" << endl;
        } else if (strcmp(op, "*") == 0) {
            outputFile << "MOV R0, " << arg1 << endl;
            outputFile << "MUL R0, " << arg2 << endl;
            outputFile << "MOV " << result << ", R0" << endl;
        } else if (strcmp(op, "-") == 0) {
            outputFile << "MOV R0, " << arg1 << endl;
            outputFile << "SUB R0, " << arg2 << endl;
            outputFile << "MOV " << result << ", R0" << endl;
        } else if (strcmp(op, "/") == 0) {
            outputFile << "MOV R0, " << arg1 << endl;
            outputFile << "DIV R0, " << arg2 << endl;
            outputFile << "MOV " << result << ", R0" << endl;
        } else if (strcmp(op, "=") == 0) {
            outputFile << "MOV R0, " << arg1 << endl;
            outputFile << "MOV " << result << ", R0" << endl;
        }
    }

    // Close the files
    inputFile.close();
    outputFile.close();

    cout << "Assembly code successfully written to output.txt" << endl;
    
    return 0;
}