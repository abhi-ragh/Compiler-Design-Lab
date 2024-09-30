%{
#include <stdio.h>
%}
%%
[0-9]+ {printf("Number: %s\n",yytext);}
[ \t\n ]
"+"|"-"|"*"|"/" {printf("Operator: %s\n",yytext);}
"(" {printf("Left Parenthesis: %s\n",yytext);}
")" {printf("Right Parenthesis: %s\n",yytext);}
. {printf("Invalid Character: %s\n",yytext);}
%%
int yywrap(){
  return 0;
}
int main(){
  printf("Enter the input: ");
  yylex();
  return 0;
}
