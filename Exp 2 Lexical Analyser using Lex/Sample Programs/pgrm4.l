%{ 
#include <stdio.h>
int lines = 1;
int words = 0;
int chars = 0; 
%}

%%

\n { lines++;chars++;}
[a-zA-Z]+ {words++;chars+=strlen(yytext);}
. {chars++;}
\n\n {return 0;}

%%
int main(){
	printf("Enter Your Input: ");
	yylex();
	printf("No of lines: %d\n",lines);
	printf("No of words: %d\n",words);
	printf("No of chars: %d\n",chars);
}

int yywrap(){
	return 1;
}
