#include "minishell.h"

bool	ms_contains_redirect(char *line_chunk, char type)
{
	if (!line_chunk || !*line_chunk)
		return (false);
	if (*(ft_skip_spaces(line_chunk)) == type)
		return (true);
	return (false);
}