#include <stdio.h>
#include <string.h>
#include <ctype.h>

int i = 1, j = 0, no = 0, tmpch = 90;
char str[100], left[15], right[15];
void findopr();
int explore();
void fleft(int);
void fright(int);

struct exp {
    int pos;
    char op;
} k[15];

void main() {
    printf("\tIntermediate code generation\n\n");
    printf("Enter The Expression: ");
    scanf("%s", str);
    printf("\nThe Intermediate Code:\texpression in:\n");
    findopr();
    explore();
}

void findopr() {
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            k[j].pos = i;
            k[j++].op = str[i];
        }
    }
}

int explore() {
    int i = j - 1;  // Start from the last operator
    while (i >= 0) {
        fleft(k[i].pos);
        fright(k[i].pos);
        str[k[i].pos] = tmpch--;
        printf("\t%c := %s%c%s\t\t", str[k[i].pos], left, k[i].op, right);
        for (int m = 0; m < strlen(str); m++)
            if (str[m] != '$')
                printf("%c", str[m]);
        printf("\n");
        i--;
    }
    
    // Handle assignment
    char lhs[15], rhs[15];
    sscanf(str, "%[^=]=%s", lhs, rhs);
    printf("\t%s := %c\n", lhs, rhs[0]);
    return 0;
}

void fleft(int x) {
    int w = 0, flag = 0;
    x--;
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '/' && str[x] != '=' && str[x] != '-') {
        if (str[x] != '$' && flag == 0) {
            left[w++] = str[x];
            left[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x--;
    }
    // Reverse the left string
    int start = 0;
    int end = strlen(left) - 1;
    while (start < end) {
        char temp = left[start];
        left[start] = left[end];
        left[end] = temp;
        start++;
        end--;
    }
}

void fright(int x) {
    int w = 0, flag = 0;
    x++;
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '/' && str[x] != '=' && str[x] != '-') {
        if (str[x] != '$' && flag == 0) {
            right[w++] = str[x];
            right[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x++;
    }
}
