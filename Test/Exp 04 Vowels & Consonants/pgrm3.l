%{
   #include <stdio.h>
   int vowels = 0;
   int consonants = 0;
%}

%%
[aeiouAEIOU] {vowels++;}
[a-zA-Z] {consonants++;}
  
\n {return 1;}  
%%

void main(){
   printf("Enter your input: ");
   yylex();
   printf("Vowels = %d\nConsonants = %d\n",vowels,consonants);
}

int yywrap(){
   return 1;
}
