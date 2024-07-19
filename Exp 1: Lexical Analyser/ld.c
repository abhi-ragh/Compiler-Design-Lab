#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int kwd(char buffer[15]);

int main() {
    char ch, buffer[15];
    FILE *fp;
    int j = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error while opening the file.\n");
        exit(1);
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (isalnum(ch)) {
            buffer[j++] = ch;
        } else if ((ch == ' ' || ch == '\n') && (j != 0)) {
            buffer[j] = '\0'; 
            j = 0;
            if (kwd(buffer) == 1) {
                printf("%s is a keyword\n", buffer);
            } else {
                printf("%s is an identifier\n", buffer);
            }
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
                   ch == '=' || ch == ';' || ch == ',' || ch == '(' || ch == ')') {
            printf("%c is an operator\n", ch);
        }
    }

    fclose(fp);
    return 0;
}

int kwd(char buffer[]) {
    char keywords[32][10] = { "auto","break","case","const","continue","default","do",
                              "double","else","enum","extern","float","for","goto","if",
                              "int","long","register","return","short","signed","sizeof",
                              "static","struct","switch","typedef","union","unsigned",
                              "void","volatile","while" };
    int i;
    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

