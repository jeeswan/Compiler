#include <stdio.h>
#include <string.h>

char op[2], arg1[5], arg2[5], result[5];

int main() {
    FILE *fp1, *fp2;
    
    // Open input and output files
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read input file line by line
    while (fscanf(fp1, "%s %s %s %s", op, arg1, arg2, result) != EOF) {
        
        if (strcmp(op, "+") == 0) {
            fprintf(fp2, "MOV R0, %s\n", arg1);
            fprintf(fp2, "ADD R0, %s\n", arg2);
            fprintf(fp2, "MOV %s, R0\n", result);
        } 
        else if (strcmp(op, "-") == 0) {
            fprintf(fp2, "MOV R0, %s\n", arg1);
            fprintf(fp2, "SUB R0, %s\n", arg2);
            fprintf(fp2, "MOV %s, R0\n", result);
        } 
        else if (strcmp(op, "*") == 0) {
            fprintf(fp2, "MOV R0, %s\n", arg1);
            fprintf(fp2, "MUL R0, %s\n", arg2);
            fprintf(fp2, "MOV %s, R0\n", result);
        } 
        else if (strcmp(op, "/") == 0) {
            fprintf(fp2, "MOV R0, %s\n", arg1);
            fprintf(fp2, "DIV R0, %s\n", arg2);
            fprintf(fp2, "MOV %s, R0\n", result);
        } 
        else if (strcmp(op, "=") == 0) {
            fprintf(fp2, "MOV R0, %s\n", arg1);
            fprintf(fp2, "MOV %s, R0\n", result);
        } 
        else {
            fprintf(fp2, "INVALID OPERATION: %s\n", op);
        }
    }

    // Close files
    fclose(fp1);
    fclose(fp2);

    printf("Machine code generated successfully in output.txt\n");

    return 0;
}