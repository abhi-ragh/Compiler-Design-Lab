#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void main(){
    int i,j=0;
    char ch, buffer[15];
    char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
        "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while"
    };
    FILE *fp;
    char operators[] = "+-*/%()=;"; 
    
    fp = fopen("input.txt","r");
    
    while( (ch=fgetc(fp)) != EOF ) {
        if(isalnum(ch))
            buffer[j++] = ch;
        else if ( ch == ' ' || ch == '\n' && j != 0 ){
            buffer[j] = '\0';
            j = 0;

            int isKeyword = 0;
            for(i=0;i<32;i++){
                if(strcmp(keywords[i],buffer)==0){
                    isKeyword = 1;
                    break;        
                }            
            }
            
            if(isKeyword==1)
                printf("%s : Keyword\n", buffer);
            else
                printf("%s : Identifier\n\n", buffer);
        }
        else if(strchr(operators,ch)){
            printf("%c : Operator\n",ch);
        }     
    }
}
