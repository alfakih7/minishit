#include "../minishell.h"

bool	contains_redirect(char *line_chunk, char type)
{
	if (!line_chunk || !*line_chunk)
		return (false);
	if (*(ft_skip_spaces(line_chunk)) == type)
		return (true);
	return (false);
}