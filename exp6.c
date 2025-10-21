//exp6.c nfa to dfa
#include <stdio.h>
#define MAX_STATES 20
#define MAX_SYMBOLS 10
#define MAX_DFA_STATES 1000
typedef struct {
    int states[MAX_STATES], count;
} StateSet;
int n_states, n_symbols, start_state, n_final;
char symbols[MAX_SYMBOLS];
int final_states[MAX_STATES];
StateSet nfa_transitions[MAX_STATES][MAX_SYMBOLS];
StateSet dfa_states[MAX_DFA_STATES];
int dfa_transitions[MAX_DFA_STATES][MAX_SYMBOLS];
int dfa_final[MAX_DFA_STATES];
int dfa_state_count = 0;
int contains(StateSet *set, int s) {
    for (int i = 0; i < set->count; i++) if (set->states[i] == s) return 1;
    return 0;
}
void add_state(StateSet *set, int s) {
    if (!contains(set, s)) set->states[set->count++] = s;
}
int equals(StateSet *a, StateSet *b) {
    if (a->count != b->count) return 0;
    for (int i = 0; i < a->count; i++)
        if (!contains(b, a->states[i])) return 0;
    return 1;
}
int sym_index(char c) {
    for (int i = 0; i < n_symbols; i++)
        if (symbols[i] == c) return i;
    return -1;
}
int find_dfa(StateSet *set) {
    for (int i = 0; i < dfa_state_count; i++)
        if (equals(set, &dfa_states[i])) return i;
    return -1;
}
int is_final(StateSet *set) {
    for (int i = 0; i < set->count; i++)
        for (int j = 0; j < n_final; j++)
            if (set->states[i] == final_states[j]) return 1;
    return 0;
}
void nfa_to_dfa() {
    dfa_state_count = 0;
    dfa_states[0].count = 0;
    add_state(&dfa_states[0], start_state);
    dfa_final[0] = is_final(&dfa_states[0]);
    dfa_state_count = 1;

    for (int processed = 0; processed < dfa_state_count; processed++) {
        StateSet *curr = &dfa_states[processed];
        for (int sym = 0; sym < n_symbols; sym++) {
            StateSet next = { .count = 0 };
            for (int i = 0; i < curr->count; i++) {
                StateSet *trans = &nfa_transitions[curr->states[i]][sym];
                for (int j = 0; j < trans->count; j++)
                    add_state(&next, trans->states[j]);
            }
            if (next.count == 0)
                dfa_transitions[processed][sym] = -1;
            else {
                int idx = find_dfa(&next);
                if (idx == -1) {
                    idx = dfa_state_count++;
                    dfa_states[idx] = next;
                    dfa_final[idx] = is_final(&next);
                }
                dfa_transitions[processed][sym] = idx;
            }
        }
    }
}
void print_stateset(StateSet *set) {
    printf("{");
    for (int i = 0; i < set->count; i++) {
        printf("%d", set->states[i]);
        if (i < set->count - 1) printf(",");
    }
    printf("}");
}
int main() {
    printf("Number of NFA states: "); scanf("%d", &n_states);
    printf("Number of input symbols: "); scanf("%d", &n_symbols);
    printf("Input symbols: ");
    for (int i = 0; i < n_symbols; i++) scanf(" %c", &symbols[i]);
    for (int i = 0; i < n_states; i++)
        for (int j = 0; j < n_symbols; j++)
            nfa_transitions[i][j].count = 0;
    int n_transitions;
    printf("Number of NFA transitions: "); scanf("%d", &n_transitions);
    printf("Transitions (from_state symbol to_state):\n");
    for (int i = 0; i < n_transitions; i++) {
        int from, to; char sym;
        scanf("%d %c %d", &from, &sym, &to);
        int si = sym_index(sym);
        if (si == -1) {
            printf("Invalid symbol '%c'\n", sym);
            return 1;
        }
        add_state(&nfa_transitions[from][si], to);
    }
    printf("Start state: "); scanf("%d", &start_state);
    printf("Number of final states: "); scanf("%d", &n_final);
    printf("Final states: ");
    for (int i = 0; i < n_final; i++) scanf("%d", &final_states[i]);
    nfa_to_dfa();
    printf("\nDFA states:\n");
    for (int i = 0; i < dfa_state_count; i++) {
        printf("DFA state %d: ", i);
        print_stateset(&dfa_states[i]);
        if (dfa_final[i]) printf(" [Final]");
        printf("\n");
    }
    printf("\nDFA transitions:\n");
    for (int i = 0; i < dfa_state_count; i++) {
        for (int j = 0; j < n_symbols; j++) {
            printf("δ(%d, %c) -> ", i, symbols[j]);
            int t = dfa_transitions[i][j];
            if (t == -1) printf("None\n");
            else printf("%d\n", t);
        }
    }
    printf("\nDFA start state: 0\nDFA final states: ");
    for (int i = 0; i < dfa_state_count; i++)
        if (dfa_final[i]) printf("%d ", i);
    printf("\n");

    return 0;
}



/*input
nfa states=3
input symbols=2
symbols=a b
nfa transitions=4
transitions:
0 a 0
0 a 1
1 b 2
2 b 2
start state=0
final states=1
final states list=2
*/



