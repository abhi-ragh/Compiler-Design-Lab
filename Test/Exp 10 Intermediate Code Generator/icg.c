#include <stdio.h>
#include <string.h>

typedef struct {
    int pos;
    char op;
} Operator;

Operator operators[15];
char expression[100];
int op_count = 0;

void find_operators();
void generate_intermediate_code();
void get_operand(char* operand, int start, int direction);

int main() {
    printf("Intermediate Code Generation\n\n");
    printf("Enter the Expression: ");
    scanf("%s", expression);
    printf("\nIntermediate Code:\n");
    
    find_operators();
    generate_intermediate_code();
    
    return 0;
}

void find_operators() {
    // Identify operator positions and types
    for (int i = 0; expression[i] != '\0'; i++) {
        if (strchr("+-*/", expression[i])) {
            operators[op_count].pos = i;
            operators[op_count++].op = expression[i];
        }
    }
}

void generate_intermediate_code() {
    char left[15], right[15];
    int temp_var_count = 1;
    
    for (int i = op_count - 1; i >= 0; i--) {
        int pos = operators[i].pos;
        char op = operators[i].op;

        // Get operands and generate intermediate code
        get_operand(left, pos - 1, -1);
        get_operand(right, pos + 1, 1);
        printf("\tt%d := %s %c %s\n", temp_var_count, left, op, right);

        // Replace operator in expression with temporary variable (e.g., t1, t2, etc.)
        expression[pos] = 't';
        expression[pos + 1] = '0' + temp_var_count++;
    }

    // Handle the final assignment (e.g., a = t1)
    char lhs[15], rhs[15];
    sscanf(expression, "%[^=]=%s", lhs, rhs);
    printf("\t%s := %s\n", lhs, rhs);
}

void get_operand(char* operand, int start, int direction) {
    int w = 0;
    operand[0] = '\0';

    while (start >= 0 && expression[start] != '+' && expression[start] != '*' &&
           expression[start] != '/' && expression[start] != '=' && expression[start] != '-') {
        if (expression[start] != '$') {
            operand[w++] = expression[start];
            expression[start] = '$';
            break;
        }
        start += direction;
    }
    operand[w] = '\0';

    // Reverse for left operand
    if (direction == -1) {
        for (int i = 0, j = w - 1; i < j; i++, j--) {
            char temp = operand[i];
            operand[i] = operand[j];
            operand[j] = temp;
        }
    }
}

