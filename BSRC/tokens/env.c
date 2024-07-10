/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:24:23 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/08 19:10:04 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

static char **array_dup(char **envp)
{
	char **my_env;
	int i;

	i = 0;
	if (!envp && !*envp)
		return (NULL);
	while (envp[i])
		i++;
	my_env = malloc(sizeof(char *) * (i + 1));
	if (!my_env)
		return (NULL);
	i = -1;
	while (envp[++i])
		my_env[i] = ft_strdup(envp[i]);
	my_env[i] = NULL;
	return (my_env);
}

//////askjdh >kasdh $PATH "akskdjh$PWD" $kasjdh $ $

static long	envcmp(char *str, char **my_env)
{
	int	i;
	int	n;
	int	x;
	int	which;
	int	temp;

	x = 0;
	n = 0;
	which = 0;
	i = 0;
	while (str[x] != '$')
		x++;
	temp = ++x;
	if (str[x])
	{
		while (my_env[i])
		{
			x = temp; n = 0;
			while((str[x] && my_env[i][n] && str[x] == my_env[i][n]))
			{
				x++;
				n++;
			}
			if (!str[x] && (my_env[i][n] == '=' || my_env[i][n] == '\0'))
				return (i);
			which++;
			i++;
		}
	}
		return (9999999999999); //// check $$$$
}


static char	*replace(char *str, char **my_env)
{
	int	i;
	long	the_num;
	char	*repl;

	i = 0;
	while (str[i] != '$')
		i++;
	if (!str[++i])
		return (str);
	the_num = envcmp(str, my_env);
	if (the_num == 9999999999999)
		return (NULL);
	i = 0;
	while (str[i] != '$')
		i++;
	repl = malloc(i + 1);
	i = -1;
	while (str[++i] != '$')
		repl[i] = str[i];
	repl[i] = '\0';
	repl = ft_strjoin(repl, getenv(my_env[the_num]));
	return (repl);
}

char	*expansion(char **env, char *line)
{
	char	**my_env;
	long long	i;

	i = 0;
	if (!line)
	{
		return (NULL);
	}
	my_env = array_dup(env);
	if (ft_strchr(line, '$'))
		line = replace(line, my_env);
	return(line);
}
