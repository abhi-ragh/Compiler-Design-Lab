%{
int COMMENT=0;
%}
identifier [a-zA-Z_][a-zA-Z0-9_]*
%%
#.* { printf("\n%s is a preprocessor directive\n", yytext); }
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
goto { if (!COMMENT) printf("kwd "); }
"/*" { COMMENT=1; }
"*/" { COMMENT=0; }
"+" { if (!COMMENT) printf("op-plus "); }
"-" { if (!COMMENT) printf("op-sub "); }
"*" { if (!COMMENT) printf("op-mul "); }
"/" { if (!COMMENT) printf("op-div "); }
"(" { if (!COMMENT) printf("( "); }
")" { if (!COMMENT) printf(") "); }
"{" { if (!COMMENT) printf("\nblock begins \n"); }
"}" { if (!COMMENT) printf("\nblock ends \n"); }
";" { if (!COMMENT) printf("; "); }
"=" { if (!COMMENT) printf("op-equ "); }
"<=" |
">=" |
"<" |
"==" |
">" { if (!COMMENT) printf("rel-op "); }
{identifier}\( { if (!COMMENT) printf("id ( "); }
{identifier} { if (!COMMENT) printf("id "); }
\".*\" { if (!COMMENT) printf("str "); }
[0-9]+ { if (!COMMENT) { printf("num "); ECHO; } }
[ \t]+ { /* Ignore whitespace */ }
\n { if (!COMMENT) printf("\n"); }
. { if (!COMMENT) printf("Unknown token: %s\n", yytext); }
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
