//exp5.c nfa with E transition to nfa without E transition
#include <stdio.h>
#include <string.h>

#define N 20

int n, m, start, finals[N], is_final[N];
char sym[N];
int trans[N][N][N], e_trans[N][N], closure[N][N], result[N][N][N];

void compute_e_closure() {
    for (int i = 0; i < n; i++) closure[i][i] = 1;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (closure[i][k] || e_trans[i][k])
                for (int j = 0; j < n; j++)
                    if (closure[k][j]) closure[i][j] = 1;
}

int symbol_index(char c) {
    for (int i = 0; i < m; i++) if (sym[i] == c) return i;
    return -1;
}

void build_nfa() {
    for (int s = 0; s < n; s++) {
        for (int a = 0; a < m; a++) {
            for (int i = 0; i < n; i++) {
                if (!closure[s][i]) continue;
                for (int j = 0; j < n; j++) {
                    if (trans[i][a][j])
                        for (int k = 0; k < n; k++)
                            if (closure[j][k]) result[s][a][k] = 1;
                }
            }
        }
        for (int i = 0; i < n; i++)
            if (closure[s][i] && is_final[i])
                finals[s] = 1;
    }
}

void print_nfa() {
    printf("\nNFA without ε-transitions:\n");
    printf("Start State: q%d\nFinal States:", start);
    for (int i = 0; i < n; i++) if (finals[i]) printf(" q%d", i);
    printf("\nTransitions:\n");
    for (int s = 0; s < n; s++)
        for (int a = 0; a < m; a++) {
            int found = 0;
            printf("δ(q%d, %c) → {", s, sym[a]);
            for (int d = 0; d < n; d++)
                if (result[s][a][d]) {
                    printf(" q%d", d);
                    found = 1;
                }
            printf(found ? " }\n" : " }\n");
        }
}

int main() {
    printf("States: "); scanf("%d", &n);
    printf("Symbols: "); scanf("%d", &m);
    printf("Enter symbols: ");
    for (int i = 0; i < m; i++) scanf(" %c", &sym[i]);

    printf("Transitions (from symbol to), 'e' for epsilon, -1 to stop:\n");
    while (1) {
        int from, to;
        char c;
        if (scanf("%d", &from) != 1 || from == -1) break;
        if (scanf(" %c %d", &c, &to) != 2) break;

        if (c == 'e') e_trans[from][to] = 1;
        else {
            int idx = symbol_index(c);
            if (idx != -1) trans[from][idx][to] = 1;
        }
    }

    printf("Start state: "); scanf("%d", &start);
    int f;
    printf("Number of final states: "); scanf("%d", &f);
    printf("Final states: ");
    for (int i = 0; i < f; i++) {
        int x; scanf("%d", &x); is_final[x] = 1;
    }

    compute_e_closure();
    build_nfa();
    print_nfa();

    return 0;
}

/*input
states:4
symbols:2
enter symbols: a b
transition:
0 e 1
0 e 2
1 a 1
1 e 3
2 b 2
3 a 3
-1
start state:0
number of final states:1
final states:2
*/