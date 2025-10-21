//ex3.l(arithmetic expression & result)
%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t\n]+    ;  // Ignore whitespace
.           { return *yytext; }
%%

int yywrap() {
    return 1;
}


//ex3.y
%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%left '&'

%%

input:
    E { printf("Result = %d\n", $1); }
;

E:
      E '+' E   { $$ = $1 + $3; }
    | E '-' E   { $$ = $1 - $3; }
    | E '*' E   { $$ = $1 * $3; }
    | E '/' E   {
                  if ($3 == 0) {
                      yyerror("Division by zero");
                      exit(1);
                  }
                  $$ = $1 / $3;
                }
    | E '&' E   { $$ = $1 & $3; }
    | '(' E ')' { $$ = $2; }
    | NUMBER    { $$ = $1; }
;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main() {
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}


