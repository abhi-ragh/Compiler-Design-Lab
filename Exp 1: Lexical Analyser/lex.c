#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check if a token is a keyword
int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
        "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while"
    };

    int i, flag = 0;
    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }
    return flag;
}

// Function to check if a token is an operator
int isOperator(char ch) {
    char operators[] = "+-*/%=,;()";
    int i, flag = 0;
    for (i = 0; i < strlen(operators); ++i) {
        if (ch == operators[i]) {
            flag = 1;
            break;
        }
    }
    return flag;
}

// Main function for lexical analysis
int main() {
    FILE *fp;
    char ch, buffer[15];
    int i, j = 0;

    fp = fopen("lexical.txt", "r");
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (isalnum(ch)) {
            buffer[j++] = ch;
        } else if ((ch == ' ' || ch == '\n') && (j != 0)) {
            buffer[j] = '\0';
            j = 0;
            if (isKeyword(buffer))
                printf("%s : keyword\n", buffer);
            else
                printf("%s : identifier\n", buffer);
        } else if (isOperator(ch)) {
            printf("%c : operator\n", ch);
        }
    }

    fclose(fp);
    return 0;
}

