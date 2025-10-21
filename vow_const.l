%{
#include <stdio.h>

int vowels = 0;
int consonants = 0;
%}

%%
[aAeEiIoOuU]      { vowels++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]   { consonants++; }
.|\n              { /* Ignore other characters */ }
%%

int main(int argc, char **argv) {
    printf("Enter text: ");
    yylex();  // Start lexical analysis
    printf("\nNumber of vowels: %d\n", vowels);
    printf("Number of consonants: %d\n", consonants);
    return 0;
}

int yywrap() {
    return 1;
}

