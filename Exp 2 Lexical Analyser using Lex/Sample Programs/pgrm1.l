%{#include <stdio.h>
%}
%%
if|else|for|switch|while|int|char|float { printf("%s is a keyword\n",yytext);}
[a-z|A-Z][(a-z)|A-Z|0-9]* { printf("%s is an identifier\n",yytext);}
. {}
%%
int yywrap(){
	return 1;
}
void main(){
	printf("\nEnter Input: ");
	yylex();
}
