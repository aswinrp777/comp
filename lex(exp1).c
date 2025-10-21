#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char *keywords[] = {
    "int", "float", "char", "if", "else", "while", "for", "return", "void", "main"
};
int num_keywords = 10;

int isKeyword(char *word) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(keywords[i], word) == 0)
            return 1;
    }
    return 0;
}

int isSpecialSymbol(char ch) {
    return ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}';
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '=' ||
           ch == '<' || ch == '>' || ch == '!';
}

int main() {
    FILE *file;
    char ch, word[MAX];
    int i;

    file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("Error: Input file not found.\n");
        exit(0);
    }

    printf("Lexical Analysis Output:\n");

    while ((ch = fgetc(file)) != EOF) {

        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        if (ch == '"') {
            i = 0;
            word[i++] = ch;
            while ((ch = fgetc(file)) != '"' && ch != EOF)
                word[i++] = ch;
            word[i++] = '"';
            word[i] = '\0';
            printf("String Literal\t\t: %s\n", word);
            continue;
        }
       
        if (ch == '\'') {
            char c = fgetc(file); 
            fgetc(file);          
            printf("Char Literal\t\t: '%c'\n", c);
            continue;
        }

        if (ch == '/') {
            char next = fgetc(file);
            if (next == '/') {
            
                while ((ch = fgetc(file)) != '\n' && ch != EOF);
                continue;
            } else if (next == '*') {

                while (1) {
                    ch = fgetc(file);
                    if (ch == '*' && fgetc(file) == '/')
                        break;
                }
                continue;
            } else {
                ungetc(next, file);
            }
        }


        if (isalpha(ch) || ch == '_') {
            i = 0;
            word[i++] = ch;
            while (isalnum(ch = fgetc(file)) || ch == '_')
                word[i++] = ch;
            word[i] = '\0';
            ungetc(ch, file);

            if (isKeyword(word))
                printf("Keyword\t\t\t: %s\n", word);
            else
                printf("Identifier\t\t: %s\n", word);
        }

        else if (isdigit(ch)) {
            i = 0;
            word[i++] = ch;
            while (isdigit(ch = fgetc(file)))
                word[i++] = ch;
            word[i] = '\0';
            ungetc(ch, file);
            printf("Constant\t\t: %s\n", word);
        }

        else if (isOperator(ch)) {
            char op[3];
            op[0] = ch;
            op[1] = fgetc(file);
            op[2] = '\0';

            if ((op[0] == '=' && op[1] == '=') ||
                (op[0] == '!' && op[1] == '=') ||
                (op[0] == '<' && op[1] == '=') ||
                (op[0] == '>' && op[1] == '=')) {
                printf("Relational Operator\t\t: %s\n", op);
            } else {
                ungetc(op[1], file);
                printf("Operator\t\t: %c\n", op[0]);
            }
        }

        else if (isSpecialSymbol(ch)) {
            printf("Special Symbol\t\t: %c\n", ch);
        }

        else {
            printf("Unknown Component\t: %c\n", ch);
        }
    }

    fclose(file);
    return 0;
}


/*input.txt
//Input for Lexical analyser
/*Multi line*/
int main() {
    int a = 70;
    float b = 105.5;
    if (a < b) {
        a = a * 2;
    }
    printf("%d",a);
}
*/

