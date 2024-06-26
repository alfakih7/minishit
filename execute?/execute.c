/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:29:49 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/24 10:40:24 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/fcntl.h>

void	with_path(char *av, char **path, char **env)
{
	char	**split;
	char	*command;
	int		i;

	i = -1;
	split = ft_split(av, ' ');
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

void	without_path(char *av, char **env)
{
	char	**split;

	split = ft_split(av, ' ');
	if (!split || !split[0] || execve(split[0], split, env) == -1)
	{
		write(2, "zsh: command not found: ", 24);
		ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		ft_free(NULL, split);
		exit(127);
	}
}

void	execute_helper(char **av, t_fds *fd, int i)
{
	if (i == 2)
	{
		(*fd).fd_input = open(av[1], O_RDONLY);
		if ((*fd).fd_input == -1)
			(perror("zsh"), exit(1));
		dup2((*fd).fd_input, 0);
		(close((*fd).fd_input), close((*fd).pip[0]));
		dup2((*fd).pip[1], 1);
		close((*fd).pip[1]);
	}
	if (i == ((*fd).ac - 2))
	{
		(*fd).fd_output = open(av[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((*fd).fd_output == -1)
			(perror("zsh"), exit(1));
		dup2((*fd).fd_output, 1);
		(close((*fd).fd_output), close((*fd).pip[1]), close((*fd).pip[0]));
	}
	else
	{
		close((*fd).pip[0]);
		dup2((*fd).pip[1], 1);
		close((*fd).pip[1]);
	}
}

void	execute(char **av, char **env, int i, t_fds fd)
{
	char	**path;

	execute_helper(av, &fd, i);
	path = get_path(env);
	if (!path)
		exit (1);
	if (!ft_strchr(av[i], '/'))
		with_path(av[i], path, env);
	else
	{
		ft_free(NULL, path);
		without_path(av[i], env);
	}
}
