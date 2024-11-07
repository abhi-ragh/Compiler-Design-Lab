%{
#include <stdio.h>
#include "y.tab.h"
extern int yylval;
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]+      ; /* Ignore whitespace */
\n          return 0; /* Return 0 to signal end of input */
.           return yytext[0]; /* Return any other character */
%%

int yywrap() {
    return 1;
}
