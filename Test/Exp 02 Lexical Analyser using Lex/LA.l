%{
int COMMENT = 0;
%}

identifier [a-zA-Z_][a-zA-Z0-9_]*
%%
#.* {printf("\n %s- Header\n",yytext);}

(int|float|char|double|while|for|struct|typedef|do|if|break|continue|void|switch|return|else|goto) {
    if (!COMMENT) printf("kwd %s\n ", yytext);
}

"/*" {COMMENT=1;} 
"*/" {COMMENT=0;}
"+"|"-"|"*"|"/"|"="|"%" {if(!COMMENT) printf("op-%s ",yytext);}
")" {if (!COMMENT) printf(")");}
"(" {if (!COMMENT) printf("(");}
"{" {if (!COMMENT) printf("\nblock begins\n");}
"}" {if (!COMMENT) printf("\nblock ends\n");}
";" {if (!COMMENT) printf("; ");}
">"|"<"|"<="|"=="|">=" {if (!COMMENT) printf("rel-op ");}
{identifier}\( {if (!COMMENT) printf("id( ");}
{identifier} {if (!COMMENT) printf("id ");}
\".*\" {if (!COMMENT) printf("str ");}
[0-9]+ {if (!COMMENT) printf("num %s",yytext);}
[ \t]+ { /* Ignore whitespace */ }
\n {if (!COMMENT) printf("\n");}
. {if (!COMMENT) printf("unknown token: %s\n",yytext);}
%%

int main(int argc,char **argv){
    FILE *fp = fopen("input.c","r");
    yyin = fp;
    yylex();
    printf("\n");
    return 0;
}

int yywrap(){
    return 1;
}
