%{
#include <stdio.h>
%}
%%
[\t\n] 
"//".*

[a-zA-Z][a-zA-Z0-9]* {printf("identifier: %s\n",yytext);}
. {/* ignore */}
%%
int yywrap(){
	return 1;
}
int main(){
	printf("Enter your input: ");
	yylex();
	return 0;
}
