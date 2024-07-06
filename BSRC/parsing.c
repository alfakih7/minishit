/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:41:27 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/06 07:42:19 by asid-ahm         ###   ########.fr       */
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
		// cmd = cmd->next->next;
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
		// if (ft_strchr(str, '\"'))
		// 	return (1);
	}
	return (0);
}

// Dummy implementation of get_next_line
int main(int ac, char **av, char **env)
{
    t_tokens *cmd;
    char *line_chunk;
    int ptr = 0;
	int	i;
    t_file *redirect;

    while(42)
    {
        line_chunk = get_next_line(0);
		if (line_chunk)
		{
        	printf("minishell > ");
			check_quotes(line_chunk);
			if (!check_syntax(line_chunk))
				ft_putstr_fd("syntax error near unexpected token\n", 2);
			// cmd = tokens_1(split_with_no_quotes(line_chunk, '|'));
			// while (line_chunk[ptr]) {
			// redirect = ms_get_next_redirect(line_chunk, '>', &ptr);
			// if (redirect) {
			//     printf("Redirect: %s, Extra: %d\n", redirect->name, redirect->is_extra);
			//     free(redirect->name);
			//     free(redirect);
			// }
			i = 0;
			// while (cmd)
			// {
			// 	printf("cmd[%d] = (%s)\n",i++ , cmd->content);
			// 	cmd = cmd->next;
			// }
			// printf("num of pipes = %d\n", split_with_no_quotes_len(line_chunk, '|'));
			// if (ft_strchr(line_chunk, '\"'))
			// 	return (1);
		}
    }
    return (0);
}
