/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 06:17:10 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/24 03:19:28 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_fd(char *av, int *pip, char **split)
{
	int	fd;

	fd = open(av, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("zsh");
		ft_free(NULL, split);
		(close(pip[0]), close(pip[1]));
		exit(1);
	}
	return (fd);
}

void	execute_child(t_fds fd, char **av, char **env)
{
	char	**path;
	char	**splitted;

	splitted = ft_split(av[3], ' ');
	if (!splitted)
	{
		(close(fd.pip[0]), close(fd.pip[1]));
		(close(fd.here[0]), close(fd.here[1]), exit (1));
	}
	close(fd.here[1]);
	dup2(fd.here[0], 0);
	close(fd.here[0]);
	close(fd.pip[0]);
	dup2(fd.pip[1], 1);
	close(fd.pip[1]);
	if (!ft_strchr(splitted[0], '/'))
	{
		path = get_path(env);
		if (!path)
			(ft_free(NULL, splitted), exit(1));
		with_path(splitted, path, env);
	}
	else
		without_path(splitted, env);
}

void	execute_parent(int *pip, char **av, char **env)
{
	int		fd;
	char	**path;
	char	**splitted;

	splitted = ft_split(av[4], ' ');
	if (!splitted)
		exit (1);
	fd = open_fd(av[5], pip, splitted);
	close(pip[1]);
	dup2(pip[0], 0);
	close(pip[0]);
	dup2(fd, 1);
	close(fd);
	if (!ft_strchr(splitted[0], '/'))
	{
		path = get_path(env);
		if (!path)
			(ft_free(NULL, splitted), exit(1));
		with_path(splitted, path, env);
	}
	else
		without_path(splitted, env);
}

void	here_doc(char **av, t_fds *fd)
{
	char	*line;
	char	*str;
	char	*temp;

	(close((*fd).pip[0]), close((*fd).pip[1]), close((*fd).here[0]));
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
	ft_putstr_fd(str, (*fd).here[1]);
	(free (str), close((*fd).here[1]));
}
