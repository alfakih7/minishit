/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:59:42 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/31 22:33:21 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void	exec_heredoc_helper(t_files *files, int *pip)
{
	char	*line;
	char	*str;
	char	*temp;

	(close(pip[0]), close(pip[1]), close(files->heredoc_fd[0]));
	str = NULL;
	line = readline("> ");
	while (line && ft_strncmp(line,
			files->file_name, ft_strlen(files->file_name) + 1))
	{
		ft_putstr_fd(line, files->heredoc_fd[1]);
		ft_putstr_fd("\n", files->heredoc_fd[1]);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	if (line)
		free(line);
	(close(files->heredoc_fd[1]));
	exit(0);
}

void	execute_heredoc(t_files *files, int *pip)
{
	int	pid;

	pipe(files->heredoc_fd);
	pid = fork();
	if (pid == 0)
		exec_heredoc_helper(files, pip);
	else
	{
		waitpid(pid, NULL, 0);
		close(files->heredoc_fd[1]);
		if (files->last_input)
			dup2(files->heredoc_fd[0], STDIN_FILENO);
		close(files->heredoc_fd[0]);
	}
}