/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:17 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/30 04:48:01 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/_types/_pid_t.h>

int	main(int ac, char **av, char **env)
{
	t_tokens	*cmd;
	pid_t		pid;
	char		*str;
	int			i;

	while (42)
	{
		printf("minishell > \n");
		str = get_next_line(0);
		check_quotes(str);
		cmd = split_with_no_quotes(str, '|');
		i = 0;
		check_quotes(str);
		// // cmd = cmd->next->next;
		// printf("(%s)\n", cmd->content);
		// pid = fork();
		// if (!pid)
		// 	execute(cmd->content, env);
		while (cmd)
		{
			printf("cmd[%d] = (%s)\n", i, cmd->content);
			cmd = cmd->next;
			i++;
		}
		printf("num of pipes = %d\n", split_with_no_quotes_len(str, '|'));
		if (ft_strchr(str, '\"'))
			return (1);
	}
	return (0);
}

// Dummy implementation of get_next_line
