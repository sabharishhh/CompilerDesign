#include <stdio.h>
#define MAX_STATES 10
#define MAX_ALPHABET 10
#define MAX_DFA_STATES 1024 // 2^MAX_STATES

int nfa[MAX_STATES][MAX_ALPHABET];        // NFA transitions (bitmasks)
int dfa[MAX_DFA_STATES][MAX_ALPHABET];    // DFA transitions
int dfa_states[MAX_DFA_STATES];           // list of DFA states (bitmasks)
int dfa_count = 0;

int state_exists(int state) {
    for (int i = 0; i < dfa_count; i++)
        if (dfa_states[i] == state) return i;
    return -1;
}

void print_state(int state, int nfa_states) {
    printf("{");
    int empty = 1;
    for (int i = 0; i < nfa_states; i++) {
        if (state & (1 << i)) {
            if (!empty) printf(",");
            printf("q%d", i);
            empty = 0;
        }
    }
    if (empty) printf("empty");
    printf("}");
}

int main() {
    int nfa_states, symbols;
    printf("Enter number of NFA states: ");
    scanf("%d", &nfa_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    printf("Enter NFA transition table:\n");
    printf("(Format: number of next states followed by list of states)\n");

    for (int i = 0; i < nfa_states; i++) {
        for (int j = 0; j < symbols; j++) {
            int count;
            printf("Transition(q%d, %d): ", i, j);
            scanf("%d", &count);
            int mask = 0;
            for (int k = 0; k < count; k++) {
                int s;
                scanf("%d", &s);
                mask |= (1 << s);
            }
            nfa[i][j] = mask;
        }
    }

    // Subset construction
    dfa_states[dfa_count++] = 1; // start {q0}

    for (int i = 0; i < dfa_count; i++) {
        for (int j = 0; j < symbols; j++) {
            int next = 0;
            for (int k = 0; k < nfa_states; k++) {
                if (dfa_states[i] & (1 << k))
                    next |= nfa[k][j];
            }
            int idx = state_exists(next);
            if (idx == -1) {
                dfa_states[dfa_count++] = next;
                idx = dfa_count - 1;
            }
            
            dfa[i][j] = idx;
        }
    }

    // Print DFA table
    printf("\nDFA Transition Table:\n\n");
    printf("%-15s", "State");
    for (int j = 0; j < symbols; j++)
        printf("%-15d", j);
    printf("\n");

    for (int i = 0; i < dfa_count; i++) {
        print_state(dfa_states[i], nfa_states);
        printf("%-10s", "");
        for (int j = 0; j < symbols; j++) {
            print_state(dfa_states[dfa[i][j]], nfa_states);
            printf("%-10s", "");
        }
        printf("\n");
    }

    return 0;
}
