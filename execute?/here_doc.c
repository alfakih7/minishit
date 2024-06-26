/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 06:17:10 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/24 10:21:57 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_child(t_fds fd, char **av, char **env)
{
	char	**path;

	path = get_path(env);
	if (!path)
		exit (1);
	close(fd.here[1]);
	dup2(fd.here[0], 0);
	close(fd.here[0]);
	close(fd.pip[0]);
	dup2(fd.pip[1], 1);
	close(fd.pip[1]);
	if (!ft_strchr(av[3], '/'))
		with_path(av[3], path, env);
	else
	{
		ft_free(NULL, path);
		without_path(av[3], env);
	}
}

void	execute_parent(int *pip, char **av, char **env)
{
	int		fd;
	char	**path;

	path = get_path(env);
	if (!path)
		exit (1);
	fd = open(av[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("zsh");
		ft_free(NULL, path);
		exit(1);
	}
	close(pip[1]);
	dup2(pip[0], 0);
	close(pip[0]);
	dup2(fd, 1);
	close(fd);
	if (!ft_strchr(av[4], '/'))
		with_path(av[4], path, env);
	else
	{
		ft_free(NULL, path);
		without_path(av[4], env);
	}
}

static void	here_doc(char **av, int *fd)
{
	char	*line;
	char	*str;
	char	*temp;

	close(fd[0]);
	str = NULL;
	line = get_next_line(0);
	temp = ft_strjoin(av[2], "\n");
	while (line && ft_strncmp(line,
			temp, ft_strlen(av[2]) + 1))
	{
		free(temp);
		temp = NULL;
		temp = ft_strjoin(av[2], "\n");
		str = get_ft_strjoin(str, line);
		free(line);
		line = NULL;
		line = get_next_line(0);
	}
	if (line)
		free(line);
	if (temp)
		free(temp);
	ft_putstr_fd(str, fd[1]);
	close(fd[1]);
}

void	heredoc_decide(char **av, t_fds	*fd, char **env)
{
	pid_t	pid;
	int		status;

	pipe((*fd).pip);
	pid = fork();
	if (!pid)
	{
		pipe((*fd).here);
		pid = fork();
		if (pid == 0)
			here_doc(av, (*fd).here);
		else
			execute_child(*fd, av, env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			execute_parent((*fd).pip, av, env);
		else
		{
			(close((*fd).pip[0]), close((*fd).pip[1]));
			(waitpid(pid, &status, 0), exit (WEXITSTATUS(status)));
		}
	}
}

void	pipe_decide(char **av, t_fds *fd, char **env, int ac)
{
	pid_t	pid;
	int		status;
	int		i;

	i = 2;
	(*fd).ac = ac;
	while (i < (ac - 1))
	{
		pipe((*fd).pip);
		pid = fork();
		if (!pid)
			execute(av, env, i, *fd);
		else
		{
			close((*fd).pip[1]);
			dup2((*fd).pip[0], 0);
			close((*fd).pip[0]);
			if (i == ac - 2)
			{
				waitpid(pid, &status, 0);
				exit (WEXITSTATUS(status));
			}
			i++;
		}
	}
}
