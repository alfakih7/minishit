#include "minishell.h"

int update_quote_state(char current_char, int *quote_state)
{
    int initial_state;
    initial_state = *quote_state;

    if (current_char == '\'') {
        if (initial_state == 0) {
            *quote_state = 1; // that means now it's entering single quotes
        } else if (initial_state == 1) {
            *quote_state = 0; // that means it's exiting single quotes
        }
    } else if (current_char == '"') {
        if (initial_state == 0) {
            *quote_state = 2; // entering double quotes
        } else if (initial_state == 2) {
            *quote_state = 0; // exiting double quotes
        }
    }

    return (initial_state);
}
