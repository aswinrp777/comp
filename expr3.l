//expr3.l
%{
#include "y.tab.h"
%}
%%
[a-zA-Z][a-zA-Z_0-9]* return letter;
[0-9]                 return digit;
.                     return yytext[0];
\n
%%
int yywrap()
{
return 1;
}


//expr3.y
%{
#include<stdio.h>
int valid=1;
%}
%token digit letter
%%
start :letter s
s:letter s
  | digit s
  |
  ;
%%
int yyerror()
{
printf("\n Not an identifier\n");
valid=0;
return 0;
}
int main()
{
printf("\nEnter input:\n");
yyparse();
if(valid)
{
printf("\nIt is an identifier\n");
}
}
