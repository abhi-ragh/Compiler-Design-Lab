%{
int COMMENT=0;
%}
identifier [a-zA-Z_][a-zA-Z0-9_]*
%%
#.* { printf("\n%s is a preprocessor directive", yytext); }

int |
float |
char |
double |
while |
for |
struct |
typedef |
do |
if |
break |
continue |
void |
switch |
return |
else |
goto { if (!COMMENT) printf("\nkwd "); }

"/*" { COMMENT=1; }
"*/" { COMMENT=0; }
"+" { if (!COMMENT) printf("\nop-plus "); }
"-" { if (!COMMENT) printf("\nop-sub "); }
"*" { if (!COMMENT) printf("\nop-mul "); }
"/" { if (!COMMENT) printf("\nop-div "); }
{identifier}\( { if (!COMMENT) printf("\nfun "); }
"{" { if (!COMMENT) printf("\nblock begins "); }
"}" { if (!COMMENT) printf("\nblock ends "); }
{identifier}(\[[0-9]*\])? { if (!COMMENT) printf("\nid "); }
\".*\" { if (!COMMENT) printf("\nstr "); }
[0-9]+ { if (!COMMENT) { printf("\n\t"); ECHO; printf("\n"); } }
"(" { if (!COMMENT) printf("\n( "); }
")" { if (!COMMENT) printf("\n) "); }
";" { if (!COMMENT) printf("\n; "); }
"=" { if (!COMMENT) printf("\nop-equ "); }
"<=" |
">=" |
"<" |
"==" |
">" { if (!COMMENT) printf("\nrel-op "); }
[ \t\n]+ { /* Ignore whitespace */ }
. { if (!COMMENT) printf("\nUnknown token: %s\n", yytext); }
%%
int main(int argc, char **argv) {
    FILE *file;
    file = fopen("input.c", "r");
    if (!file) {
        printf("could not open the file");
        exit(0);
    }
    yyin = file;
    yylex();
    printf("\n");
    return 0;
}

int yywrap() {
    return 1;
}
