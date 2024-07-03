/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:17 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/04 01:17:45 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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