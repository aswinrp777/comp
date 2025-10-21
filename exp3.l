//exp3.l
%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+                      { yylval = atoi(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*      { return ID; }
[=+*/&()-]                  { return yytext[0]; }
[ \t\n]+                    ;  // Skip whitespace
.                           { return yytext[0]; }

%%

int yywrap() {
    return 1;
}

//exp3.y
%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token ID NUM

%left '+' '-'
%left '*' '/'
%left '&'

%%

input:
      assignment ';'   { printf("Expression is valid\n"); }
    | expr ';'         { printf("Expression is valid\n"); }
    ;

assignment:
    ID '=' expr
    ;

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '&' expr
    | '(' expr ')'
    | '-' expr
    | ID
    | NUM
    ;

%%

void yyerror(const char *s) {
    printf("Invalid expression!\n");
}

int main() {
    printf("Enter an expression:\n");
    return yyparse();
}

