%{
#include <stdio.h>

int tabs = 0;
int spaces = 0;
int specials = 0;
int lines = 0;
%}

%%

"\t"        { tabs++; }
" "         { spaces++; }
\n          { lines++; }
[^a-zA-Z0-9 \t\n] { specials++; }
.           { /* Ignore other characters */ }

%%

int main(int argc, char **argv) {
    printf("Enter text (Ctrl+D to end input):\n");
    yylex();
    printf("\nStatistics:\n");
    printf("Tabs: %d\n", tabs);
    printf("Spaces: %d\n", spaces);
    printf("Lines: %d\n", lines);
    printf("Special characters: %d\n", specials);
    return 0;
}

int yywrap() {
    return 1;
}

