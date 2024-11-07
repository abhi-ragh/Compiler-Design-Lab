#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STATES 100
#define MAX_TRANSITIONS 100
#define MAX_STRING_LENGTH 1000

typedef struct {
    int transitions[MAX_STATES][2][MAX_STATES];  // [from_state][input][to_state]
    int num_states;
    int initial_state;
    int final_states[MAX_STATES];
    int num_final_states;
} NFA;

typedef struct {
    int state_mapping[10000];  // Maps bitmask to whether state exists
    int next_state[10000][2];  // Maps current state and input to next state
    int reachable_states[10000];  // List of reachable states
    int num_reachable_states;
} DFA;

// Function prototypes
void initialize_nfa(NFA *nfa);
void read_nfa_input(NFA *nfa);
void initialize_dfa(DFA *dfa);
void convert_nfa_to_dfa(NFA *nfa, DFA *dfa);
void print_dfa_states(DFA *dfa, NFA *nfa);
bool process_string(const char *input, NFA *nfa, DFA *dfa);
bool is_final_state(int state, NFA *nfa);
void print_path(const char *input, int initial_state, DFA *dfa);

int main() {
    NFA nfa;
    DFA dfa;
    char input_string[MAX_STRING_LENGTH];
    char continue_input;

    printf("\nNFA to DFA Converter\n");
    printf("===================\n");
    printf("Note: Use one-based indexing for states\n");

    // Initialize and read NFA
    initialize_nfa(&nfa);
    read_nfa_input(&nfa);

    // Convert NFA to DFA
    initialize_dfa(&dfa);
    convert_nfa_to_dfa(&nfa, &dfa);

    // Print resulting DFA states
    print_dfa_states(&dfa, &nfa);

    // Process strings
    do {
        printf("\nEnter string to test (using only 0s and 1s): ");
        scanf("%s", input_string);

        // Validate input string
        bool valid_input = true;
        for (int i = 0; input_string[i]; i++) {
            if (input_string[i] != '0' && input_string[i] != '1') {
                valid_input = false;
                break;
            }
        }

        if (!valid_input) {
            printf("Error: String must contain only 0s and 1s\n");
            continue;
        }

        // Process the string and show the path
        print_path(input_string, 1 << nfa.initial_state, &dfa);
        
        bool accepted = process_string(input_string, &nfa, &dfa);
        printf("\nResult: String is %s\n", accepted ? "ACCEPTED" : "REJECTED");

        printf("\nTest another string? (y/n): ");
        scanf(" %c", &continue_input);
    } while (continue_input == 'y' || continue_input == 'Y');

    return 0;
}

void initialize_nfa(NFA *nfa) {
    memset(nfa->transitions, 0, sizeof(nfa->transitions));
    nfa->num_states = 0;
    nfa->initial_state = 0;
    nfa->num_final_states = 0;
}

void read_nfa_input(NFA *nfa) {
    printf("\nEnter the number of states: ");
    scanf("%d", &nfa->num_states);
    
    if (nfa->num_states <= 0 || nfa->num_states > MAX_STATES) {
        printf("Error: Invalid number of states\n");
        exit(1);
    }

    printf("Enter number of final states: ");
    scanf("%d", &nfa->num_final_states);
    
    if (nfa->num_final_states > nfa->num_states) {
        printf("Error: Number of final states cannot exceed total states\n");
        exit(1);
    }

    printf("Enter final states: ");
    for (int i = 0; i < nfa->num_final_states; i++) {
        scanf("%d", &nfa->final_states[i]);
        if (nfa->final_states[i] >= nfa->num_states) {
            printf("Error: Invalid final state\n");
            exit(1);
        }
    }

    printf("Enter the number of transitions: ");
    int num_transitions;
    scanf("%d", &num_transitions);

    printf("Enter transitions as 'from_state input to_state':\n");
    for (int i = 0; i < num_transitions; i++) {
        int from, input, to;
        scanf("%d %d %d", &from, &input, &to);
        if (input != 0 && input != 1) {
            printf("Error: Input symbol must be 0 or 1\n");
            exit(1);
        }
        nfa->transitions[from][input][to] = 1;
    }

    printf("Enter initial state: ");
    scanf("%d", &nfa->initial_state);
}

void initialize_dfa(DFA *dfa) {
    memset(dfa->state_mapping, 0, sizeof(dfa->state_mapping));
    memset(dfa->next_state, 0, sizeof(dfa->next_state));
    dfa->num_reachable_states = 0;
}

void convert_nfa_to_dfa(NFA *nfa, DFA *dfa) {
    int initial_state_mask = 1 << nfa->initial_state;
    dfa->state_mapping[initial_state_mask] = 1;
    dfa->reachable_states[dfa->num_reachable_states++] = initial_state_mask;

    for (int i = 0; i < dfa->num_reachable_states; i++) {
        int current_state = dfa->reachable_states[i];

        // Process inputs 0 and 1
        for (int input = 0; input < 2; input++) {
            int new_state = 0;

            // Check transitions for each state in the current subset
            for (int state = 0; state < nfa->num_states; state++) {
                if (current_state & (1 << state)) {
                    for (int next = 0; next < nfa->num_states; next++) {
                        if (nfa->transitions[state][input][next]) {
                            new_state |= (1 << next);
                        }
                    }
                }
            }

            // Add new state if it hasn't been seen before
            if (new_state && !dfa->state_mapping[new_state]) {
                dfa->state_mapping[new_state] = 1;
                dfa->reachable_states[dfa->num_reachable_states++] = new_state;
            }

            dfa->next_state[current_state][input] = new_state;
        }
    }
}

void print_dfa_states(DFA *dfa, NFA *nfa) {
    printf("\nDFA States:\n");
    printf("===========\n");
    for (int i = 0; i < dfa->num_reachable_states; i++) {
        int state = dfa->reachable_states[i];
        printf("State %d: { ", i);
        for (int j = 0; j < nfa->num_states; j++) {
            if (state & (1 << j)) {
                printf("q%d ", j);
            }
        }
        printf("}\n");
    }
}

bool process_string(const char *input, NFA *nfa, DFA *dfa) {
    int current_state = 1 << nfa->initial_state;
    
    for (int i = 0; input[i]; i++) {
        current_state = dfa->next_state[current_state][input[i] - '0'];
    }

    return is_final_state(current_state, nfa);
}

bool is_final_state(int state, NFA *nfa) {
    for (int i = 0; i < nfa->num_final_states; i++) {
        if (state & (1 << nfa->final_states[i])) {
            return true;
        }
    }
    return false;
}

void print_path(const char *input, int initial_state, DFA *dfa) {
    printf("\nTransition path: ");
    int current_state = initial_state;
    printf("%d", current_state);
    
    for (int i = 0; input[i]; i++) {
        current_state = dfa->next_state[current_state][input[i] - '0'];
        printf(" -> %d", current_state);
    }
    printf("\n");
}
