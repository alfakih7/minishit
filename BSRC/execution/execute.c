/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:29:49 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/26 03:04:12 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void	with_path(char **split, char **path, char **env)
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
		// perror("zsh");
		ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		ft_free(NULL, path);
		ft_free(command, split);
		exit(127);
	}
}

void	without_path(char **split, char **env)
{
	if (!split || !split[0] || execve(split[0], split, env) == -1)
	{
		// write(2, "zsh: command not found: ", 24);
		// ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		ft_free(NULL, split);
		exit(127);
	}
}

static void	execute_helper(t_cmd *cmd, int *fd)
{
	int		cmd_num;

	printf("cmd_num = %d\n", cmd->cmd_num);
	if (ft_cmdlstsize(cmd) != 1)
		dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void	execute(t_cmd *cmd, char **env, int *fd)
{
	char	**path;
	char	**split;

	if (fd)
		execute_helper(cmd, fd);
	// split = ft_split(av[i], ' ');
	if (!cmd)
		exit (1);
	if (cmd->content)
	{
		if (!ft_strchr(cmd->content[0], '/'))
		{
			path = get_path(env);
			if (!path)
				(ft_free(NULL, cmd->content), exit(1));
			with_path(cmd->content, path, env);
		}
		else
		{
			ft_free(NULL, cmd->content);
			without_path(cmd->content, env);
		}
	}
}
