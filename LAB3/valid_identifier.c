#include <stdio.h>
#include <ctype.h>
#include <string.h>

// List of C keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

// Function to check if a string is a keyword
int isKeyword(const char *str) {
    int size = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < size; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if an identifier is valid
int isValidIdentifier(const char *str) {
    if (!isalpha(str[0]) && str[0] != '_') {
        return 0; // Must start with letter or underscore
    }
    
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return 0; // Must contain only letters, digits, or underscore
        }
    }

    if (isKeyword(str)) {
        return 0; // Should not be a keyword
    }

    return 1;
}

int main() {
    char identifier[50];

    printf("Enter an identifier: ");
    scanf("%s", identifier);

    if (isValidIdentifier(identifier)) {
        printf("\"%s\" is a valid identifier.\n", identifier);
    } else {
        printf("\"%s\" is not a valid identifier.\n", identifier);
    }

    return 0;
}
