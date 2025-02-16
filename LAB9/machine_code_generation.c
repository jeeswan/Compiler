#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char op[2], arg1[5], arg2[5], result[5];

int main() {
    // Ensure the input file exists
    FILE *checkFile = fopen("input.txt", "a"); // Opens in append mode, creates if it doesn't exist
    if (checkFile == NULL) {
        perror("Error creating input file");
        return 1;
    }
    fclose(checkFile);

    // Open the input and output files
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    // Check if the input file is open
    if (inputFile == NULL) {
        perror("Error opening input.txt file");
        return 1;
    }
    
    // Check if the output file is open
    if (outputFile == NULL) {
        perror("Error opening output.txt file");
        fclose(inputFile);
        return 1;
    }

    // Process each line from the input file
    while (fscanf(inputFile, "%s %s %s %s", op, arg1, arg2, result) == 4) {
        if (strcmp(op, "+") == 0) {
            fprintf(outputFile, "MOV R0, %s\n", arg1);
            fprintf(outputFile, "ADD R0, %s\n", arg2);
            fprintf(outputFile, "MOV %s, R0\n", result);
        } else if (strcmp(op, "*") == 0) {
            fprintf(outputFile, "MOV R0, %s\n", arg1);
            fprintf(outputFile, "MUL R0, %s\n", arg2);
            fprintf(outputFile, "MOV %s, R0\n", result);
        } else if (strcmp(op, "-") == 0) {
            fprintf(outputFile, "MOV R0, %s\n", arg1);
            fprintf(outputFile, "SUB R0, %s\n", arg2);
            fprintf(outputFile, "MOV %s, R0\n", result);
        } else if (strcmp(op, "/") == 0) {
            fprintf(outputFile, "MOV R0, %s\n", arg1);
            fprintf(outputFile, "DIV R0, %s\n", arg2);
            fprintf(outputFile, "MOV %s, R0\n", result);
        } else if (strcmp(op, "=") == 0) {
            fprintf(outputFile, "MOV R0, %s\n", arg1);
            fprintf(outputFile, "MOV %s, R0\n", result);
        }
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Assembly code successfully written to output.txt\n");
    
    return 0;
}
