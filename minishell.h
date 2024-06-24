#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "gnl/get_next_line.h"
#include "libft/libft.h"

int update_quote_state(char current_char , int *quote_state);
int	check_quotes(char *command);
#endif