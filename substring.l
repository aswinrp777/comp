%{
#include<stdio.h>
%}
%option noyywrap
%%
abc	{printf("ABC");}
.|\n	{ECHO;}
%%
int main(){
	yylex();
	return 0;
}
