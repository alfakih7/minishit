/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 08:08:45 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/06 11:56:01 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/_types/_size_t.h>

static int	last_arg(char**cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
			i++;
	}
	return (--i);
}

static int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (1);
	while (str[i])
	{
		if (str[i++] != 'n')
			return (1);
	}
	return (0);
}

int	echo(char **cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (cmd && cmd[i++])
	{
		while (cmd[i] && !check_flag(cmd[i]))
			flag = i++;
		if (cmd[i])
			printf("%s", cmd[i++]);
		while (cmd[i])
			printf(" %s", cmd[i++]);
		if (!flag)
			printf("\n");
		return (0);
	}
	else
		return (1);
}
