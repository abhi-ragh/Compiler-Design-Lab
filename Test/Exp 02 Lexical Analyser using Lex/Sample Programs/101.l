%{
	#include <stdio.h>
%}

%%

.*101.* {printf("Accepted string: %s\n",yytext);}
.|\n {return 0;}
%%
int main(){
	printf("Enter input: ");
	yylex();
}

int yywrap(){
	return 1;
}
