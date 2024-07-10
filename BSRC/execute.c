/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:29:49 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/30 04:39:39 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	with_path(char **split, char **path, char **env)
{
	char	*command;
	int		i;

	i = -1;
	while (path[++i])
	{
		command = ft_strjoin(path[i], split[0]);
		if (!access(command, X_OK))
			break ;
		free(command);
		command = NULL;
	}
	if (!command || execve(command, split, env) == -1)
	{
		write(2, "zsh: command not found: ", 24);
		ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		ft_free(NULL, path);
		ft_free(command, split);
		exit(127);
	}
}

static void	without_path(char **split, char **env)
{
	if (!split || !split[0] || execve(split[0], split, env) == -1)
	{
		write(2, "zsh: command not found: ", 24);
		ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		ft_free(NULL, split);
		exit(127);
	}
}

void	execute(char *av, char **env)
{
	char	**path;
	char	**split;

	split = ft_split(av, ' ');
	if (!split)
		exit(1);
	path = get_path(env);
	if (!path)
		(ft_free(NULL, split), exit (1));
	if (!ft_strchr(split[0], '/'))
		with_path(split, path, env);
	else
	{
		ft_free(NULL, path);
		without_path(split, env);
	}
}
