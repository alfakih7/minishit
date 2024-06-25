#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
#include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

typedef struct s_split_positions {
    int *positions;       // Array to store positions of the delimiter
    int current_index;    // Current index in the positions array
    bool inside_quotes;   // Flag indicating if we are inside single quotes
    bool inside_dquotes;  // Flag indicating if we are inside double quotes
} t_split_positions;

typedef struct s_split_vars {
    char *line;         // Original string to be split
    int c;              // Delimiter character
    size_t content_size;// Number of segments expected
    int *positions;     // Array of delimiter positions
    char **content;     // Array to store resulting substrings
} t_split_vars;


int update_quote_state(char current_char , int *quote_state);
int	check_quotes(char *command);
char	*chrskip(char *s, char c);
int	split_with_no_quotes_len(char *line, int c);
void ft_split_destroy(char **split_array);
char	**split_with_no_quotes(char *line, int c);
int *ms_char_positions(char *line, int c);
#endif