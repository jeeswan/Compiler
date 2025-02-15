#include <stdio.h>
#include <string.h>
#include <ctype.h>

int numProductions;
char productions[10][10];

void follow(char result[], char c);
void first(char result[], char c);
void addToResultSet(char result[], char val);

int main() {
    int i;
    char c, result[20];

    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);

    printf("Enter the productions:\n");
    for (i = 0; i < numProductions; i++) {
        scanf("%s", productions[i]);
    }

    printf("Find FOLLOW of: ");
    scanf(" %c", &c);

    follow(result, c);
    printf("FOLLOW(%c) = { ", c);
    for (i = 0; result[i] != '\0'; i++) {
        printf("%c ", result[i]);
    }
    printf("}\n");

    return 0;
}

void follow(char result[], char c) {
    int i, j, k;
    char subResult[20];
    result[0] = '\0';

    // If c is the start symbol, add '$' to FOLLOW(c)
    if (productions[0][0] == c) {
        addToResultSet(result, '$');
    }

    // Scan all productions
    for (i = 0; i < numProductions; i++) {
        size_t len = strlen(productions[i]);
        for (j = 2; j < len; j++) { // Start from the 2nd character (after the arrow)
            if (productions[i][j] == c) { // Found c in RHS
                subResult[0] = '\0'; // Reset subResult before using it

                if (productions[i][j + 1] != '\0') { // If next symbol exists
                    first(subResult, productions[i][j + 1]);

                    // Add FIRST of next symbol (excluding ε)
                    for (k = 0; subResult[k] != '\0'; k++) {
                        if (subResult[k] != '#') { 
                            addToResultSet(result, subResult[k]);
                        }
                    }

                    // If ε is in FIRST(next), also add FOLLOW(LHS)
                    for (k = 0; subResult[k] != '\0'; k++) {
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

void first(char result[], char c) {
    int i;
    result[0] = '\0'; // Reset result at the beginning

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

void addToResultSet(char result[], char val) {
    int i;
    for (i = 0; result[i] != '\0'; i++) {
        if (result[i] == val) return; // Avoid duplicates
    }
    result[i] = val; // Add new value to result
    result[i + 1] = '\0'; // Null terminate the string
}