#include "minishell.h"

bool	contains_cmd(char *line_chunk)
{
	if (!(*ft_skip_spaces(line_chunk)))
		return (false);
	return (true);
}