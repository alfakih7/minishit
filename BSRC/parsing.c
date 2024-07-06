/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:17 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/06 22:24:06 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static	void	printlist(t_files *file)
{
	while (file)
	{
		printf("type = %d  file_name = %s\n", file->type, file->file_name);
		file = file->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	int			i;
	t_cmd		*redirections;
	char		*line_chunk;
	char		**cmd; //splitted by pipes

	i = -1;
    while (1)
	{
        printf("minishell > \n");
        line_chunk = get_next_line(0);
		if (line_chunk)
        {
			check_quotes(line_chunk);
			if (!check_syntax(line_chunk))
				ft_putstr_fd("syntax error", 2);
			else
			{
				cmd = split_with_no_quotes(line_chunk, '|');
				if (cmd)
				{
					redirections = ft_redirection(joined_str(cmd[0]));
					// printf("waa");
					printlist(redirections->redirect);
					if (!cmd)
						return (1);
						i = -1;
					while ((redirections->content && redirections->content[++i]))
						printf("cmd [%d] = %s\n", i, redirections->content[i]);
				}
			}
		}
    }

    return 0;
}
