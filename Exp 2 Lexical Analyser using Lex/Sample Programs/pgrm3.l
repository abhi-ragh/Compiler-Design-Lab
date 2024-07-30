%{ 
#include <stdio.h>
int vowels = 0;
int consonants = 0; 
%}

%%
[aeiouAEIOU] {vowels++;}
[a-zA-Z] {consonants++;}
\n { return(1);} 
%%
int main(){
	printf("Enter Your Input: ");
	yylex();
	printf("Total no. of vowels: %d\n",vowels);
	printf("Total no. of consonants: %d\n",consonants);
	return 0;
}

int yywrap(){
	return 1;
}

