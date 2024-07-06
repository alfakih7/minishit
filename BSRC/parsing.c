/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:17 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/06 11:09:58 by asid-ahm         ###   ########.fr       */
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

	if (ac == 1)
	{
		while (42)
		{
			printf("minishell > \n");
			str = get_next_line(0);
			check_quotes(str);
			if (check_syntax(str))
			{
				cmd = split_with_no_quotes(str, '|');
				echo(ft_split(cmd->content, ' '));
				i = 0;
				check_quotes(str);
				// // cmd = cmd->next->next;
				// printf("(%s)\n", cmd->content);
				// pid = fork();
				// if (!pid)
				// 	execute(cmd->content, env);
				// while (cmd)
				// {
				// 	printf("cmd[%d] = (%s)\n", i, cmd->content);
				// 	cmd = cmd->next;
				// 	i++;
				// }
				// printf("num of pipes = %d\n", split_with_no_quotes_len(str, '|'));
				if (ft_strchr(str, '\"'))
					return (1);
			}
			else 
			{
				ft_putstr_fd("syntax error\n", 2);
			}
		}
		return (0);
	}
	else
	{	
		ft_putstr_fd("to much arguments\n", 2);
		return (1);
	}
}

// Dummy implementation of get_next_line
