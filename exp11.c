//exp11.c - Intermediate Code Generation for Arithmetic Expressions

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char str[100], left[15], right[15];
int tmpch = 90;  

struct exp {
    int pos;
    char op;
} k[15];

int nOps = 0;

void findopr();
void explore();
void fleft(int);
void fright(int);

int main() {
    printf("\t\tINTERMEDIATE CODE GENERATION\n\n");
    printf("Enter the Expression: ");
    scanf("%s", str);

    findopr();
    explore();

    return 0;
}

void findopr() {
    int len = strlen(str);
    nOps = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            k[nOps].pos = i;
            k[nOps].op = str[i];
            nOps++;
        }
    }
}

void fleft(int x) {
    int w = 0;
    x--;
    while (x >= 0 && str[x] != '+' && str[x] != '-' && str[x] != '*' && str[x] != '/') {
        if (str[x] != '$') {  
            left[w++] = str[x];
        }
        x--;
    }
    left[w] = '\0';

    for (int i = 0; i < w / 2; i++) {
        char tmp = left[i];
        left[i] = left[w - i - 1];
        left[w - i - 1] = tmp;
    }
}

void fright(int x) {
    int w = 0;
    int len = strlen(str);
    x++;
    while (x < len && str[x] != '+' && str[x] != '-' && str[x] != '*' && str[x] != '/') {
        if (str[x] != '$') {  
            right[w++] = str[x];
        }
        x++;
    }
    right[w] = '\0';
}

void print_intermediate(int idx) {
    fleft(k[idx].pos);
    fright(k[idx].pos);
    char temp = tmpch--;
    printf("\t%c := %s %c %s\n", temp, left, k[idx].op, right);
    str[k[idx].pos] = temp;

    for (int i = k[idx].pos - 1; i >= 0 && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/'; i--) {
        str[i] = '$';
    }

    for (int i = k[idx].pos + 1; i < (int)strlen(str) && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/'; i++) {
        str[i] = '$';
    }
    k[idx].op = '#';  
}

void explore() {

    for (int i = 0; i < nOps; i++) {
        if (k[i].op == '*' || k[i].op == '/') {
            print_intermediate(i);
        }
    }

    for (int i = 0; i < nOps; i++) {
        if (k[i].op == '+' || k[i].op == '-') {
            print_intermediate(i);
        }
    }


    for (int i = 0; i < (int)strlen(str); i++) {
        if (str[i] != '$' && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/') {
            printf("\tResult := %c\n", str[i]);
            break;
        }
    }
}


/*input:
enter the Expression: a+b*c-d/e
*/