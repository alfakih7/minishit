/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:29:45 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/28 23:07:35 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

// void	heredoc_decide(char **av, t_fds	*fd, char **env)
// {
// 	pid_t	pid;
// 	int		status;

// 	pipe((*fd).pip);
// 	pid = fork();
// 	if (!pid)
// 	{
// 		pipe((*fd).here);
// 		pid = fork();
// 		if (pid == 0)
// 			here_doc(av, fd);
// 		else
// 			execute_child(*fd, av, env);
// 	}
// 	else
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 			execute_parent((*fd).pip, av, env);
// 		else
// 		{
// 			(close((*fd).pip[0]), close((*fd).pip[1]));
// 			(waitpid(pid, &status, 0), exit (WEXITSTATUS(status)));
// 		}
// 	}
// }

void	pipe_decide(t_cmd *cmd, char **env, int tmp_fd[2])
{
	pid_t	pid;
	t_cmd	*temp;
	int		status;
	int		i;
	int		size;
	int		fd[2];

	i = 0;
	temp = cmd;
	size = ft_cmdlstsize(cmd);
	while (i < size && temp)
	{
		pipe(fd);
		pid = fork();
		if (!pid)
		{
			close(tmp_fd[0]);
			close(tmp_fd[1]);
			printf("\x1b[0m");
			execute(temp, env, fd);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			if (i == size - 1)
			{
				waitpid(pid, &status, 0);
				(WEXITSTATUS(status));
			}
			temp = temp->next;
			i++;
		}
	}
}
