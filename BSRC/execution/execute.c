/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:29:49 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/31 19:11:20 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <sys/unistd.h>
#include <unistd.h>

void	with_path(char **split, char **path, char **env)
{
	char	*command;
	int		i;

	i = -1;
	while (path[++i])
	{
		command = ft_strjoin(path[i], split[0]);
		if (!access(command, F_OK))
			break ;
		free(command);
		command = NULL;
	}
	if (!access(command, F_OK) && access(command, X_OK))
	{
		write(2, "zsh: permission denied: ", 24);
		ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		ft_free(command, path);
		exit(126);
	}
	if (!command || execve(command, split, env) == -1)
	{
		write(2, "zsh: command not found: ", 24);
		ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		ft_free(command, path);
		exit(127);
	}
}

void	without_path(char **split, char **env)
{
	if (!access(split[0], F_OK) && access(split[0], X_OK))
	{
		write(2, "zsh: permission denied: ", 24);
		ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		exit(126);
	}
	if (!split || !split[0] || execve(split[0], split, env) == -1)
	{
		write(2, "zsh: command not found: ", 24);
		ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		exit(127);
	}
}

static void	execute_helper(t_cmd *cmd, int *fd)
{
	int		cmd_num;

	// printf("cmd_num = %d\n", cmd->cmd_num);
	if (ft_cmdlstsize(cmd) > 1)
		dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void	execute(t_cmd *cmd, char **env, int *fd)
{
	char	**path;

	if (fd)
		execute_helper(cmd, fd);
	if (!cmd)
	{
		ft_putstr_fd("here is the error\n", 2);
		exit (1);
	}
	the_ultimate_dup(cmd->redirect, fd);
	if (cmd->content)
	{
		// printf("you got hear?\n");
		if (!ft_strchr(cmd->content[0], '/'))
		{
			path = get_path(env);
			if (!path) //ft_free(NULL, cmd->content),
				exit(1);
			with_path(cmd->content, path, env);
		}
		else
			without_path(cmd->content, env);
	}
	exit (0);
}
