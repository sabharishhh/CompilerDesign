#include <stdio.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_ALPHABET 10

int nfa[MAX_STATES][MAX_ALPHABET][MAX_STATES]; // NFA transitions
int nfa_states, symbols;
int dfa[MAX_STATES][MAX_ALPHABET];             // DFA transitions

int dfa_state_set[100][MAX_STATES];  // DFA states as sets of NFA states
int marked[100];                     // Mark DFA states as processed or not
int dfa_state_count = 0;

// Check if a DFA state already exists
int state_exists(int set[]) {
    for (int i = 0; i < dfa_state_count; i++) {
        int same = 1;
        for (int j = 0; j < nfa_states; j++) {
            if (dfa_state_set[i][j] != set[j]) {
                same = 0;
                break;
            }
        }
        if (same) return i;
    }
    return -1;
}

// Add new DFA state
int add_state(int set[]) {
    int idx = state_exists(set);
    if (idx != -1) return idx;

    for (int i = 0; i < nfa_states; i++)
        dfa_state_set[dfa_state_count][i] = set[i];

    marked[dfa_state_count++] = 0;
    return dfa_state_count - 1;
}

// Compute ε-move closure (not needed here, no ε in example)

int main() {
    int i, j, k, l;

    printf("\nNo. of NFA states: ");
    scanf("%d", &nfa_states);

    printf("No. of input symbols: ");
    scanf("%d", &symbols);

    printf("\nNFA transition table:\n");
    printf("Format: No. of next states --> by list of states\n\n");

    for (i = 0; i < nfa_states; i++) {
        for (j = 0; j < symbols; j++) {
            int count;
            printf("δ(q%d, %d): ", i, j);
            scanf("%d", &count);
            for (k = 0; k < count; k++) {
                int state;
                scanf("%d", &state);
                nfa[i][j][state] = 1;
            }
        }
    }

    // Subset construction
    int start[MAX_STATES] = {0};
    start[0] = 1; // start from q0
    add_state(start);

    for (i = 0; i < dfa_state_count; i++) {
        if (marked[i]) continue;

        marked[i] = 1;
        for (j = 0; j < symbols; j++) {
            int newset[MAX_STATES] = {0};
            for (k = 0; k < nfa_states; k++) {
                if (dfa_state_set[i][k]) {
                    for (l = 0; l < nfa_states; l++) {
                        if (nfa[k][j][l]) newset[l] = 1;
                    }
                }
            }
            int idx = add_state(newset);
            dfa[i][j] = idx;
        }
    }

    // Print DFA table
    printf("\nDFA Transition Table:\n");
    printf("State\t");
    for (i = 0; i < symbols; i++) printf("%d\t", i);
    printf("\n");

    for (i = 0; i < dfa_state_count; i++) {
        printf("{");
        for (j = 0; j < nfa_states; j++)
            if (dfa_state_set[i][j]) printf("q%d", j);
        printf("}  ");

        for (j = 0; j < symbols; j++) {
            printf("{");
            for (k = 0; k < nfa_states; k++) {
                if (dfa_state_set[dfa[i][j]][k])
                    printf("q%d", k);
            }
            printf("}  ");
        }
        printf("\n\n");
    }

    return 0;
}