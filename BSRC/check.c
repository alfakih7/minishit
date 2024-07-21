/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:10:29 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/20 18:07:17 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int print_error(int error_code, char *content)
{
    if (error_code == 1)
    {
        printf("\033[91m%s\033[0m\n",
            "minishell: parse error, quotes are never closed");
    }
    else if (error_code == 2)
    {
        printf("\033[91m%s '%s'\033[0m\n",
            "minishell: parse error, near", content);
    }
    else if (error_code == 3)
    {
        printf("\033[91m%s '%s'\033[0m\n",
            "minishell: the command cannot end with",
            content);
    }
    return 1;
}
int	check_quotes(char *command)
{
	int	cur;
	int	in_quotes;

	cur = 0;
	in_quotes = 0;
	while (command && command[cur])
	{
		update_quote_state(command[cur], &in_quotes);
		cur++;
	}
	if (in_quotes != 0)
		print_error(1, NULL);
	return (in_quotes != 0);
}
