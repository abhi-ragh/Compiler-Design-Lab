#include <stdio.h>
#include <string.h>
#include <ctype.h>

void E();
void T();
void Eprime();
void Tprime();
void check();
int count,flag;
char expression[15];

void main(){
    count = 0;
    flag = 0;

    printf("E -> TE' \nE' -> +TE'|e \nT -> FT' \nT' -> *FT'|e \nF -> (E) | a\n");
    printf("Enter Expression: ");
    scanf("%s",expression);
    E();

    if(strlen(expression)==count && flag == 0)
        printf("Valid\n");
    else
        printf("Invalid\n ");
}

void E(){
    T();
    Eprime();
}
    
void T(){
    check();
    Tprime();
}

void Tprime(){
    if(expression[count]=='*'){
        count++;
        check();
        Tprime();
    }
}

void check(){
    if (isalpha(expression[count]))
        count++;
    else if (expression[count]=='('){
        count++;
        E();
        if(expression[count]==')')
            count++;
        else
            flag = 1;
    }
    else
        flag = 1;
}

void Eprime(){
    if(expression[count]=='+'){
        count++;
        T();
        Eprime();
    }
}
