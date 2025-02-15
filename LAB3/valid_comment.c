#include <stdio.h>
#include <string.h>

// Function to check if a given string is a valid comment
int isValidComment(const char *str) {
    int len = strlen(str);
    
    // Check for single-line comment (starts with //)
    if (len >= 2 && str[0] == '/' && str[1] == '/') {
        return 1;
    }

    // Check for multi-line comment (starts with /* and ends with */)
    if (len >= 4 && str[0] == '/' && str[1] == '*' && str[len - 2] == '*' && str[len - 1] == '/') {
        return 1;
    }

    return 0;
}

int main() {
    char comment[100];

    printf("Enter a comment: ");
    fgets(comment, sizeof(comment), stdin);

    // Remove newline character if present
    comment[strcspn(comment, "\n")] = 0;

    if (isValidComment(comment)) {
        printf("\"%s\" is a valid comment.\n", comment);
    } else {
        printf("\"%s\" is not a valid comment.\n", comment);
    }

    return 0;
}
